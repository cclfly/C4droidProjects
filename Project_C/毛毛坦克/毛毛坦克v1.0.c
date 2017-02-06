#include <stdio.h>
#include <unistd.h>
#include <conio.h>
#include <sys/ioctl.h>
#include <termios.h>

#define GET_FB_PIXELS(_w,_x,_y) ((_w)->fb[(_y)*(_w)->w+(_x)])

typedef struct
{
	int w, h;
	uint32_t *fb;
} window_t;

typedef struct
{
	int x, y;
	int w, h;
} rect_t;

typedef struct
{
	int w,h;
	uint32_t* pixels;
}bitmap_t;

window_t *create_window(int w, int h)
{
	window_t *win = (window_t *) malloc(sizeof(window_t));

	win->w = w;
	win->h = h;
	win->fb = (uint32_t *) malloc(sizeof(uint32_t) * win->w * win->h);
	memset(win->fb, 0, sizeof(uint32_t) * win->w * win->h);

	return win;
}

void clear(window_t * win)
{
	memset(win->fb, 0, sizeof(uint32_t) * win->w * win->h);
}

void free_window(window_t * win)
{
	clrscr();
	free(win->fb);
	free(win);
}

void display(window_t * win)
{
	for (int y = 0; y < win->h; ++y)
	{
		for (int x = 0; x < win->w; ++x)
		{
			uint32_t pixel = GET_FB_PIXELS(win, x, y);
			if (pixel == 0)
				printf(" ");
			else
				printf("%s", &pixel);
		}
		putchar('\n');
	}
	fflush(stdout);
	clear(win);
}

void draw_pixel(window_t * win, int x, int y, const char *pixel)
{
	if (x >= 0 && x < win->w && y >= 0 && y < win->h)
	{
		GET_FB_PIXELS(win, x, y) = *(uint32_t *) pixel;
	}
}

void draw_rect(window_t * win, rect_t * rect, const char *pixel)
{
	for (int y = rect->y; y < rect->y + rect->h; ++y)
		for (int x = rect->x; x < rect->x + rect->w; ++x)
		{
			if (x >= 0 && x < win->w && y >= 0 && y < win->h)
				GET_FB_PIXELS(win, x, y) = *(uint32_t *) pixel;
		}
}

void draw_pixels(window_t * win, rect_t * rect, const char **pixels)
{
	const char** p=pixels;
	int xstart=rect->x,xend=rect->x+rect->w;
	int ystart=rect->y,yend=rect->y+rect->h;
	
	
	for (int y = ystart; y < yend; ++y)
		for (int x = xstart; x < xend; ++x)
		{
			if (x >= 0 && x < win->w && y >= 0 && y < win->h)
				GET_FB_PIXELS(win, x, y) = *(uint32_t *) *p++;
		}
}

#include <math.h>
#include <stdlib.h>

window_t *win;

void quit()
{
	free_window(win);
}

typedef enum
{
	UP,DOWN,
	LEFT,RIGHT
}Director;

typedef struct
{
	rect_t m_rect;
	char m_color;//未实现
	Director m_director;
	const char** m_bitmaps[4];
}tank_t;

tank_t* tank_create()
{
	static rect_t rect_tank={0,0,3,3};
	static const char* tank_bitmap_up[]={" ","#"," ","#","#","#","#","#","#"};
	static const char* tank_bitmap_down[]={"#","#","#","#","#","#"," ","#"," "};
	static const char* tank_bitmap_left[]={" ","#","#","#","#","#"," ","#","#"};
	static const char* tank_bitmap_right[]={"#","#"," ","#","#","#","#","#"," "};
	
	
	tank_t* tank=(tank_t*)malloc(sizeof(tank_t));
	memset(tank,0,sizeof(tank_t));
	
	memcpy(&tank->m_rect,&rect_tank,sizeof(rect_t));
	tank->m_director=UP;
	tank->m_bitmaps[UP]=tank_bitmap_up;
	tank->m_bitmaps[DOWN]=tank_bitmap_down;
	tank->m_bitmaps[LEFT]=tank_bitmap_left;
	tank->m_bitmaps[RIGHT]=tank_bitmap_right;
}

void tank_delete(tank_t* tank)
{
	free(tank);
}

void tank_draw(tank_t* tank)
{
	draw_pixels(win,&tank->m_rect,tank->m_bitmaps[tank->m_director]);
}

tank_t* player_tank;
char quit_flag = 0;

void event_handle()
{
	int key=0;
	
	while(kbhit())
	{
		key=getch();
		switch(key)
		{
			case 'w':
			player_tank->m_director=UP;
			player_tank->m_rect.y-=1;
			break;
			
			case 's':
			player_tank->m_director=DOWN;
			player_tank->m_rect.y+=1;
			break;
		
			case 'a':
			player_tank->m_director=LEFT;
			player_tank->m_rect.x-=1;
			break;
			
			case 'd':
			player_tank->m_director=RIGHT;
			player_tank->m_rect.x+=1;
			break;
			
			case 'q':
			quit_flag=1;
		}
	}
}

int main()
{
	win = create_window(20, 20);
	atexit(quit);
	player_tank=tank_create();
	
	while(!quit_flag)
	{
		clrscr();
		event_handle();
		tank_draw(player_tank);
		display(win);
		usleep(100000);
	}
}