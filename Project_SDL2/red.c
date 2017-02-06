#include <SDL2/SDL.h>
SDL_Window *window = NULL;
SDL_Surface *surface = NULL;
int Init() {
  SDL_Init(SDL_INIT_VIDEO);
  window = SDL_CreateWindow("SDL_window", 0, 0, 480, 800, SDL_WINDOW_SHOWN);

  if (window == NULL)
    return -1;

  surface = SDL_GetWindowSurface(window);
  if (surface == 0)
    return -2;
  return 0;
}


void Destroy() {
  SDL_FreeSurface(surface);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

int main(int args, char *argv[]) {
  if (Init() != 0)
    return -1;

  SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0x00, 0x00));
  SDL_UpdateWindowSurface(window);
  SDL_Delay(20000);
  Destroy();
  return 0;
}