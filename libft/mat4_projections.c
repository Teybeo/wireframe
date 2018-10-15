/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_projections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 15:21:17 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/10/15 15:21:17 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat4.h"

#include <math.h>

t_mat4	get_perspective(float near, float far, float aspect_ratio,
		float fov_angle)
{
	t_mat4	m;
	float	distance;
	float	z_factor;
	float	z_translation;

	distance = 1.f / tanf((fov_angle / 2) * M_PI_F / 180);
	z_factor = (-far + near) / (far - near);
	z_translation = ((2 * far * near) / (far - near));
	mat4_identity(&m);
	m.values[0][0] = distance * aspect_ratio;
	m.values[1][1] = distance;
	m.values[2][2] = z_factor;
	m.values[2][3] = -z_translation;
	m.values[3][2] = -1;
	m.values[3][3] = 0;
	return (m);
}

t_mat4	get_orthographic(float width, float height, float near, float far)
{
	t_mat4	m;
	float	right;
	float	left;
	float	top;
	float	bottom;

	right = (width / 2);
	left = -(width / 2);
	top = height / 2;
	bottom = -(height / 2);
	mat4_identity(&m);
	m.values[0][0] = 2 / (right - left);
	m.values[1][1] = 2 / (top - bottom);
	m.values[2][2] = -2 / (far - near);
	m.values[0][3] = -(right + left) / (right - left);
	m.values[1][3] = -(top + bottom) / (top - bottom);
	m.values[2][3] = -(far + near) / (far - near);
	return (m);
}
