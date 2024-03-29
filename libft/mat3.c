/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 15:47:29 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/10/15 16:18:11 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat3.h"

#include <math.h>
#include "vec3.h"
#include "libft.h"

void	mat3_set_identity(t_mat3 *m)
{
	ft_memzero(m, 3 * 3, sizeof(float));
	m->values[0][0] = 1;
	m->values[1][1] = 1;
	m->values[2][2] = 1;
}

/*
** AB[i][j] = A.line[i] dot B.column[j]
*/

t_mat3	mat3_mul(t_mat3 lhs, t_mat3 rhs)
{
	t_mat3	res;
	int		i;
	int		j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			res.values[i][j] =
					lhs.values[i][0] * rhs.values[0][j] +
					lhs.values[i][1] * rhs.values[1][j] +
					lhs.values[i][2] * rhs.values[2][j];
		}
	}
	return (res);
}

void	mat3_set_rotation(float x_angle, float y_angle, t_mat3 *m)
{
	t_mat3 x_rotation;
	t_mat3 y_rotation;

	mat3_set_identity(&x_rotation);
	mat3_set_identity(&y_rotation);
	mat3_set_x_rotation(&x_rotation, x_angle);
	mat3_set_y_rotation(&y_rotation, y_angle);
	*m = mat3_mul(x_rotation, y_rotation);
}

/*
** .,     .,    .
** .,   cos,  sin
** .,  -sin,  cos
*/

void	mat3_set_x_rotation(t_mat3 *m, float angle)
{
	m->values[1][1] = cosf(angle);
	m->values[1][2] = sinf(angle);
	m->values[2][1] = -sinf(angle);
	m->values[2][2] = cosf(angle);
}

/*
** cos, ., -sin
**   ., .,   .
** sin, ., cos
*/

void	mat3_set_y_rotation(t_mat3 *m, float angle)
{
	m->values[0][0] = cosf(angle);
	m->values[0][2] = sinf(angle);
	m->values[2][0] = -sinf(angle);
	m->values[2][2] = cosf(angle);
}
