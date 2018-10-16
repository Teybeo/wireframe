/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 15:29:10 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/10/09 17:01:56 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "libft.h"

void	init_camera(t_camera *camera, float speed_factor)
{
	ft_memzero(camera, 1, sizeof(t_camera));
	camera->pos = (t_vec3){0, 0, 0};
	camera->x_angle = 0;
	camera->y_angle = 0;
	camera->mode = CAMERA_FREEFLY;
	camera->speed_factor = speed_factor;
}

void	camera_key_event(t_camera *camera, t_camera_key key, int state)
{
	camera->key_state[key] = (bool)state;
	if (key == KEY_CAMERA_MODE_TOGGLE && state == 0)
		camera->mode ^= 1;
	if (key == KEY_CAMERA_RESET && state == 0)
	{
		camera->pos = (t_vec3){0, 0, 0};
		camera->x_angle = 0;
		camera->y_angle = 0;
	}
}

void	camera_mouse_event(t_camera *camera, int x, int y)
{
	camera->y_angle += x * 0.005f;
	camera->x_angle -= y * 0.005f;
}

void	camera_update(t_camera *camera)
{
	t_vec3 delta;
	t_vec3 backward;
	t_vec3 upward;
	t_vec3 strafe;

	camera->y_angle -= 0.05 * camera->key_state[KEY_RIGHT_ARROW];
	camera->y_angle += 0.05 * camera->key_state[KEY_LEFT_ARROW];
	camera->x_angle += 0.05 * camera->key_state[KEY_UP_ARROW];
	camera->x_angle -= 0.05 * camera->key_state[KEY_DOWN_ARROW];
	mat3_set_rotation(camera->x_angle, camera->y_angle, &camera->rotation);
	compute_basis_vectors(camera, &strafe, &upward, &backward);
	delta = (t_vec3){0, 0, 0};
	delta = camera->key_state[KEY_FORWARD] ? vec3_sub(delta, backward) : delta;
	delta = camera->key_state[KEY_BACKWARD] ? vec3_add(delta, backward) : delta;
	delta = camera->key_state[KEY_RIGHT] ? vec3_add(delta, strafe) : delta;
	delta = camera->key_state[KEY_LEFT] ? vec3_sub(delta, strafe) : delta;
	delta = camera->key_state[KEY_UPWARD] ? vec3_add(delta, upward) : delta;
	delta = camera->key_state[KEY_DOWNWARD] ? vec3_sub(delta, upward) : delta;
	delta = vec3_mul_scalar(delta, camera->speed_factor);
	camera->pos = vec3_add(camera->pos, delta);
}

void	compute_basis_vectors(t_camera *camera,
		t_vec3 *strafe, t_vec3 *upward, t_vec3 *backward)
{
	t_mat3 temp;

	temp = mat3_transpose(camera->rotation);
	if (camera->mode == CAMERA_FREEFLY)
	{
		*strafe = mat3_get_column(temp, 0);
		*upward = mat3_get_column(temp, 1);
		*backward = mat3_get_column(temp, 2);
	}
	else
	{
		*backward = (t_vec3){0, 0, 1};
		*upward = (t_vec3){0, 1, 0};
		*strafe = (t_vec3){1, 0, 0};
	}
}
