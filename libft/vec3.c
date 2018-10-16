/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 17:44:32 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/10/16 17:44:32 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

#include <stdio.h>
#include <math.h>

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	t_vec3 res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	t_vec3 res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}

void	vec3_sub_this(t_vec3 *a, t_vec3 b)
{
	a->x -= b.x;
	a->y -= b.y;
	a->z -= b.z;
}

t_vec3	vec3_min(t_vec3 a, t_vec3 b)
{
	t_vec3 res;

	res.x = fminf(a.x, b.x);
	res.y = fminf(a.y, b.y);
	res.z = fminf(a.z, b.z);
	return (res);
}

t_vec3	vec3_max(t_vec3 a, t_vec3 b)
{
	t_vec3 res;

	res.x = fmaxf(a.x, b.x);
	res.y = fmaxf(a.y, b.y);
	res.z = fmaxf(a.z, b.z);
	return (res);
}
