#include "sdl_gui.h"
#include <SDL.h>
#include <zconf.h>
#include <array.h>
#include <renderer.h>
#include <map_reader.h>

void sdl_init(t_sdl_app *ctx, t_array segment_array)
{
	ctx->texture_size.x = 1600;
	ctx->texture_size.y = 900;

	SDL_Init(SDL_INIT_VIDEO);
	ctx->window = SDL_CreateWindow("Wireframe",
							  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							  ctx->texture_size.x, ctx->texture_size.y,
							  SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	ctx->sdl_renderer = SDL_CreateRenderer(ctx->window, -1,
										   SDL_RENDERER_ACCELERATED);
	ctx->texture = SDL_CreateTexture(ctx->sdl_renderer,
										 SDL_PIXELFORMAT_ARGB8888,
										 SDL_TEXTUREACCESS_STREAMING,
										 ctx->texture_size.x, ctx->texture_size.y);

//	SDL_Rect rect = (SDL_Rect){400, 275, 1600, 900};
//	SDL_RenderSetViewport(ctx->renderer, &rect);

	renderer_init(&ctx->renderer, segment_array, ctx->texture_size);
}

void sdl_run(t_sdl_app *context)
{
	context->is_running = 1;
	while (context->is_running) {
		sdl_event(context);
		sdl_update();
		sdl_draw(context);
	}

}

void sdl_draw(t_sdl_app *ctx)
{
	int i;
	t_segment *segment_ptr;

	SDL_SetRenderDrawColor(ctx->sdl_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(ctx->sdl_renderer);

	SDL_SetRenderTarget(ctx->sdl_renderer, ctx->texture);
	SDL_SetRenderDrawColor(ctx->sdl_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(ctx->sdl_renderer);
	SDL_SetRenderTarget(ctx->sdl_renderer, NULL);
	puts("Clear");
	fflush(stdout);
#ifndef SDL_RENDER
	renderer_draw(ctx->renderer);

	SDL_UpdateTexture(ctx->texture, NULL, NULL, ctx->texture_size.x * sizeof(Uint32));
	SDL_UpdateTexture(ctx->texture, NULL, ctx->renderer.pixels, ctx->texture_size.x * sizeof(Uint32));
	SDL_RenderCopy(ctx->sdl_renderer, ctx->texture, NULL, NULL);
#else
	SDL_SetRenderDrawColor(ctx->sdl_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	segment_ptr = ctx->renderer.segment_array.data;
	i = 0;
	while (i < ctx->renderer.segment_array.size)
	{
		t_point a = segment_ptr[i].start;
		t_point b = segment_ptr[i].end;
		SDL_RenderDrawLine(ctx->sdl_renderer,
						   a.x * 10, a.y * 10,
						   b.x * 10, b.y * 10
		);
		i++;
	}
#endif

	SDL_RenderPresent(ctx->sdl_renderer);
}

void sdl_update()
{

}

void sdl_event(t_sdl_app* context)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			context->is_running = 0;
		renderer_event(&context->renderer);
	}
}
