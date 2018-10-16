/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_part2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 17:45:15 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/10/16 17:45:34 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

#include <math.h>

float	vec3_max_axis(t_vec3 a)
{
	return (fmaxf(a.x, fmaxf(a.y, a.z)));
}

void	vec4_mul_scalar_this(t_vec4 *vec, float scalar)
{
	vec->x *= scalar;
	vec->y *= scalar;
	vec->z *= scalar;
}

t_vec3	vec3_mul_scalar(t_vec3 vec, float scalar)
{
	t_vec3 res;

	res = vec;
	res.x *= scalar;
	res.y *= scalar;
	res.z *= scalar;
	return (res);
}

void	vec4_round2_point(t_vec4 vec, t_point *p)
{
	p->x = (int)(vec.x + 0.5f);
	p->y = (int)(vec.y + 0.5f);
}

int		color_mix(float factor, int a, int b)
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;

	red = (1 - factor) * RED(a) + factor * RED(b);
	green = (1 - factor) * GREEN(a) + factor * GREEN(b);
	blue = (1 - factor) * BLUE(a) + factor * BLUE(b);
	return ((red << R_SHIFT) + (green << G_SHIFT) + (blue << B_SHIFT));
}
