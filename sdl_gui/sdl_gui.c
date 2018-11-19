/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_gui.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 15:06:44 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/10/17 15:34:01 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_gui.h"

#include <SDL.h>

void	sdl_init(t_sdl_app *ctx, t_map map)
{
	ctx->texture_size.x = 1600;
	ctx->texture_size.y = 900;
	ctx->is_mouse_captured = false;
	SDL_Init(SDL_INIT_VIDEO);
	ctx->window = SDL_CreateWindow("Wireframe",
							SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							ctx->texture_size.x, ctx->texture_size.y,
							SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	ctx->sdl_renderer = SDL_CreateRenderer(ctx->window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	ctx->texture = SDL_CreateTexture(ctx->sdl_renderer,
										SDL_PIXELFORMAT_ARGB8888,
										SDL_TEXTUREACCESS_STREAMING,
										ctx->texture_size.x,
										ctx->texture_size.y);
	ctx->pixels = malloc(sizeof(uint32_t) *
						ctx->texture_size.x * ctx->texture_size.y);
	renderer_init(&ctx->renderer, ctx->pixels, map, ctx->texture_size);
}

void	sdl_run(t_sdl_app *context)
{
	context->is_running = true;
	while (context->is_running)
	{
		sdl_event(context);
		sdl_update(context);
		sdl_draw(context);
	}
}

void	sdl_draw(t_sdl_app *ctx)
{
	SDL_RenderClear(ctx->sdl_renderer);
	renderer_draw(ctx->renderer);
	SDL_UpdateTexture(ctx->texture, NULL, ctx->renderer.pixels,
			ctx->texture_size.x * sizeof(Uint32));
	SDL_RenderCopy(ctx->sdl_renderer, ctx->texture, NULL, NULL);
	SDL_RenderPresent(ctx->sdl_renderer);
}

void	sdl_update(t_sdl_app *context)
{
	static clock_t	timestamp = 0;
	static float	elapsed_time = 0;
	float			duration;

	renderer_update(&context->renderer);
	duration = (clock() - timestamp) / (float)CLOCKS_PER_SEC;
	duration *= 1000;
	elapsed_time += duration;
	if (elapsed_time >= 20)
	{
		elapsed_time = 0;
	}
	timestamp = clock();
}

void	sdl_event(t_sdl_app *ctx)
{
	SDL_Event		event;
	t_camera_key	camera_key;
	t_renderer_key	renderer_key;

	while (SDL_PollEvent(&event))
	{
		ctx->is_running = !(event.type == SDL_QUIT);
		if (event.type == SDL_KEYDOWN)
		{
			camera_key = get_camera_key(event.key.keysym.scancode);
			camera_key_event(&ctx->renderer.camera, camera_key, 1);
			renderer_key = get_renderer_key(event.key.keysym.scancode);
			renderer_event(&ctx->renderer, renderer_key);
			if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				ctx->is_mouse_captured = !ctx->is_mouse_captured;
			SDL_SetRelativeMouseMode(ctx->is_mouse_captured);
		}
		if (event.type == SDL_KEYUP)
			camera_key_event(&ctx->renderer.camera,
					get_camera_key(event.key.keysym.scancode), 0);
		if (event.type == SDL_MOUSEMOTION && ctx->is_mouse_captured)
			camera_mouse_event(&ctx->renderer.camera, event.motion.xrel,
					event.motion.yrel);
	}
}
