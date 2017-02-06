/*在g++编译参数中加上 -lOpenSLES */
/*作者:毛玉*/

#include <string>
#include <vector>
#include <stack>
#include <regex>
#include <thread>
#include <iostream>
#include <atomic>
#include <mutex>
#include <cmath>
#include <unistd.h>
#include <conio.h>
#include <dirent.h>
#include <SLES/OpenSLES.h>

using namespace std;

struct entity
{
	string path;
	string file;
};

enum PlayMode
{
    ORDER=0,
    RANDOM
};

vector < entity > FindFileInDir(string dirname, int r)
{
	vector < entity > entitylist;
	DIR *dirptr = NULL;
	struct dirent *entry = NULL;
	if ((dirptr = opendir(dirname.c_str())) == NULL)
		return vector < entity > ();

	for (int i = 0; entry = readdir(dirptr); i++)
	{
		if (entry->d_type == DT_REG)
		{
			entity e;
			e.path = dirname;
			e.file = entry->d_name;
			entitylist.push_back(e);
		}
		if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".")
			&& strcmp(entry->d_name, "..") && r)
		{
			string next_dirname = dirname + "/" + entry->d_name;
			vector < entity > next_entitylist = FindFileInDir(next_dirname, r);
			entitylist.insert(entitylist.end(),next_entitylist.begin(),next_entitylist.end());
		}
	}
	closedir(dirptr);
	return std::move(entitylist);
}

vector < entity > Filter(vector < entity > &&le, string match)
{
	vector < entity > ret;
	regex reg(match);
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

class AudioPlayer
{

	SLObjectItf soi = nullptr;
	SLEngineItf sei = nullptr;

	SLObjectItf soi_mix = nullptr;

	SLDataLocator_URI sdl_uri;
	SLDataFormat_MIME sdf_mime;
	SLDataSource sl_data_source;

	SLDataLocator_OutputMix sdl_om;
	SLDataSink sl_data_sink;

	SLObjectItf soi_player = nullptr;
	SLPlayItf spi = nullptr;
	SLSeekItf ssi = nullptr;
	SLVolumeItf svi = nullptr;

	SLmillibel max_level;
	
	string current_file;
	
	mutex mtx;

  public:

	 ~AudioPlayer()
	{
		if (soi_player != nullptr)
			(*soi_player)->Destroy(soi_player);
		(*soi_mix)->Destroy(soi_mix);
		(*soi)->Destroy(soi);
	}

	AudioPlayer()
	{
		create();
	}

	AudioPlayer(string file)
	{
		create();
		setSource(file);
	}

	void create()
	{
		// 创建引擎对象
		slCreateEngine(&soi, 0, NULL, 0, NULL, NULL);
		(*soi)->Realize(soi, false);
		(*soi)->GetInterface(soi, SL_IID_ENGINE, &sei);

		// 从引擎对象创建输出混响器对象
		(*sei)->CreateOutputMix(sei, &soi_mix, 0, NULL, SL_BOOLEAN_FALSE);
		(*soi_mix)->Realize(soi_mix, false);

	}

	void setSource(string file)
	{
	    mtx.lock();
		if (soi_player != nullptr)
		{
			(*soi_player)->Destroy(soi_player);
			soi_player = nullptr;
			spi=nullptr;
			ssi=nullptr;
			svi=nullptr;
		}
		current_file=file;
		// 配置源
		sdl_uri.locatorType = SL_DATALOCATOR_URI;
		sdl_uri.URI = (SLchar *) file.c_str();
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

		SLInterfaceID id[] = { SL_IID_SEEK, SL_IID_VOLUME };
		SLboolean req[] = { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE };
		// 创建音频播放器对象
		(*sei)->CreateAudioPlayer(sei, &soi_player, &sl_data_source,&sl_data_sink, 2, id, req);
		(*soi_player)->Realize(soi_player, false);
		(*soi_player)->GetInterface(soi_player, SL_IID_PLAY, &spi);
		(*soi_player)->GetInterface(soi_player, SL_IID_SEEK, &ssi);
		(*soi_player)->GetInterface(soi_player, SL_IID_VOLUME, &svi);

		(*svi)->GetMaxVolumeLevel(svi, &max_level);
		mtx.unlock();
	}

	void play()
	{
	    if(spi!=nullptr)
	    {
	        mtx.lock();
	        (*spi)->SetPlayState(spi, SL_PLAYSTATE_PLAYING);
	        mtx.unlock();
	    }
	}

	void pause()
	{
	    if(spi!=nullptr)
	    {
	        mtx.lock();
	        (*spi)->SetPlayState(spi, SL_PLAYSTATE_PAUSED);
	        mtx.unlock();
	    }
	}

	void stop()
	{
	    if(spi!=nullptr)
	    {
	        mtx.lock();
	        (*spi)->SetPlayState(spi, SL_PLAYSTATE_STOPPED);
	        mtx.unlock();
	    }
	}

	void seek(uint32_t ms)
	{
	    if(ssi!=nullptr)
	    {
	        mtx.lock();
	        (*ssi)->SetPosition(ssi, ms, SL_SEEKMODE_FAST);
	        mtx.unlock();
	    }
	}
	
	uint32_t getState()
	{
	    if(spi==nullptr)return SL_PLAYSTATE_STOPPED;
	    mtx.lock();
	    SLuint32 state;
	    (*spi)->GetPlayState(spi,&state);
	    mtx.unlock();
	    return state;
	}

	void setVolume(int16_t level)
	{
	    if(svi==nullptr)return;
	    mtx.lock();
		(*svi)->SetVolumeLevel(svi, level > max_level ? max_level : level);
		mtx.unlock();
	}
	
	int16_t getVolume()
	{
	    if(svi==nullptr)return -1;
	    mtx.lock();
	    SLmillibel ret;
		(*svi)->GetVolumeLevel(svi,&ret);
		mtx.unlock();
		return ret;
	}

	uint32_t getPosition()
	{
	    if(spi==nullptr)return 0;
	    mtx.lock();
		SLmillisecond position;
		(*spi)->GetPosition(spi, &position);
		mtx.unlock();
		return position;
	}

	uint32_t getDuration()
	{
	    if(spi==nullptr)return 0;
	    mtx.lock();
		SLmillisecond duration;
		(*spi)->GetDuration(spi, &duration);
		mtx.unlock();
		return duration;
	}
	
	string getFileName()
	{
	    return current_file;
	}
};

atomic_bool key_down_pause(false);
atomic_int page(0);
atomic_int play_mode(ORDER);
//atomic_int current_music(-1);
stack<int> music_play_history;//栈顶是当前歌曲

bool quit_flag=false;

void NextMusic(AudioPlayer& ap,const vector<entity>& audio_list)
{
    if(music_play_history.empty())return;
    if(play_mode==ORDER)
    {
        int next=music_play_history.top();
        music_play_history.push((next+1)%audio_list.size());
     }
     if(play_mode==RANDOM)
     {
         music_play_history.push(rand()%audio_list.size());
     }
     ap.setSource(audio_list[music_play_history.top()].path+"/"+audio_list[music_play_history.top()].file);
     ap.play();
}

void FrontMusic(AudioPlayer& ap,const vector<entity>& audio_list)
{
    if(music_play_history.size()<=1)return;
    music_play_history.pop();
    ap.setSource(audio_list[music_play_history.top()].path+"/"+audio_list[music_play_history.top()].file);
    ap.play();
}

void DisplayThread(AudioPlayer& ap,const vector<entity>& audio_list)
{
    int t=0;
    while(!quit_flag)
    {
        clrscr();
        uint32_t current=ap.getPosition()/1000;
        uint32_t end=ap.getDuration()/1000;
        int current_music=music_play_history.empty()?-1:music_play_history.top();
        
        cout<<"Playing:"<<(music_play_history.empty()?"":audio_list[current_music].file)<<endl;       
        cout<<"Time: ";
        ShowProgressBar(((double)current/end)*20,20);
        cout<<current/60<<":"<<current%60<<"/"<<end/60<<":"<<end%60<<endl;
        cout<<"Mode:"<<((play_mode==ORDER)?"order":"random")<<endl<<endl;
        
        cout<<"List["<<current_music+1<<"/"<<audio_list.size()<<"]:"<<endl;
        for(int i=0;i<10;++i)
        {
            if(page*10+i>=audio_list.size())break;
            if(current_music==page*10+i)cout<<"\033[33m";
            cout<<"["<<i<<"] "<<audio_list[page*10+i].file;
            if(current_music==page*10+i)cout<<"\033[37m";
            cout<<endl;
        }
        
        cout<<"Page:"<<page+1<<"/"<<ceil(audio_list.size()/10.)<<endl<<endl;
        
        cout<<"[P]暂停/播放  "<<"[S]停止播放  "<<"[F]上一页  "<<"[N]下一页  "<<"[0-9]选曲\n"<<"[K]上一曲  "<<"[L]下一曲  "<<"[M]模式  "<<"[Q]退出"<<endl;
        
         if(key_down_pause==false&&ap.getState()==SL_PLAYSTATE_PAUSED)
            NextMusic(ap,audio_list);
        usleep(250000);
    }
}

int main()
{
    string dir_path;
    cout<<"音乐文件夹路径:";
    cin>>dir_path;
    cout<<"扫描中...."<<endl;
	vector<entity> audio_list=Filter(FindFileInDir(dir_path,1),".*(\\.mp3|\\.ogg|\\.wav|\\.flac)");
	srand(time(nullptr));
	
	AudioPlayer ap;	
	
	thread display_thread(DisplayThread,std::ref(ap),std::ref(audio_list));
	
	char command;
    while(!quit_flag)
    {
        command=getch();
        if(command>='A'&&command<='Z')
            command+=32;
        switch(command)
        {
            case 'n':
            if(audio_list.size()>(page+1)*10)
                ++page;
            break;
            
            case 'f':
            if(page>0)
                --page;
            break;
            
            case 's':
            ap.stop();          
            break;
            
            case 'p':
            if(ap.getState()==SL_PLAYSTATE_PLAYING)
            {
                ap.pause();
                key_down_pause=true;
            }
            else
            {
                ap.play();
                key_down_pause=false;
            }                
            break;
            
            case 'q':
            quit_flag=true;
            break;
            
            case 'k':
            FrontMusic(ap,audio_list);
            break;
            
            case 'l':
            NextMusic(ap,audio_list);
            break;
            case 'm':
            ++play_mode;
            play_mode=play_mode%2;
            break;
            
            default:
            if(command>='0'&&command<='9')
            {
                int pos=page*10+command-'0';
                if(pos<audio_list.size())
                {
                    ap.stop();
                    ap.setSource(audio_list[pos].path+"/"+audio_list[pos].file);
                    music_play_history.push(pos);
                    ap.play();
                    key_down_pause=false;
                }
            }
        }
    }
    display_thread.join();
    clrscr();
    cout<<"已退出"<<endl;
    return 0;
}