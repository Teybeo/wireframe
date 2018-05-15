#include "sdl_gui.h"
#include <SDL.h>
#include <zconf.h>

void sdl_init()
{
	SDL_Window *window;

	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Wireframe",
							  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							  1600, 900,
							  SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
}

void sdl_run()
{
}
