#include <SDL/SDL.h>
#include <SDL_image.h>
#include <string>
#include <stdlib.h>
#include <time.h>

SDL_Surface *load_image(std::string filename)
{
	SDL_Surface *loadedimage = 0;
	SDL_Surface *optimizedimage = 0;
	loadedimage = IMG_Load(filename.c_str());
	if (loadedimage != 0)
	{
		optimizedimage = SDL_DisplayFormat(loadedimage);
		SDL_FreeSurface(loadedimage);
	}
	
	return optimizedimage;
}

void apply_surface(int x, int y, SDL_Surface * source,
				   SDL_Surface * destination,SDL_Rect *clip=0)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(source, clip, destination, &offset);
}
int getrand(int n)
{
	srand(time(NULL));
	unsigned x=rand()%n;
	return x;
}