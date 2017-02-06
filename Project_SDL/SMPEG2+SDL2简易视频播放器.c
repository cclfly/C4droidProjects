/**
  SDL2+SMPEG音视频播放测试代码
  单击屏幕暂停或播放
  上下滑动控制音量
  左右滑动控制进度(不能使用会崩溃)<谁能帮我找找原因QAQ>
  ps.因SMPEG自身的原因只能播放mpeg编码格式的视频或音频
  ps2.mp3是mpeg格式
  by 毛玉
**/
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <smpeg2/smpeg.h>

int w = 0, h = 0;
char temp[127] = { 0 };

//char *file = "/sdcard/kirikiri2/Sactter樱吹雪~千年之恋~[无压]/op.mpg";
//char *file="/sdcard/音乐/Adios Eden.mp3";
char *file="/storage/sdcard1/kgmusic/download/Tk From 凛として时雨 - Unravel.mp3";
typedef enum{
	STOP=0,
	PLAYING,
	PAUSE
}state;

typedef enum
{
	NUL=0,
	CHANGEVOLUME,
	CHANGEPLAYTIME
}eventtype;

SDL_Window *win = NULL;
SDL_Renderer *ren = NULL;
SDL_Texture *frameimage = NULL;
SDL_mutex *mutex=NULL;
SDL_Rect rect = { 0, 0, 0, 0 };

SMPEG_Frame *frame = NULL;
int current_frame = 0;
int offset = 0;
int current_state=0;
int current_time=0;
int current_volume=50;
int changing_volume=0;
float changing_time=0;
int current_event=0;

//文字转贴图
SDL_Texture *makeText(SDL_Renderer * ren, const char *text, int size, int rgba)
{
	SDL_Surface *temp = NULL;
	SDL_Texture *finish = NULL;
	TTF_Font *font=NULL;
	SDL_Color text_color = { (rgba&0xff000000)>>23, (rgba&0x00ff0000)>>15, (rgba&0x0000ff00)>>7, rgba&0x000000ff };
	TTF_Init();
	font = TTF_OpenFont("/system/fonts/DroidSansFallback.ttf", size);//打开字体
	temp = TTF_RenderUTF8_Solid(font, text, text_color);//渲染文本
	finish = SDL_CreateTextureFromSurface(ren, temp);
	SDL_FreeSurface(temp);
	TTF_CloseFont(font);//关闭字体
	TTF_Quit();
	return finish;
}
//显示文字
void nshowText(SDL_Renderer * ren, const char *msg, int size,int x,int y,int rgba)
{
	SDL_Rect tr = { 0, 0, 0, 0 };
	SDL_Texture *t = makeText(ren, msg, size, rgba);
	SDL_QueryTexture(t, NULL, NULL, &tr.w, &tr.h);
	if(x==-1)
	tr.x = (w - tr.w) / 2;
	else
	tr.x=x;
	if(y==-1)
	tr.y = (h - tr.h) / 2;
	else
	tr.y=y;
	SDL_RenderCopy(ren, t, NULL, &tr);
	SDL_DestroyTexture(t);
}
//显示文字到屏幕中间(在渲染过程中使用会闪屏)
void showText(SDL_Renderer *ren,const char *msg,int size)
{
	SDL_RenderClear(ren);
	nshowText(ren,msg,size,-1,-1,0xffffffff);
	SDL_RenderPresent(ren);
}
//判断文件是否存在
int isFile(const char *file)
{
	int was = 0;
	FILE *t = fopen(file, "rb");
	if (t != NULL)
	{
		was = 1;
		fclose(t);
	}
	return was;
}
//视频播放的回调函数
void callback(void *data, SMPEG_Frame * _frame)
{
	if (_frame->image == NULL)
		exit(-1);
	frame = _frame;
	offset = ((_frame->image_height - _frame->h) + 2) * _frame->image_width;//This is magic,do not change.╮(╯▽╰)╭ 
	current_frame++;
}
//退出程序时会被调用的函数
void Quit()
{
	SDL_DestroyMutex(mutex);
	SDL_DestroyTexture(frameimage);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}
//事件循环
double x=0,y=0;
int dx=0,dy=0;
void loopEvent(SDL_Event *event,SMPEG *SV)
{

	while(SDL_PollEvent(event))
	{
		switch(event->type)
		{
			case SDL_FINGERUP://手指松开
			if(current_event==NUL)
			{
			SMPEG_pause(SV);
			if(current_state!=PAUSE)
			current_state=PAUSE;
			else
			current_state=PLAYING;
			}
			dx=0;dy=0;x=0;y=0;
			current_volume=changing_volume;
			if(current_event==CHANGEPLAYTIME)
			SMPEG_skip(SV,changing_time);
			current_event=NUL;
			break;
			
			case SDL_FINGERDOWN://手指放下
			x=event->tfinger.x;
			y=event->tfinger.y;
			changing_volume=current_volume;
			break;
			
			case SDL_FINGERMOTION://手指移动
			dx=(event->tfinger.x-x)*100;
			dy=(y-event->tfinger.y)*100;
			if((dy>3||dy<-3)&&current_event!=CHANGEPLAYTIME)
			{
				current_event=CHANGEVOLUME;
				if(dy>3)
				changing_volume=current_volume+dy-3;				
				if(dy<-3)
				changing_volume=current_volume+dy+3;
				if(current_volume>100)
					current_volume=100;
				if(changing_volume>100)
					changing_volume=100;
				if(current_volume<0)
					current_volume=0;
				if(changing_volume<0)
				changing_volume=0;
				SMPEG_setvolume(SV,changing_volume);
			}
			if((dx>3||dx<-3)&&current_event!=CHANGEVOLUME)
			{
				current_event=CHANGEPLAYTIME;
				changing_time=current_time+dx;	
			}
		}
	}
}

//主函数
int main(int argc, char **argv)
{
	SMPEG *SV = NULL;   //SMPEG_Video
	SMPEG_Info si;   //视频信息结构体
	SDL_Event event;

	atexit(Quit);   //设置退出时会被调用的函数
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);//初始化视频,音频系统
	win = SDL_CreateWindow("←_←", 10, 10, 500, 500, SDL_WINDOW_SHOWN);
	ren =SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC  | SDL_RENDERER_TARGETTEXTURE);
	SDL_GetWindowSize(win, &w, &h);//获取窗口大小
	mutex = SDL_CreateMutex();//创建互斥锁
	showText(ren, "Loading...", 100);//显示Loading...
	if (isFile(file))
		SV = SMPEG_new(file, &si, 1);
	else
	{
		showText(ren, "文件或路径不存在！", 80);
		SDL_Delay(3000);
		exit(-1);
	}
	if (si.has_video == 0 && strstr(si.audio_string, "0kbit/s 16000Hz"))
	{
		showText(ren, "仅支持MPEG编码的音频和视频", 70);
		SDL_Delay(3000);
		exit(-1);
	}

	if (si.has_video == 1)
	{
		frameimage =SDL_CreateTexture(ren, SDL_PIXELFORMAT_YV12,SDL_TEXTUREACCESS_STREAMING, si.width,si.height);//创建YV12贴图
		SMPEG_setdisplay(SV, callback, NULL, mutex);//设置播放回调函数
		SMPEG_renderFinal(SV);//This is magic,do not change. 23333
		rect.w = w;
		rect.h = h;
	}
	SMPEG_setvolume(SV,current_volume);//设置声音大小
	SMPEG_play(SV);//开始播放
	current_state=PLAYING;
	while (si.current_time < si.total_time)
	{
		loopEvent(&event,SV);
		SDL_RenderClear(ren);
		if (si.has_video == 1)
		{
			SDL_LockMutex(mutex);
			SDL_UpdateTexture(frameimage, NULL, (frame->image + offset),frame->image_width);//更新播放贴图
			SDL_UnlockMutex(mutex);
		}
		if(current_state!=PAUSE)
		{
		 SMPEG_getinfo(SV, &si);//获取视频信息
		 current_time=si.current_time;
		sprintf(temp,"Time:%.2llf/%.2llf(%.1llf%%)    FPS:%.2llf   SDL2+SMPEG音视频播放测试",si.current_time, si.total_time,(si.current_time / si.total_time) * 100, si.current_fps);
		}
		SDL_RenderCopy(ren, frameimage, NULL, &rect);//显示视频帧
		nshowText(ren,temp,35,0,0,0xff0000ff);//显示时间,fps信息
		if (si.has_video == 0 && si.has_audio == 1)
		{
				nshowText(ren,file,50,-1,80,0xffffffff);
		}
		if(current_state==PAUSE)
		nshowText(ren,"暂停",100,-1,-1,0xffffffff);
		if(current_event==CHANGEVOLUME)
		{
			sprintf(temp,"声音:%d",changing_volume);
			nshowText(ren,temp,60,-1,-1,0xff00ffff);
		}
		if(current_event==CHANGEPLAYTIME)
		{
			sprintf(temp,"时间:%d",changing_time);
			nshowText(ren,temp,60,-1,-1,0xff00ffff);
		}
		SDL_RenderPresent(ren);
		SDL_Delay(33);	
	}
	SMPEG_stop(SV);//停止播放
	SMPEG_delete(SV);//释放视频所占内存
	SDL_CloseAudio();
	exit(0);
}