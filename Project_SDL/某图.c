#include <SDL2/SDL.h>
#include <math.h>

SDL_Window *win = nullptr;
SDL_Renderer *ren = nullptr;
int width = 1080, height = 1920;


struct Point
{
	double x, y;
};

const char *init()
{
	SDL_Init(SDL_INIT_VIDEO);
	if ((win =
		 SDL_CreateWindow("贝塞尔曲线test", SDL_WINDOWPOS_CENTERED,
						  SDL_WINDOWPOS_CENTERED, 500, 500,
						  SDL_WINDOW_SHOWN)) == nullptr)
		return SDL_GetError();
	if ((ren =
		 SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED)) == nullptr)
		return SDL_GetError();
}

void quit()
{
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}

long A(int down, int up)
{
	long s = 1;
	for (int i = down, k = 1; k <= up; k++, i--)
		s *= i;
	return s;
}

long C(int down, int up)
{
	return A(down, up) / A(up, up);
}


void BesselCurve(Point * s,int n,double t, Point * out)
{
	double p = 0.0, p2 = 0.0;
	for (int i = 0; i < n; i++)
	{
		p = pow(t, i);
		p2 = pow((1 - t), n - i);
		out->x += C(n, i) * (s + i)->x * p2 * p;
		out->y += C(n, i) * (s + i)->y * p2 * p;
	}
}

void DrawLine(SDL_Renderer * ren, int x1, int y1, int x2, int y2)
{
	if (x2 < x1)
	{
		int t = x2;
		x2 = x1;
		x1 = t;
		t = y2;
		y2 = y1;
		y1 = t;
	}
	double k = (y1 - y2) / (double)(x1 - x2);
	for (int i = x1; i <= x2; i++)
		SDL_RenderDrawPoint(ren, i, k * (i - x1) + y1);
}

int main()
{
//	FILE* f=fopen("/sdcard/log.txt","w");
	Point p[] = { {1, 1}, {597, 1900} };
	int length = 2;
	Point result[2];
	init();
	SDL_GetWindowSize(win, &width, &height);
	SDL_RenderClear(ren);
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	for (double i = 0; i < 1; i += 0.00001)
	{
		BesselCurve(p,length, i, &result[0]);
		BesselCurve(p, length, i + 0.00001, &result[1]);
//		SDL_RenderDrawPoint(ren, result[0].x, result[0].y);
		SDL_RenderDrawLine(ren, result[0].x, result[0].y, result[1].x,result[1].y);
		 printf("%d (%.1lf,%.1lf) to (%.1lf,%.1lf)\n",(int)(i*100000),result[0].x, result[0].y, result[1].x,result[1].y);
	//	fflush(f);
		if (result[0].x > width || result[0].y > height)
			break;
	}
	SDL_RenderPresent(ren);
//	fclose(f);
	SDL_Delay(3000);
	quit();
}//你们试下这代码正常吗