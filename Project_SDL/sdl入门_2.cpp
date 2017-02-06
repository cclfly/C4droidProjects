#include <iostream>
#include <SDL/SDL.h>
void beginSDL()
{
	if (SDL_WasInit(SDL_INIT_EVERYTHING)!=0)
	{
		std::cout<<"SDL is already running.\n";
		return;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING)==-1)
	{
		throw "Unable to init SDL!";
	}
	std::cout<<"SDL is running successfully.\n";
	return;
}
void endSDL()
{
	if (SDL_WasInit(SDL_INIT_EVERYTHING)==0)
	{
		std::cout<<"SDL was NOT running!\n";
		return;
	}
	SDL_Quit();
	std::cout<<"SDL_Quit successfully.\n";
	return;
}
int main(int argc,char*argv[])
{
	try {
		beginSDL();
	}
	catch (const char *s)
	{
		std::cout<<s<<std::endl;
		return -1;
	}
	std::cout<<SDL_WasInit(SDL_INIT_EVERYTHING)<<std::endl;
	
	atexit(endSDL);
	return 0;
}