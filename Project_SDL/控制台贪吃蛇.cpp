#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "string"
//#include "initialization.h"
SDL_Surface* screen=0;
SDL_Surface* background=0;
SDL_Surface* dots=0;
SDL_Surface* a=0;
SDL_Surface* b=0;
SDL_Surface* c=0;
const int SCREEN_HEIGHT = 320;
const int SCREEN_WIDHT = 480;
const int BPP = 32;
SDL_Event event;
class dot
{
  private:
	int x;
	int y;
	int xvel;
	int yvel;
  public:
	  dot();
	void handle_input();
	void move();
	void show();
};
dot::dot()
{
	x = 0;
	y = 0;
	xvel = 0;
	yvel = 0;
}
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
void dot::handle_input()
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_UP:
			yvel -= 1;
			break;
		case SDLK_DOWN:
			yvel += 1;
			break;
		case SDLK_LEFT:
			xvel -= 1;
			break;
		case SDLK_RIGHT:
			xvel += 1;
			break;
		}
	}
	else if (event.type == SDL_KEYUP)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_UP:
			yvel += 1;
			break;
		case SDLK_DOWN:
			yvel -= 1;
			break;
		case SDLK_LEFT:
			xvel += 1;
			break;
		case SDLK_RIGHT:
			xvel -= 1;
			break;
		}
	}
}

void dot::move()
{
	x += xvel;
	if ((x < 0) || ((x + 20) > SCREEN_WIDHT))
	{
		x -= xvel;
	}
	y += yvel;
	if ((y < 0) || ((y + 20) > SCREEN_HEIGHT))
	{
		y -= yvel;
	}
}

void dot::show()
{
	apply_surface(x, y, dots, screen);
}

bool init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_SetVideoMode(SCREEN_WIDHT, SCREEN_HEIGHT, BPP, SDL_SWSURFACE);
}

bool load_files()
{
	dots = load_image("dots.png");
	b = load_image("b.png");
}

bool show_screen()
{
	apply_surface(0, 0, b, screen);
}

int main(int argc, char *args[])
{
	bool quit;
	dot mydot;
	init();
	load_files();
	 while (quit == false)
	{
		while (SDL_PollEvent(&event))
		{
			mydot.handle_input();
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
			mydot.move();
			show_screen();
			mydot.show();
			SDL_Flip(screen);
			SDL_Delay(20);
		}
	}
	SDL_FreeSurface(b);
	SDL_FreeSurface(dots);
	SDL_Quit();
}