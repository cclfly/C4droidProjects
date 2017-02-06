#include <iostream>
#include <SDL/SDL.h>
using namespace std;

void doSomeLoopThings()
{
	cout<<".";
	return;
}

void pressESCtoQuit()
{
	bool gameOver=false;
	while (gameOver==false)
	{
		SDL_Event gameEvent;
		//SDL_PollEvent(&gameEvent);
		while (SDL_PollEvent(&gameEvent)!=0)//if (&gameEvent != 0)
		{
			if (gameEvent.type == SDL_QUIT)
			{
				gameOver=true;
			}
			if (gameEvent.type == SDL_KEYDOWN)
			{
				if (gameEvent.key.keysym.sym == SDLK_ESCAPE)
				{
					gameOver=true;
				}
				if (gameEvent.key.keysym.sym == 'e')
				{
					gameOver=true;
				}
			}
		}
		doSomeLoopThings();
	}
	return;
}
	

int main(int argc,char *argv[])
{
	try {
		if (SDL_Init(SDL_INIT_VIDEO)==-1)
		{
			throw SDL_GetError();
		}
	}
	catch (const char *s)
	{
		cerr<<s<<endl;
		return -1;
	}
	atexit(SDL_Quit);
	
	SDL_SetVideoMode(409,678,32,SDL_SWSURFACE);
	
	pressESCtoQuit();
	
	return 0;
}