#include <iostream>
#include <SDL/SDL.h>
int main(int argc,char*argv[])
{
	try{
		if (SDL_Init(SDL_INIT_EVERYTHING)==-1)
		{
			throw "Could not initialize SDL!";
		}
	}
	catch (const char *s)
	{
		std::cerr<<s<<std::endl;
		return -1;
	}
	std::cout<<"SDL initialized. \n";
	//SDL_Quit();
	atexit(SDL_Quit);
	return 0;
}