#include "mlx_gui.h"

#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>
#include <time.h>

int				expose_callback(void *param)
{
	t_mlx_context *ctx;

	ctx = param;
	printf("Expose\n");
	mlx_put_image_to_window(ctx->mlx_ptr, ctx->win_ptr, ctx->texture, 0, 0);
	return (0);
}

int				callback(void *param)
{
	t_mlx_context	*ctx;

	ctx = param;
	mlx_clear_window(ctx->mlx_ptr, ctx->win_ptr);
	renderer_update(&ctx->renderer);
	renderer_draw(ctx->renderer);
//	renderer_draw0(ctx->renderer);
	mlx_put_image_to_window(ctx->mlx_ptr, ctx->win_ptr, ctx->texture, 0, 0);
	return (0);
}

int				mouse_move(int x, int y, void *param)
{
	t_mlx_context	*ctx;
	static int		old_x;
	static int		old_y;
	int				dx;
	int				dy;

	ctx = param;
	dx = x - old_x;
	dy = y - old_y;
	old_x = x;
	old_y = y;
	if (ctx->is_mouse_captured)
		camera_mouse_event(&ctx->renderer.camera, dx, dy);
	return (0);
}

int				quit_event(void)
{
	exit(0);
}

void			init_mlx(t_mlx_context *ctx, t_map map)
{
	t_vec2i size;
	void	*pixels;
	int		osef;

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
	mlx_hook(ctx->win_ptr, 6, osef, mouse_move, ctx);
	mlx_hook(ctx->win_ptr, 17, osef, quit_event, NULL);
	mlx_expose_hook(ctx->win_ptr, expose_callback, ctx);
	mlx_loop_hook(ctx->mlx_ptr, callback, ctx);
//	mlx_mouse_hook(ctx->win_ptr, mouse_move, ctx);
	mlx_loop(ctx->mlx_ptr);
}

