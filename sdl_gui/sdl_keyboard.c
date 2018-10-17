/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_keyboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 15:04:56 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/10/17 15:04:56 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

#include "camera.h"
#include "SDL_scancode.h"

t_camera_key	get_camera_key(SDL_Scancode scancode)
{
	static t_camera_key table[SDL_NUM_SCANCODES] = {0};

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
	table[SDL_SCANCODE_C] = KEY_CAMERA_MODE_TOGGLE;
	table[SDL_SCANCODE_R] = KEY_CAMERA_RESET;
	table[SDL_SCANCODE_P] = KEY_CAMERA_PRINT_POS;
	return (table[scancode]);
}

t_renderer_key	get_renderer_key(SDL_Scancode scancode)
{
	if (scancode == SDL_SCANCODE_KP_PLUS)
		return (KEY_SCALE_UP);
	if (scancode == SDL_SCANCODE_KP_MINUS)
		return (KEY_SCALE_DOWN);
	if (scancode == SDL_SCANCODE_KP_MULTIPLY)
		return (KEY_FOV_UP);
	if (scancode == SDL_SCANCODE_KP_DIVIDE)
		return (KEY_FOV_DOWN);
	if (scancode == SDL_SCANCODE_T)
		return (KEY_PROJECTION_TOOGLE);
	if (scancode == SDL_SCANCODE_F)
		return (KEY_FOG_TOOGLE);
	return (KEY_RUNKNOWN);
}
