#include <stdio.h>
#include <conio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

SDL_Renderer *Renderer;


void showtext(char *text,
size_t size,
SDL_Color c,
SDL_Rect Box
)
{
	TTF_Font *font;
	SDL_Surface *font_sf ;
	SDL_Texture *Texture;
	TTF_Init();
	font = TTF_OpenFont("/system/fonts/DroidSansFallback.ttf", size);

font_sf = TTF_RenderUTF8_Blended(font,text, c);
Texture = SDL_CreateTextureFromSurface(Renderer, font_sf);

SDL_QueryTexture(Texture, NULL, NULL, &Box.w, &Box.h);
SDL_RenderClear(Renderer);
SDL_RenderCopy(Renderer, Texture, NULL, &Box);
SDL_RenderPresent(Renderer);

SDL_FreeSurface(font_sf);
TTF_CloseFont(font);
TTF_Quit();
}

int main (int argc,char ** argv)
{
	SDL_Window *win;
//	SDL_Surface *sf;
TTF_Init();
	
	win = SDL_CreateWindow("SDL_Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 480, 800, SDL_WINDOW_SHOWN);
	
    Renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);


SDL_Rect b={0};
b.x=20;
b.y=86;

SDL_Color c;
c.r=25;
c.g=205;
c.b=255;
c.a=6;
char n[20]={0};
SDL_Event event; 
while (1)
while (SDL_PollEvent(&event))
{
	 sprintf (n,"%f",event.tfinger.x);
     showtext(n,25,c,b);
}

while (1);
}