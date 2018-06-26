#include "mlx_gui.h"

#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>
#include <time.h>

t_camera_key get_camera_key(int keycode);
t_renderer_key get_renderer_key(int keycode);

int key_event(int keycode, int state, void *param)
{
	t_mlx_context* ctx;
	t_camera_key camera_key;
	t_renderer_key renderer_key;

//	printf("key: %d\n", keycode);
	ctx = param;
	camera_key = get_camera_key(keycode);
	if (camera_key != KEY_UNKNOWN)
		camera_key_event(&ctx->renderer.camera, camera_key, state);
	renderer_key = get_renderer_key(keycode);
	if (renderer_key != KEY_RUNKNOWN && state == 1)
		renderer_event(&ctx->renderer, renderer_key);
	if (keycode == MLX_KEY_ESC && state == 1)
	{
		ctx->is_mouse_captured = !ctx->is_mouse_captured;
		mlx_set_relative_mouse_mode(ctx->win_ptr, ctx->is_mouse_captured);
	}

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
	static clock_t timestamp;
	float duration;

	ctx = param;
	duration = (clock() - timestamp) / (float)CLOCKS_PER_SEC;
	duration *= 1000;
//	printf("Interval: %f\n", duration);
	timestamp = clock();

	mlx_clear_window(ctx->mlx_ptr, ctx->win_ptr);

	renderer_update(&ctx->renderer);
	renderer_draw(ctx->renderer);

	mlx_put_image_to_window(ctx->mlx_ptr, ctx->win_ptr, ctx->texture, 0, 0);
	return 0;
}

int mouse_move(int x, int y, void* param)
{
	t_mlx_context *ctx;
	static int old_x;
	static int old_y;
	int dx;
	int dy;

	ctx = param;
	dx = x - old_x;
	dy = y - old_y;
//	printf("x: %d, y: %d\n", x, y);
//	printf("dx: %d, dy: %d\n", dx, dy);
	old_x = x;
	old_y = y;
	if (ctx->is_mouse_captured)
		camera_mouse_event(&ctx->renderer.camera, dx, dy);
	return 0;
}
/*
void mouse_press(int x, int y, void* param)
{
	printf("PRESS\n");
	printf("x: %d, y: %d\n", x, y);
}

void mouse_release(int x, int y, void* param)
{
	printf("RELEASE\n");
	printf("x: %d, y: %d\n", x, y);
}
*/
void init_mlx(t_mlx_context *ctx, t_map map)
{
	t_vec2i size;
	void* pixels;
	int osef;

	size.x = 1600;
	size.y = 900;
	ctx->mlx_ptr = mlx_init();
	ctx->is_mouse_captured = false;
	ctx->win_ptr = mlx_new_window(ctx->mlx_ptr, size.x, size.y, "Wireframe");
	ctx->texture = mlx_new_image(ctx->mlx_ptr, size.x, size.y);
	pixels = mlx_get_data_addr(ctx->texture, &osef, &osef, &osef);

	renderer_init(&ctx->renderer, pixels, map, size);

	mlx_do_key_autorepeatoff(ctx->mlx_ptr);
	mlx_hook(ctx->win_ptr, 2, osef, keydown_event, ctx);
	mlx_hook(ctx->win_ptr, 3, osef, keyup_event, ctx);
//	mlx_hook(ctx->win_ptr, 4, osef, mouse_press, ctx);
//	mlx_hook(ctx->win_ptr, 5, osef, mouse_release, ctx);
	mlx_hook(ctx->win_ptr, 6, osef, mouse_move, ctx);
	mlx_hook(ctx->win_ptr, 17, osef, quit_event, NULL);
	mlx_expose_hook(ctx->win_ptr, expose_callback, ctx);
	mlx_loop_hook(ctx->mlx_ptr, callback, ctx);
//	mlx_mouse_hook(ctx->win_ptr, mouse_move, ctx);
	mlx_loop(ctx->mlx_ptr);
}


t_camera_key get_camera_key(int keycode)
{
	t_camera_key table[MLX_KEY_MAX];

	table[MLX_KEY_W] = KEY_FORWARD;
	table[MLX_KEY_S] = KEY_BACKWARD;
	table[MLX_KEY_A] = KEY_LEFT;
	table[MLX_KEY_D] = KEY_RIGHT;
	table[MLX_KEY_Q] = KEY_UPWARD;
	table[MLX_KEY_Z] = KEY_DOWNWARD;
	table[MLX_KEY_UP] = KEY_UP_ARROW;
	table[MLX_KEY_DOWN] = KEY_DOWN_ARROW;
	table[MLX_KEY_LEFT] = KEY_LEFT_ARROW;
	table[MLX_KEY_RIGHT] = KEY_RIGHT_ARROW;
	table[MLX_KEY_C] = KEY_CAMERA_MODE_TOGGLE;
	table[MLX_KEY_R] = KEY_CAMERA_RESET;
	if (keycode >= MLX_KEY_MAX)
		return KEY_UNKNOWN;
	return table[keycode];
}

t_renderer_key get_renderer_key(int keycode)
{
	if (keycode == MLX_KEY_PLUS)
		return KEY_SCALE_UP;
	if (keycode == MLX_KEY_MINUS)
		return KEY_SCALE_DOWN;
	if (keycode == MLX_KEY_MULTIPLY)
		return KEY_FOV_UP;
	if (keycode == MLX_KEY_DIVIDE)
		return KEY_FOV_DOWN;
	return KEY_RUNKNOWN;
}
