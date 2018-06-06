#include "sdl_gui.h"
#include <SDL.h>
#include <zconf.h>
#include <array.h>
#include <renderer.h>
#include <map_reader.h>
#include <time.h>

int translate_keycode(SDL_Scancode scancode, t_camera_key *key)
;

void sdl_init(t_sdl_app *ctx, t_array segment_array)
{
	ctx->texture_size.x = 1600;
	ctx->texture_size.y = 900;

	SDL_Init(SDL_INIT_VIDEO);


	ctx->window = SDL_CreateWindow("Wireframe",
							  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							  ctx->texture_size.x, ctx->texture_size.y,
							  SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

//	SDL_SetHintWithPriority(SDL_HINT_RENDER_VSYNC, "1", SDL_HINT_OVERRIDE);

	ctx->sdl_renderer = SDL_CreateRenderer(ctx->window, -1,
										    SDL_RENDERER_ACCELERATED);
	SDL_RendererInfo info;
	SDL_GetRendererInfo(ctx->sdl_renderer, &info);
	printf("Renderer: %s\n", info.name);
	printf("SDL_RENDERER_ACCELERATED: %d\n", (SDL_RENDERER_ACCELERATED & info.flags) == SDL_RENDERER_ACCELERATED);
	printf("SDL_RENDERER_PRESENTVSYNC: %d\n", (SDL_RENDERER_PRESENTVSYNC & info.flags) == SDL_RENDERER_PRESENTVSYNC);
	printf("SDL_RENDERER_SOFTWARE: %d\n", (SDL_RENDERER_SOFTWARE & info.flags) == SDL_RENDERER_SOFTWARE);

	ctx->texture = SDL_CreateTexture(ctx->sdl_renderer,
										 SDL_PIXELFORMAT_ARGB8888,
										 SDL_TEXTUREACCESS_STREAMING,
										 ctx->texture_size.x, ctx->texture_size.y);

	ctx->pixels = malloc(sizeof(uint32_t) * ctx->texture_size.x * ctx->texture_size.y);

	renderer_init(&ctx->renderer, ctx->pixels, segment_array, ctx->texture_size);
}

void sdl_run(t_sdl_app *context)
{
	context->is_running = 1;
	while (context->is_running) {
		sdl_event(context);
		sdl_update(context);
		sdl_draw(context);
	}

}

void sdl_draw(t_sdl_app *ctx)
{

#ifndef SDL_RENDER
	renderer_draw(ctx->renderer);

	SDL_UpdateTexture(ctx->texture, NULL, ctx->pixels, ctx->texture_size.x * sizeof(Uint32));
	SDL_RenderCopy(ctx->sdl_renderer, ctx->texture, NULL, NULL);
#else
	SDL_SetRenderDrawColor(ctx->sdl_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	segment_ptr = ctx->renderer.segment_array.data;
	i = 0;
	while (i < ctx->renderer.segment_array.size)
	{
		t_vec3 a = segment_ptr[i].start;
		t_vec3 b = segment_ptr[i].end;
		SDL_RenderDrawLine(ctx->sdl_renderer,
						   a.x * 10, a.y * 10,
						   b.x * 10, b.y * 10
		);
		i++;
	}
#endif

	SDL_RenderPresent(ctx->sdl_renderer);
}

void sdl_update(t_sdl_app *context)
{
	static clock_t timestamp = 0;
	float duration = (clock() - timestamp) / (float)CLOCKS_PER_SEC;
	duration *= 1000;
//	printf("Interval: %f ms\n", duration);

	renderer_update(&context->renderer);

	timestamp = clock();
}

void sdl_event(t_sdl_app* ctx)
{
	SDL_Event event;
	t_camera_key key;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			ctx->is_running = 0;
		renderer_event(&ctx->renderer);
		if (event.type == SDL_KEYDOWN)
			if (translate_keycode(event.key.keysym.scancode, &key) == 0)
				camera_key_event(&ctx->renderer.camera, key, 1);
		if (event.type == SDL_KEYUP)
			if (translate_keycode(event.key.keysym.scancode, &key) == 0)
				camera_key_event(&ctx->renderer.camera, key, 0);
	}
}

int translate_keycode(SDL_Scancode scancode, t_camera_key *key)
{
	t_camera_key table[SDL_NUM_SCANCODES];

	table[SDL_SCANCODE_W] = KEY_FORWARD;
	table[SDL_SCANCODE_S] = KEY_BACKWARD;
	table[SDL_SCANCODE_A] = KEY_LEFT;
	table[SDL_SCANCODE_D] = KEY_RIGHT;
	table[SDL_SCANCODE_Q] = KEY_UPWARD;
	table[SDL_SCANCODE_Z] = KEY_DOWNWARD;
	table[SDL_SCANCODE_UP] = KEY_UP_ARROW;
	table[SDL_SCANCODE_DOWN] = KEY_DOWN_ARROW;
	table[SDL_SCANCODE_LEFT] = KEY_LEFT_ARROW;
	table[SDL_SCANCODE_RIGHT] = KEY_RIGHT_ARROW;

	*key = table[scancode];
	return 0;
}
