/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_keyboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 17:58:39 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/10/17 17:58:39 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_gui.h"

#include <stdlib.h>
#include "camera.h"

int				key_event(int keycode, int state, void *param)
{
	t_mlx_context	*ctx;
	t_camera_key	camera_key;
	t_renderer_key	renderer_key;

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
	return (0);
}

t_camera_key	get_camera_key(int keycode)
{
	static t_camera_key table[MLX_KEY_MAX] = {0};

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
	table[MLX_KEY_P] = KEY_CAMERA_PRINT_POS;
	if (keycode >= MLX_KEY_MAX)
		return (KEY_UNKNOWN);
	return (table[keycode]);
}

t_renderer_key	get_renderer_key(int keycode)
{
	if (keycode == MLX_KEY_PLUS)
		return (KEY_SCALE_UP);
	if (keycode == MLX_KEY_MINUS)
		return (KEY_SCALE_DOWN);
	if (keycode == MLX_KEY_MULTIPLY)
		return (KEY_FOV_UP);
	if (keycode == MLX_KEY_DIVIDE)
		return (KEY_FOV_DOWN);
	if (keycode == MLX_KEY_T)
		return (KEY_PROJECTION_TOOGLE);
	if (keycode == MLX_KEY_F)
		return (KEY_FOG_TOOGLE);
	return (KEY_RUNKNOWN);
}

int				keydown_event(int keycode, void *param)
{
	return (key_event(keycode, 1, param));
}

int				keyup_event(int keycode, void *param)
{
	return (key_event(keycode, 0, param));
}
