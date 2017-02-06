#include "SDL/SDL.h"
#include "mygame.h"
SDL_Event event;
SDL_Surface *screen = 0;
SDL_Surface *dot = 0;
const int SCREEN_WIDHT = 480;
const int SCREEN_HEIGHT = 840;
const int SCREEN_BPP = 32;
bool quit = true;
class game
{
  private:
	SDL_Rect rect[5];
	SDL_Rect a;
	int x, y, vx;
	int wx, wy[5] = { 850, 850, 850, 850, 850 }, wv;
	const int wh = 30;
	const int ww = 150;
	const int vy = 2;
  public:
	game();
	void input();
	void move();
	void show();
	void wall();
	bool check(SDL_Rect a, SDL_Rect b);
};

game::game()
{
	x = SCREEN_WIDHT / 2;
	y = SCREEN_HEIGHT / 5;
	vx = 0;
	wx = 0;
	dot = load_image("dots.png");

}

void game::input()
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:
			vx -= 5;
			break;
		case SDLK_RIGHT:
			vx += 5;
			break;
		}
	}
	else if (event.type == SDL_KEYUP)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:
			vx += 5;
			break;
		case SDLK_RIGHT:
			vx -= 5;
			break;
		}
	}
}

void game::show()
{
	game::wall();

	SDL_FillRect(screen, &rect[0],
				 SDL_MapRGB(screen->format, 0xff, 0xff, 0xff));

	SDL_FillRect(screen, &rect[1],
				 SDL_MapRGB(screen->format, 0xff, 0xff, 0xff));

	SDL_FillRect(screen, &rect[2],
				 SDL_MapRGB(screen->format, 0xff, 0xff, 0xff));
	 a.x = x;
	a.y = y;
	a.w = 50;
	a.h = 50;
	SDL_FillRect(screen, &a, SDL_MapRGB(screen->format, 0xff, 0xff, 0xff));
	apply_surface(x, y, dot, screen);
}

void game::move()
{
	x += vx;
	if ((x > (SCREEN_WIDHT - 50)) || (x < 0))
	{
		x -= vx;
	}
	y += vy;
	if (y < 0 || y > SCREEN_HEIGHT)
	{
		quit = false;
	}
	for (int i = 0; i < 5; i++)
	{
		wy[i] -= vy;
		game::check(a, rect[i]);
	}
}

void game::wall()
{
	rect[0].x = 0;
	rect[0].y = wy[0];
	rect[0].w = ww;
	rect[0].h = wh;

	rect[1].x = 180;
	rect[1].y = wy[1] + 300;
	rect[1].w = ww;
	rect[1].h = wh;

	rect[2].x = 350;
	rect[2].y = wy[2] + 600;
	rect[2].w = ww;
	rect[2].h = wh;


	for (int i = 0; i < 5; i++)
	{
		if (rect[i].y < 0)
		{
			wy[i] += 850;
		}
	}

}

bool game::check(SDL_Rect a, SDL_Rect b)
{
	if ((((a.y) + 50) > (b.y))
		&& (((a.x) >= (b.x) - 50 && (a.x) <= ((b.w) + (b.x)))))
	{
		y -= 2 * vy;
		if (b.y < a.y)
			y += 2 * vy;
	}
	return true;
}







int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	screen =
		SDL_SetVideoMode(SCREEN_WIDHT, SCREEN_HEIGHT, SCREEN_BPP,
						 SDL_SWSURFACE);
	game games;
	while (quit)
	{
		while (SDL_PollEvent(&event))
		{
			games.input();
		}
		SDL_FillRect(screen, &screen->clip_rect,
					 SDL_MapRGB(screen->format, 0, 0, 0));
		games.move();
		games.show();
		SDL_Flip(screen);
	}
}