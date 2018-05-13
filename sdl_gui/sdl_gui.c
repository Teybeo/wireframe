#include "sdl_gui.h"
#include <SDL2/SDL.h>

void app_init()
{
	SDL_Window *window;

	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Wireframe",
							  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							  1600, 900,
							  SDL_WINDOW_HIDDEN);
}

void app_run()
{
}
