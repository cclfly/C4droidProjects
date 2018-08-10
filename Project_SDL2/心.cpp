/* c4droid代码手册 *爱心 @DXkite 编写 */
#include <SDL2/SDL.h>
#define DOUBLE(x) 2*x
#define UI_X DOUBLE(150)
#define UI_Y DOUBLE(100)
#define XIN(x,y) (x*x+y*y-1)*(x*x+y*y-1)*(x*x+y*y-1)-x*x*y*y*y
bool ui[UI_X][UI_Y];
// 初始化界面
void init_ui();
// 绘制界面
int draw_ui();
void draw_point(int x, int y) {
	if (x < UI_X && y < UI_Y)
		if (ui[x][y] == false)
			ui[x][y] = true;
}

int main(int args, char **argv) {
	init_ui();
	// int x = 15, y = 10;
	for (int i = -(UI_Y / 2); i <= UI_Y / 2; ++i)
		for (int j = -(UI_X / 2); j <= UI_X / 2; ++j)
			if (XIN(j * 1.3 / (UI_X / 2), -i * 1.5 / (UI_Y / 2)) < 0)
				draw_point(j + UI_X / 2, i + UI_Y / 2);
	while (true) {
		draw_ui();
		SDL_Delay(10);
	}
}

// 函数
int draw_ui() {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *Window = NULL;
	SDL_Renderer *Renderer = NULL;
	SDL_Texture *Texture = NULL;
	SDL_Surface *Surface = NULL;
	Window =
		SDL_CreateWindow("SDL_Window", SDL_WINDOWPOS_CENTERED,
						 SDL_WINDOWPOS_CENTERED, 300, 400, SDL_WINDOW_SHOWN);
	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
	Uint32 Surface_Color[UI_X * UI_Y];
	for (int y = 0; y < UI_Y; ++y)
		for (int x = 0; x < UI_X; ++x) {
			if (ui[x][y])
				Surface_Color[y * UI_X + x] = 0xff0000ff;
			else
				Surface_Color[y * UI_X + x] = 0xfffffffff;
		}
	Surface =
		SDL_CreateRGBSurfaceFrom(Surface_Color, UI_X, UI_Y, 32,
								 UI_X * sizeof(Uint32), 0xFF000000, 0x00FF0000,
								 0x0000FF00, 0x000000FF);
	Texture = SDL_CreateTextureFromSurface(Renderer, Surface);
	SDL_RenderCopy(Renderer, Texture, NULL, NULL);
	SDL_RenderPresent(Renderer);
	SDL_DestroyWindow(Window);
	SDL_DestroyRenderer(Renderer);
	SDL_Quit();
	return 0;
}

void init_ui() {
	for (int y = 0; y < UI_X; ++y)
		for (int x = 0; x < UI_Y; ++x)
			ui[x][y] = false;
} 