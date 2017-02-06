//项目:水波纹测试
//操作:滑动屏幕产生水波,退出在左上角
//PS:建议开启编译器-O2优化，不然卡死你丫的
//by Mao-Yu
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#define readArray(_Array,_x,_y,_width) (_Array)[(_y)*(_width)+(_x)]

#if _cplusplus<201103L
#define nullptr NULL
#endif

using namespace std;

static int width = 1280, height = 720;
static SDL_Window *win = nullptr;
static SDL_Renderer *ren = nullptr;
static int rad=35;//半径
static int energy=64;//能量

const char *init(const char* title,int w,int h)
{
	SDL_Init(SDL_INIT_VIDEO);
	if ((win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, w, h,SDL_WINDOW_SHOWN)) == nullptr)//创建窗口
		return SDL_GetError();
	if ((ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC)) == nullptr)//创建渲染器，使用硬件加速和垂直同步
		return SDL_GetError();
	SDL_GetWindowSize(win, &width, &height);
}

void quit()//退出函数
{
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}

SDL_Texture *makeText(SDL_Renderer * ren, const char *text, int size, int rgba)//生成文字(SDL_Surface)
{
	SDL_Surface *temp = nullptr;
	SDL_Texture *finish = nullptr;
	TTF_Font *font=nullptr;
	SDL_Color text_color = { (Uint8)((rgba&0xff000000)>>23), (Uint8)((rgba&0x00ff0000)>>15), (Uint8)((rgba&0x0000ff00)>>7), (Uint8)(rgba&0x000000ff) };//从rgba分离r,g,b,a值
	TTF_Init();
	font = TTF_OpenFont("/system/fonts/DroidSansFallback.ttf", size);//打开字体
	temp = TTF_RenderUTF8_Solid(font, text, text_color);//渲染文字
	finish = SDL_CreateTextureFromSurface(ren, temp);
	SDL_FreeSurface(temp);
	TTF_CloseFont(font);
	TTF_Quit();
	return finish;
}

void nshowText(SDL_Renderer * ren, const char *msg, int size,int x,int y,int rgba)//显示字符串到屏幕，需在渲染循环中使用
{
	SDL_Rect tr = { 0, 0, 0, 0 };
	SDL_Texture *t = makeText(ren, msg, size, rgba);
	SDL_QueryTexture(t, NULL, NULL, &tr.w, &tr.h);//获取贴图大小
	if(x==-1)//x居中
		tr.x = (width - tr.w) / 2;
	else
		tr.x=x;
	if(y==-1)//y居中
		tr.y = (width - tr.h) / 2;
	else
		tr.y=y;
	SDL_RenderCopy(ren, t, NULL, &tr);
	SDL_DestroyTexture(t);
}

class Wave//水波类
{
  public:
	Wave(SDL_Surface * in, SDL_Renderer * _ren):ren(_ren)
	{
		if (in == nullptr || ren == nullptr)
		{
			throw invalid_argument(string("参数无效"));
			  return;
		}
		in = SDL_ConvertSurfaceFormat(in, SDL_PIXELFORMAT_RGBA8888, 0);//转换格式，匹配贴图格式
		w = in->w;
		h = in->h;
		pixels_source = (Uint32*)malloc(w * h*sizeof(Uint32));//原像素数组
		pixels_out = (Uint32*)malloc(w * h*sizeof(Uint32));//输出像素数组
		wavebuf1 = (Sint32*)malloc(w * h*sizeof(Sint32));//波浪缓存区1
		wavebuf2 = (Sint32*)malloc(w * h*sizeof(Sint32));//波浪缓存区2
		memcpy(pixels_source, in->pixels, w * h * sizeof(Uint32));//从SDL_Surface中复制像素至原像素数组
		memset(wavebuf1, 0, w * h*sizeof(Sint32));//清零缓存区1
		memset(wavebuf2, 0, w * h*sizeof(Sint32));//清零缓存区2
		out=SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_STREAMING, w, h);//创建空白贴图
		SDL_FreeSurface(in);//in已无用，释放
	}
	void setSource(int x, int y, int r, Sint32 e)//设置波源
	{
		if ((x+r)>w || (y+r)>h|| (x-r)<0|| (y-r)<0) return; //范围检测
		for (int i = x-r; i <x+ r; i++)
			for (int j = y-r; j < y+r; j++)
				if (((i - x) * (i - x) + (j - y) * (j - y)) <=(r * r))
					readArray(wavebuf1,i,j, w-2) -=e;
	}	
	void next()
	{
		for (int i = w; i < w * h - w; i++)//波浪扩散
		{
			wavebuf2[i] =((wavebuf1[i - 1] + wavebuf1[i + 1] + wavebuf1[i - w] +wavebuf1[i + w]) >> 1) - wavebuf2[i];//扩散
			wavebuf2[i] -= (wavebuf2[i] >> 5);//阻力
		}
		Sint32 *t = wavebuf2;//交换缓存区
		wavebuf2 = wavebuf1;
		wavebuf1 = t;
	}
	void render()
	{
		int xoff = 0, yoff = 0;
		int k = w;
		for (int i = 1; i < h; i++)
			for (int j = 1; j < w-1; j++)
			{
				xoff = wavebuf1[k - 1] - wavebuf1[k + 1];//计算x偏移值
				yoff = wavebuf1[k - w] - wavebuf1[k + w];//计算y偏移值
				if (i + yoff < 0){k++;continue;}//范围判断
				if (i + yoff > h){k++;continue;}
				if (j + xoff < 0){k++;continue;}
				if (j + xoff > w){k++;continue;}
				readArray(pixels_out,j,i,w)=readArray(pixels_source,j+xoff,i+yoff,w);//复制并偏移像素至输出像素数组
				k++;
			}		
		SDL_UpdateTexture(out, nullptr, pixels_out, w*sizeof(Uint32));//更新贴图画面
	}	
	void renderWave()
	{
		render();
		next();
	}
	inline SDL_Texture *getTexture()
	{
		return out;
	}
	inline int getW(){return w;}
	inline int getH(){return h;}
	~Wave()
	{
		free(wavebuf1);
		free(wavebuf2);
		free(pixels_source);
		free(pixels_out);
		SDL_DestroyTexture(out);
	}
  private:
	Sint32 *wavebuf1, *wavebuf2;
	Uint32 w, h;
	int x, y;
	Uint32 *pixels_out, *pixels_source;
	SDL_Texture *out;
	SDL_Renderer *ren;
};

bool flag=false;

void EventLoop(SDL_Event &e,Wave& wave)
{

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_FINGERMOTION)
				wave.setSource(e.tfinger.x*wave.getW(),e.tfinger.y*wave.getH(),rad,energy);
		if(e.type==SDL_FINGERDOWN)
			if(e.tfinger.y>0&&e.tfinger.y<0.05&&e.tfinger.x>0&&e.tfinger.x<0.05)
				flag=true;
	}
}

int main()
{
	SDL_Event event;
	char buffer[1024];
	atexit(quit);
	const char *err = init("水波测试",width,height);
	if (err == nullptr)
		cerr << err << endl;
	SDL_Surface* img=IMG_Load("/storage/sdcard0/DCIM/Camera/1431022497501.jpg");
	if(img==nullptr)return -1;
	SDL_SetWindowSize(win,img->w,img->h);
	Wave wave(img,ren);
	SDL_Texture *tex=wave.getTexture();
	SDL_FreeSurface(img);
	int e=0,s=0,ms=0;
	while(!flag)
	{
		EventLoop(event,wave);
		s=SDL_GetTicks();
		wave.renderWave();
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren,tex,nullptr,nullptr);
		sprintf(buffer,"MS:%d  FPS:%.2lf Rad:%d  Energy:%d",ms,1000./ms,rad,energy);
		nshowText(ren,buffer,50*(width/1080.),0,0,0x00ff0000);
		sprintf(buffer,"Width:%d  Height:%d  Screen:%d╳%d",width,height,wave.getW(),wave.getH());
		nshowText(ren,buffer,50*(width/1080.),0,height-(64*(width/1080.)),0x00ff0000);
		SDL_RenderPresent(ren);
		e=SDL_GetTicks();
		ms=e-s;
	}
}