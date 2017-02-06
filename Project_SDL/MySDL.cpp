#include <SDL.h>
#include <SDL_image.h>

int _tmain(int argc, char* argv[])
{
	SDL_Surface *win = NULL;
	SDL_Init(SDL_INIT_EVERYTHING);
	win = SDL_CreateWindow("Test", 100, 100, 200, 200, SDL_WINDOW_SHOWN);


	SDL_DestroyWindow(win);
	return 0;
}