#include "mlx_gui.h"

#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>
#include <time.h>

int translate_keycode(int keycode, t_camera_key *pKey);

int key_event(int keycode, int state, void *param)
{
	t_mlx_context* ctx;
	printf("key: %d\n", keycode);
	ctx = param;
	t_camera_key key;
	if (translate_keycode(keycode, &key) == 0)
		camera_key_event(&ctx->renderer.camera, key, state);
	return 0;
}

int keydown_event(int keycode, void *param)
{
	return key_event(keycode, 1, param);
}
int keyup_event(int keycode, void *param)
{
	return key_event(keycode, 0, param);
}

int translate_keycode(int keycode, t_camera_key *key)
{
	if (keycode == MLX_KEY_W)
		*key = KEY_FORWARD;
	else if (keycode == MLX_KEY_S)
		*key = KEY_BACKWARD;
	else if (keycode == MLX_KEY_A)
		*key = KEY_LEFT;
	else if (keycode == MLX_KEY_D)
		*key = KEY_RIGHT;
	else if (keycode == MLX_KEY_Q)
		*key = KEY_UPWARD;
	else if (keycode == MLX_KEY_Z)
		*key = KEY_DOWNWARD;
	else if (keycode == MLX_KEY_LEFT)
		*key = KEY_LEFT_ARROW;
	else if (keycode == MLX_KEY_RIGHT)
		*key = KEY_RIGHT_ARROW;
	else if (keycode == MLX_KEY_UP)
		*key = KEY_UP_ARROW;
	else if (keycode == MLX_KEY_DOWN)
		*key = KEY_DOWN_ARROW;
	else
		return -1;
	return 0;
}

int quit_event()
{
	exit(0);
}

int expose_callback(void *param)
{
	t_mlx_context *ctx;
	ctx = param;
	printf("Expose\n");
//	mlx_put_image_to_window(ctx->mlx_ptr, ctx->win_ptr, ctx->texture, 0, 0);

	return 0;
}

int callback(void *param)
{
	t_mlx_context *ctx;
	ctx = param;

	static clock_t timestamp = 0;
	float duration = (clock() - timestamp) / (float)CLOCKS_PER_SEC;
	duration *= 1000;
//	printf("Interval: %f\n", duration);
	timestamp = clock();

	renderer_update(&ctx->renderer);
	renderer_draw(ctx->renderer);

	mlx_put_image_to_window(ctx->mlx_ptr, ctx->win_ptr, ctx->texture, 0, 0);
	return 0;
}

void init_mlx(t_mlx_context *ctx, t_array segment_array)
{
	t_vec3 size;
	void* pixels;
	int osef;

	size.x = 1600;
	size.y = 900;

	ctx->mlx_ptr = mlx_init();
	ctx->win_ptr = mlx_new_window(ctx->mlx_ptr, size.x, size.y, "Wireframe");
	ctx->texture = mlx_new_image(ctx->mlx_ptr, size.x, size.y);
	pixels = mlx_get_data_addr(ctx->texture, &osef, &osef, &osef);

	renderer_init(&ctx->renderer, pixels, segment_array, size);

	mlx_do_key_autorepeatoff(ctx->mlx_ptr);
	mlx_hook(ctx->win_ptr, 2, 0xFFFFFFFF, keydown_event, ctx);
	mlx_hook(ctx->win_ptr, 3, 0xFFFFFFFF, keyup_event, ctx);
	mlx_hook(ctx->win_ptr, 17, 0xFFFFFFFF, quit_event, NULL);
	mlx_expose_hook(ctx->win_ptr, expose_callback, ctx);
	mlx_loop_hook(ctx->mlx_ptr, callback, ctx);
	mlx_loop(ctx->mlx_ptr);
}
