#ifndef WIREFRAME_APP_H
#define WIREFRAME_APP_H

#include <SDL_video.h>
#include <SDL_system.h>
#include "array.h"

struct s_sdl_context {
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	int				is_running;
};
typedef struct s_sdl_context t_sdl_context;

void sdl_init(t_sdl_context *pContext);
void sdl_run(t_sdl_context *array, t_array sArray);
static void	sdl_event(t_sdl_context *pContext);
static void	sdl_update();
static void sdl_draw(t_sdl_context *array, t_array sArray);

#endif
