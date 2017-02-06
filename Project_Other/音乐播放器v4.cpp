/*在g++编译参数中加上 -lOpenSLES */
/*作者:毛玉*/
/*
第八版更新记录
    大幅度修改了代码结构
    增加了环境回响，但安卓不支持SLEnvironmentalReverbSettings(然并卵)<-不认真看文档的后果
*/

#include <string>
#include <vector>
#include <stack>
#include <regex>
#include <thread>
#include <iostream>
#include <atomic>
#include <mutex>
#include <random>
#include <functional>
#include <condition_variable>

#include <cmath>
#include <unistd.h>
#include <conio.h>
#include <dirent.h>
#include <SLES/OpenSLES.h>

using namespace std;

struct filepath
{
	string path;
	string file;
	
	string toString()
	{
	    return file;
	}
};

enum PlayMode
{
    ORDER=0,
    RANDOM
};

vector < filepath > FindFileInDir(string dirname, int r)
{
	vector < filepath > entitylist;
	DIR *dirptr = NULL;
	struct dirent *entry = NULL;
	if ((dirptr = opendir(dirname.c_str())) == NULL)
		return vector < filepath > ();

	for (int i = 0; entry = readdir(dirptr); i++)
	{
		if (entry->d_type == DT_REG)
		{
			filepath e;
			e.path = dirname;
			e.file = entry->d_name;
			entitylist.push_back(e);
		}
		if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".")
			&& strcmp(entry->d_name, "..") && r)
		{
			string next_dirname = dirname + "/" + entry->d_name;
			vector < filepath > next_entitylist = FindFileInDir(next_dirname, r);
			entitylist.insert(entitylist.end(),next_entitylist.begin(),next_entitylist.end());
		}
	}
	closedir(dirptr);
	return std::move(entitylist);
}

vector < filepath > Filter(vector < filepath > &&le, string match)
{
	vector < filepath > ret;
	regex reg(match,regex_constants::icase);//icase->忽略大小写
	for (auto & e:le)
		if (regex_match(e.file,reg))
			ret.push_back(e);
			
	return std::move(ret);
}

void ShowProgressBar(int progress,int total)
{
    cout<<("[");
    for(int i=0;i<total;++i)
    if(i<progress)
        cout<<"=";
    else
        cout<<" ";
    cout<<"]";
}

struct EnvironmentalReverbSettings
{
    SLEnvironmentalReverbSettings sers;
    string name;
    
    string toString()
    {
        return name;
    }
};

static vector<EnvironmentalReverbSettings> environment_preset(
{
    {SL_I3DL2_ENVIRONMENT_PRESET_DEFAULT,"默认"},
    {SL_I3DL2_ENVIRONMENT_PRESET_GENERIC,"一般"},
    {SL_I3DL2_ENVIRONMENT_PRESET_PADDEDCELL,"墙壁都是软垫的房间"},
    {SL_I3DL2_ENVIRONMENT_PRESET_ROOM,"房间"},
	{SL_I3DL2_ENVIRONMENT_PRESET_BATHROOM,"浴室"},
    {SL_I3DL2_ENVIRONMENT_PRESET_LIVINGROOM,"客厅"},
    {SL_I3DL2_ENVIRONMENT_PRESET_STONEROOM,"石房"},
    {SL_I3DL2_ENVIRONMENT_PRESET_AUDITORIUM,"礼堂"},
    {SL_I3DL2_ENVIRONMENT_PRESET_CONCERTHALL,"音乐厅"},
    {SL_I3DL2_ENVIRONMENT_PRESET_CAVE,"洞穴"},
    {SL_I3DL2_ENVIRONMENT_PRESET_ARENA,"竞技场"},
    {SL_I3DL2_ENVIRONMENT_PRESET_HANGAR,"飞机库"},
    {SL_I3DL2_ENVIRONMENT_PRESET_CARPETEDHALLWAY,"有地毯的走廊"},
    {SL_I3DL2_ENVIRONMENT_PRESET_HALLWAY,"走廊"},
    {SL_I3DL2_ENVIRONMENT_PRESET_STONECORRIDOR,"石头走廊"},
    {SL_I3DL2_ENVIRONMENT_PRESET_ALLEY,"小巷"},
    {SL_I3DL2_ENVIRONMENT_PRESET_FOREST,"森林"},
    {SL_I3DL2_ENVIRONMENT_PRESET_CITY,"城市"},
    {SL_I3DL2_ENVIRONMENT_PRESET_MOUNTAINS,"山地"},
    {SL_I3DL2_ENVIRONMENT_PRESET_QUARRY,"采石场"},
    {SL_I3DL2_ENVIRONMENT_PRESET_PLAIN,"平原"},
    {SL_I3DL2_ENVIRONMENT_PRESET_PARKINGLOT,"停车场"},
    {SL_I3DL2_ENVIRONMENT_PRESET_SEWERPIPE,"污水管"},
    {SL_I3DL2_ENVIRONMENT_PRESET_UNDERWATER,"水下"},
    {SL_I3DL2_ENVIRONMENT_PRESET_SMALLROOM,"小房间"},
    {SL_I3DL2_ENVIRONMENT_PRESET_MEDIUMROOM,"中等房间"},
    {SL_I3DL2_ENVIRONMENT_PRESET_LARGEROOM,"大房间"},
    {SL_I3DL2_ENVIRONMENT_PRESET_MEDIUMHALL,"中型礼堂"},
    {SL_I3DL2_ENVIRONMENT_PRESET_LARGEHALL,"大礼堂"},
    {SL_I3DL2_ENVIRONMENT_PRESET_PLATE,"盘子"}
});
	
class AudioPlayer
{
	SLObjectItf soi = nullptr;//引擎对象接口
	SLEngineItf sei = nullptr;//引擎对象的引擎接口
	
	SLObjectItf soi_mix = nullptr;//输出混响器接口
	SLEnvironmentalReverbItf ser = nullptr;//输出混响器的环境混响接口
	
	SLDataLocator_URI sdl_uri;//文件位置
	SLDataFormat_MIME sdf_mime;//文件格式
	SLDataSource sl_data_source;//数据源

	SLDataLocator_OutputMix sdl_om;//混响器位置(输出位置)
	SLDataSink sl_data_sink;//输出槽
	
	SLObjectItf soi_player = nullptr;//播放器对象接口
	SLPlayItf spi = nullptr;//播放器对象的播放接口
	SLSeekItf ssi = nullptr;//播放器对象的seek接口
	
	thread* callback_thread=nullptr;//EOS回调函数线程
	mutex callback_mtx;//EOS回调函数线程用的互斥锁
	condition_variable cv;//EOS回调线程用的条件变量
	function<void()> eos_callback;//回调函数
	void* eos_callback_arg[5]={nullptr,&callback_thread,&callback_mtx,&cv};//EOS回调函数的参数
	
	filepath current_filepath;
	
	mutex mtx;
	
	bool was_display=false;
	
	public:	
	
	 ~AudioPlayer()
	{
	    if(callback_thread!=nullptr)
	    {
	        callback_thread->join();
	        delete callback_thread;
	    }
		if (soi_player != nullptr)
			(*soi_player)->Destroy(soi_player);
		(*soi_mix)->Destroy(soi_mix);
		(*soi)->Destroy(soi);
	}

	AudioPlayer()
	{
		create();
	}

	AudioPlayer(filepath file)
	{
		create();
		setSource(file);
	}

	void create()
	{	    
		// 创建引擎对象
		slCreateEngine(&soi, 0, NULL, 0, NULL, NULL);
		(*soi)->Realize(soi, false);//每个新创建的对象必须先实现
		(*soi)->GetInterface(soi, SL_IID_ENGINE, &sei);		
		
		SLInterfaceID ids[]={SL_IID_ENVIRONMENTALREVERB};
		SLboolean req[]={SL_BOOLEAN_FALSE};
		
		// 从引擎对象创建输出混响器对象
		(*sei)->CreateOutputMix(sei, &soi_mix, 1, ids,req);
		(*soi_mix)->Realize(soi_mix, SL_BOOLEAN_FALSE);
		(*soi_mix)->GetInterface(soi_mix,SL_IID_ENVIRONMENTALREVERB,&ser);
		
	}

	void setSource(filepath file)
	{
	    unique_lock<mutex> ul(mtx);//上锁
		if (soi_player != nullptr)
		{
			(*soi_player)->Destroy(soi_player);
			soi_player = nullptr;
			spi=nullptr;
			ssi=nullptr;
		}

		current_filepath=file;
		// 配置源
		sdl_uri.locatorType = SL_DATALOCATOR_URI;
		sdl_uri.URI = (SLchar *) (file.path+"/"+file.file).c_str();
		sdf_mime.formatType = SL_DATAFORMAT_MIME;
		sdf_mime.mimeType = NULL;
		sdf_mime.containerType = SL_CONTAINERTYPE_UNSPECIFIED;
		sl_data_source.pLocator = &sdl_uri;
		sl_data_source.pFormat = &sdf_mime;

		// 配置输出
		sdl_om.locatorType = SL_DATALOCATOR_OUTPUTMIX;
		sdl_om.outputMix = soi_mix;
		sl_data_sink.pLocator = &sdl_om;
		sl_data_sink.pFormat = NULL;
		
		SLInterfaceID id[] = { SL_IID_SEEK};//配置需要的接口
		SLboolean req[] = { SL_BOOLEAN_FALSE};
		// 创建音频播放器对象
		(*sei)->CreateAudioPlayer(sei, &soi_player, &sl_data_source,&sl_data_sink, 1, id, req);
		(*soi_player)->Realize(soi_player, false);
		(*soi_player)->GetInterface(soi_player, SL_IID_PLAY, &spi);//获取播放器对象接口
		(*soi_player)->GetInterface(soi_player, SL_IID_SEEK, &ssi);
		
		//注册播放回调
		(*spi)->RegisterCallback(spi,[](SLPlayItf self,void* pContext,SLuint32 event)
		{
		    void** arg=(void**)pContext;
		    thread** callback_thread=static_cast<thread**>(arg[1]);
		    if(*callback_thread!=nullptr)
		    {
		        (*callback_thread)->join();
		        delete *callback_thread;
		        *callback_thread=nullptr;
		     }
		    if(arg[0]!=nullptr&&(event&SL_PLAYEVENT_HEADATEND))
		    {
		        *callback_thread=new thread([=]{
		            unique_lock<mutex> lck(*static_cast<mutex*>(arg[2]));
		            static_cast<condition_variable*>(arg[3])->wait_for(lck,chrono::milliseconds(500));
		            (*static_cast<function<void()>*>(arg[0]))();
		            });
		          static_cast<condition_variable*>(arg[3])->notify_all();
		    }
		},eos_callback_arg);
		(*spi)->SetCallbackEventsMask(spi,SL_PLAYEVENT_HEADATEND);
	}

	void play()
	{
	    if(spi==nullptr)return;
	    
	    unique_lock<mutex> ul(mtx);
	    (*spi)->SetPlayState(spi, SL_PLAYSTATE_PLAYING);
	}

	void pause()
	{
	    if(spi==nullptr)return;
	    
	    unique_lock<mutex> ul(mtx);
	    (*spi)->SetPlayState(spi, SL_PLAYSTATE_PAUSED);
	}

	void stop()
	{
	    if(spi==nullptr)return;
	    
	    unique_lock<mutex> ul(mtx);
	    (*spi)->SetPlayState(spi, SL_PLAYSTATE_STOPPED);
	}

	void seek(uint32_t ms)
	{
	    if(ssi==nullptr)return;
	    
	    unique_lock<mutex> ul(mtx);
	    (*ssi)->SetPosition(ssi, ms, SL_SEEKMODE_FAST);
	}
	
	uint32_t getState()
	{
	    if(spi==nullptr)return SL_PLAYSTATE_STOPPED;
	    
	    unique_lock<mutex> ul(mtx);
	    
	    SLuint32 state;
	    (*spi)->GetPlayState(spi,&state);
	    return state;
	}

	uint32_t getPosition()
	{
	    if(spi==nullptr)return 0;
	    
	    unique_lock<mutex> ul(mtx);
	    
		SLmillisecond position;
		(*spi)->GetPosition(spi, &position);
		return position;
	}

	uint32_t getDuration()
	{
	    if(spi==nullptr)return 0;
	    
	    unique_lock<mutex> ul(mtx);
		
		SLmillisecond duration;
		(*spi)->GetDuration(spi, &duration);
		return duration;
	}
	
	void setEnvironmentalReverb(EnvironmentalReverbSettings sers)
	{
	    if(ser==nullptr)return;
	    (*ser)->SetEnvironmentalReverbProperties(ser,&sers.sers);
	}
	
	filepath getFileName()
	{
	    return current_filepath;
	}
	
	void RegisterEOSCallback(function<void()> callback)
	{
	    eos_callback=callback;
	    eos_callback_arg[0]=(void*)&eos_callback;
	}
	
	void setDisplay(bool display)
	{
	    was_display=display;
	}
	
	bool isDisplay()
    {
        return was_display;
    }
	
	void show()
	{
	    if(was_display){
	        uint32_t current=getPosition()/1000;
	        uint32_t end=getDuration()/1000;
	        cout<<"Playing:"<<current_filepath.file<<endl;       
	        cout<<"Time: ";
	        ShowProgressBar(((double)current/end)*20,20);
	        cout<<current/60<<":"<<current%60<<"/"<<end/60<<":"<<end%60<<endl;
	    }
	}
};

template<class T>
class Menu
{
    vector<T> list;
    string menu_title;
    static mutex mtx;
    int page=0,total_page;
    int item_index=-1;
    bool was_display=false;
    public:
    Menu()=default;
    Menu(vector<T>& l)
    {
        create(l);
    }
    
    Menu(vector<T>&& l)
    {
        create(l);
    }
    
    Menu(Menu<T>&&)=default;
    
    void create(vector<T>& l)
    {
        list=std::move(l);
        total_page=ceil(list.size()/10)-1;
    }
    
    size_t size()
    {
        return list.size();
    }
    
    void setTitle(string title)
    {
        menu_title=title;
    }
    
    void setItemIndex(int index)
    {
        if(index>=0&&index<list.size())
            item_index=index;
    }
    
    int getItemIndex()
    {
        return item_index;
    }
   
    const T& getSelectedItem()
    {
        return list[item_index];
    }
    
    void nextPage()
    {
        if(page<total_page)
        ++page;
    }
    
    void frontPage()
    {
        if(page>0)
        --page;
    }
            
    void setPage(int page)
    {
        if(page<total_page)
            this->page=page-1;
    }
            
    size_t getPage()
    {
        return page;
    }
    
    void setDisplay(bool display)
    {
        unique_lock<mutex> lck(mtx);
        was_display=display;
    }
    
    bool isDisplay()
    {
        return was_display;
    }
    
    void show()
    {
        unique_lock<mutex> lck(mtx);
        if(was_display)
        {
            cout<<menu_title<<"["<<item_index+1<<"/"<<list.size()<<"]:"<<endl;
            for(int i=0;i<10;++i)
            {
                if(page*10+i>=list.size())break;
                if(page*10+i==item_index)cout<<"\033[33m";
                cout<<"["<<i<<"] "<<list[page*10+i].toString();
                if(page*10+i==item_index)cout<<"\033[37m";
                cout<<endl;
            }
            cout<<"Page:"<<page+1<<"/"<<total_page+1<<endl<<endl;
        }
   }
};

template<class T>
mutex Menu<T>::mtx;

enum
{
    MUSICMENU,
    ENVIRONMENTALREVERBMENU
};

atomic_int play_mode(ORDER);

stack<int> music_play_history;//栈顶是当前歌曲

 random_device rd;//硬件随机数
 mt19937 mt(rd());//随机数生成器(梅森随机数算法)
 uniform_int_distribution<int> uid;//平均分布器

bool quit_flag=false;

void NextMusic(AudioPlayer& ap,Menu<filepath>& music_menu)
{
    if(music_play_history.empty())return;
    if(play_mode==ORDER)
    {
        int next=music_play_history.top();
        next=(next+1)%music_menu.size();
        music_play_history.push(next);
        music_menu.setItemIndex(next);
     }
     if(play_mode==RANDOM)
     {
         int next=0;
         do
             next=uid(mt);
         while(next==music_play_history.top());
         
         music_play_history.push(next);
         music_menu.setItemIndex(next);
     }
     ap.setSource(music_menu.getSelectedItem());
     ap.play();
}

void FrontMusic(AudioPlayer& ap,Menu<filepath>& music_menu)
{
    if(music_play_history.size()<=1)return;
    music_play_history.pop();
    int front=music_play_history.top();
    music_menu.setItemIndex(front);
    
    ap.setSource(music_menu.getSelectedItem());
    ap.play();
}

void DisplayThread(AudioPlayer& ap,Menu<filepath>& music_menu,Menu<EnvironmentalReverbSettings>& environment_menu)
{
    int t=0;
    while(!quit_flag)
    {
        clrscr();
        ap.show();
        cout<<"Mode:"<<((play_mode==ORDER)?"Order":"Random")<<endl<<endl;
        music_menu.show();
        environment_menu.show();
                
        cout<<"[P]暂停/播放  "<<"[S]停止播放  "<<"[F]上一页  "<<"[N]下一页  "<<"[0-9]选择\n"<<"[K]上一曲  "<<"[L]下一曲  "<<(music_menu.isDisplay()?"[E]混响菜单  ":"[E]音乐菜单  ")<<"[M]模式  "<<"[Q]退出"<<endl;
        
        usleep(250000);
    }
}

int main()
{
    string dir_path;
    cout<<"音乐文件夹路径:";
    cin>>dir_path;
    cout<<"扫描中...."<<endl;
	Menu<filepath> music_menu(Filter(FindFileInDir(dir_path,1),".*(\\.mp3|\\.ogg|\\.wav|\\.flac|\\.aac)"));
	Menu<EnvironmentalReverbSettings> environment_menu(environment_preset);
	music_menu.setDisplay(true);
	music_menu.setTitle("Music List");
	environment_menu.setTitle("Environmental Preset List");
	
	uid=uniform_int_distribution<int>(0,music_menu.size()-1);
	
	AudioPlayer ap;
	ap.setDisplay(true);
	ap.RegisterEOSCallback([&]{
	    NextMusic(ap,music_menu);
	    });
	environment_menu.setItemIndex(0);
	ap.setEnvironmentalReverb(environment_menu.getSelectedItem());
	    
	thread display_thread(DisplayThread,std::ref(ap),std::ref(music_menu),std::ref(environment_menu));
	
	char command;
    while(!quit_flag)
    {
        command=getch();
        if(command>='A'&&command<='Z')
            command+=32;
        switch(command)
        {
            case 'n':
            if(music_menu.isDisplay())
                music_menu.nextPage();
            if(environment_menu.isDisplay())
                environment_menu.nextPage();
            break;
            
            case 'f':
            if(music_menu.isDisplay())
                music_menu.frontPage();
            if(environment_menu.isDisplay())
                environment_menu.frontPage();
            break;
            
            case 's':
            ap.stop();          
            break;
            
            case 'p':
            if(ap.getState()==SL_PLAYSTATE_PLAYING)
                ap.pause();
            else
                ap.play();   
            break;
            
            case 'q':
            quit_flag=true;
            break;
            
            case 'k':
            FrontMusic(ap,music_menu);
            break;
            
            case 'l':
            NextMusic(ap,music_menu);
            break;
            
            case 'm':
            ++play_mode;
            play_mode=play_mode%2;
            break;
            
            case 'e':
            music_menu.setDisplay(!music_menu.isDisplay());
            environment_menu.setDisplay(!environment_menu.isDisplay());
            break;
            
            default:
            if(command>='0'&&command<='9')
            {
                if(music_menu.isDisplay())
                {
                    int pos=music_menu.getPage()*10+command-'0';
                    if(pos<music_menu.size())
                    {
                        ap.stop();
                        music_menu.setItemIndex(pos);
                        music_play_history.push(pos);
                        ap.setSource(music_menu.getSelectedItem());
                        ap.play();
                    }
                }
                if(environment_menu.isDisplay())
                {
                    int pos=environment_menu.getPage()*10+command-'0';
                    if(pos<environment_menu.size())
                    {
                        environment_menu.setItemIndex(pos);
                        ap.setEnvironmentalReverb(environment_menu.getSelectedItem());
                    }
                }
            }
        }
    }
    display_thread.join();
    clrscr();
    cout<<"已退出"<<endl;
    return 0;
}