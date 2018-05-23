#ifndef WIREFRAME_APP_H
#define WIREFRAME_APP_H

#include <SDL_video.h>
#include <SDL_system.h>
#include <map_reader.h>
#include <renderer.h>
#include "array.h"

struct s_sdl_app {
	SDL_Window		*window;
	SDL_Renderer	*sdl_renderer;
	SDL_Texture		*texture;
	t_renderer		renderer;
	t_point			texture_size;
	int				is_running;
};
typedef struct s_sdl_app t_sdl_app;

void	sdl_init(t_sdl_app *ctx, t_array array);
void	sdl_run(t_sdl_app *app);
void	sdl_event(t_sdl_app *app);
void	sdl_update();
void	sdl_draw(t_sdl_app *app);

#endif
