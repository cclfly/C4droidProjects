#include "msocket.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>

using namespace std;
using namespace msocket;

static int width = 1280, height = 720;
static SDL_Window *win = nullptr;
static SDL_Renderer *ren = nullptr;

const char *init(const char* title,int w,int h)
{
	SDL_Init(SDL_INIT_VIDEO);
	if ((win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, w, h,SDL_WINDOW_SHOWN)) == nullptr)
		return SDL_GetError();
	if ((ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC)) == nullptr)
		return SDL_GetError();
	SDL_GetWindowSize(win, &width, &height);
	return nullptr;
}

void quit()
{
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}

SDL_Texture* LoadTextureFromNet(SDL_Renderer *ren,const char* host)
{
	string get_data;
	try
	{
		get_data=get(host);
	}
	catch(string e)
	{
		throw e;
		return nullptr;
	}
	SDL_RWops *image=SDL_RWFromConstMem(get_data.c_str(),get_data.size());
	SDL_Texture *bg=IMG_LoadTexture_RW(ren,image,0);
	SDL_FreeRW(image);
	return bg;
}

int main()
{
		if(init("msocket+SDL2",1080,1920)!=nullptr)return -1;
		atexit(quit);
		SDL_Init(SDL_INIT_VIDEO);
		SDL_Texture* bg=LoadTextureFromNet(ren,"www.mao-yu.net/image/BG/yande-160667-dress-fixed-flandre_scarlet-izayoi_sakuya-kinokonomi-konomi-macchatei_koeda-thighhighs-touhou.jpg");
		SDL_Rect r{0,0};
		SDL_QueryTexture(bg,0,0,&r.w,&r.h);
		double rate=(double)width/r.w;
		r.w*=rate;
		r.h*=rate;
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren,bg,nullptr,&r);
		SDL_RenderPresent(ren);
		SDL_DestroyTexture(bg);
		SDL_Delay(5000);
}