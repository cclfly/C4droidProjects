#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
SDL_Window *Window ;
SDL_Renderer *Renderer;
SDL_Texture *Texture ;
SDL_Surface *Surface ;
int Init() {
  SDL_Init(SDL_INIT_VIDEO);
  Window = SDL_CreateWindow("SDL_Window", SDL_WINDOWPOS_CENTERED,
                     SDL_WINDOWPOS_CENTERED, 240, 400, SDL_WINDOW_SHOWN);
  if (Window == NULL)
    return -1;
  Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
  if (Renderer == NULL)
    return -2;
  return 0;
}
void RenderText(int x, int y, const char *text) {
  TTF_Init();
  TTF_Font *font = NULL;
  int w = 0, h = 0;
  font = TTF_OpenFont("/system/fonts/DroidSansFallback.ttf", 20);
  SDL_Color color;
  color.r = 0xff;
  color.g = 0;
  color.b = 0;
  color.a = 0xff;
  Surface = TTF_RenderUTF8_Blended(font, text, color);
  w = Surface->w;
  h = Surface->h;
  Texture = SDL_CreateTextureFromSurface(Renderer, Surface);
  SDL_FreeSurface(Surface);
  TTF_CloseFont(font);
  SDL_Rect Box;
  Box.x = x;
  Box.y = y;
  Box.w = w;
  Box.h = h;
  SDL_RenderCopy(Renderer, Texture, NULL, &Box);
  SDL_DestroyTexture(Texture);
  TTF_Quit();
}
void Destroy() {
  SDL_FreeSurface(Surface);
  SDL_DestroyWindow(Window);
  SDL_DestroyTexture(Texture);
 SDL_DestroyRenderer(Renderer);
  SDL_Quit();
}
int main(int args, char *argv[]) {
  if (Init() != 0)
    return -1;
  bool Quit = false;
  SDL_Event event;
  double Tx, Ty, Tdy, Tdx;
  int W = 0, H = 0;
  SDL_GetWindowSize(Window, &W, &H);
  Tx = Ty = Tdy = Tdx = 0;
  char str[80];
  while (!Quit) {
    SDL_RenderClear(Renderer);
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_FINGERUP) {
        Tx = event.tfinger.x;
        Ty = event.tfinger.y;
        Tdx = event.tfinger.dx;
        Tdy = event.tfinger.dy;
        RenderText(0, 100, "SDL_FINGERUP");
      }
      if (event.type == SDL_FINGERDOWN) {
        Tx = event.tfinger.x;
        Ty = event.tfinger.y;
        Tdx = event.tfinger.dx;
        Tdy = event.tfinger.dy;
        RenderText(0, 100, "SDL_FINGERDOWN");
      }
      if (event.type == SDL_FINGERMOTION) {
        Tx = event.tfinger.x;
        Ty = event.tfinger.y;
        Tdx = event.tfinger.dx;
        Tdy = event.tfinger.dy;
        RenderText(0, 100, "SDL_FINGERMOTION");
      }
       if (event.key.keysym.sym == SDLK_MENU) {
        Quit = true;
      }
    }
    sprintf(str, "x,y [x:%f][y :%f]", Tx, Ty);
    RenderText(0, 200, str);
    sprintf(str, "dx,dy [x:%f][y:%f]", Tdx, Tdy);
    RenderText(0, 230, str);
    sprintf(str, "W:%d H:%d", W, H);
    RenderText(0, 260, str);
    SDL_RenderPresent(Renderer);
    SDL_Delay(10);
  }
  Destroy();
  return 0;
}