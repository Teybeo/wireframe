#include "sdl_gui.h"
#include <SDL.h>
#include <zconf.h>
#include <array.h>
#include <renderer.h>
#include <map_reader.h>

void sdl_init(t_sdl_context *context)
{
	SDL_Init(SDL_INIT_VIDEO);
	context->window = SDL_CreateWindow("Wireframe",
							  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							  1600, 900,
							  SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	context->renderer = SDL_CreateRenderer(context->window, -1,
										   SDL_RENDERER_SOFTWARE);
	SDL_Rect rect = (SDL_Rect){400, 275, 1600, 900};
	SDL_RenderSetViewport(context->renderer, &rect);
}

void sdl_run(t_sdl_context *context, t_array segment_array)
{
	context->is_running = 1;
	while (context->is_running) {
		sdl_event(context);
		sdl_update();
		sdl_draw(context, segment_array);
	}

}

void sdl_draw(t_sdl_context *ctx, t_array segment_array)
{
	int i;
	t_segment *segment_ptr;

	SDL_SetRenderDrawColor(ctx->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(ctx->renderer);

	SDL_SetRenderDrawColor(ctx->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	segment_ptr = segment_array.data;
	i = 0;

	while (i < segment_array.size)
	{
		t_point a = segment_ptr[i].start;
		t_point b = segment_ptr[i].end;
		SDL_RenderDrawLine(ctx->renderer,
						   a.x * 10, a.y * 10,
						   b.x * 10, b.y * 10
		);
		i++;
	}
	SDL_RenderPresent(ctx->renderer);
}

void sdl_update()
{

}

void sdl_event(t_sdl_context* context)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			context->is_running = 0;
		renderer_event();
	}
}
