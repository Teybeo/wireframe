/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat3_part2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 17:30:12 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/10/15 17:30:13 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat3.h"

void	swap_float(float *a, float *b)
{
	float temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

t_mat3	mat3_transpose(t_mat3 m)
{
	t_mat3 res;

	res = m;
	swap_float(&res.values[0][1], &res.values[1][0]);
	swap_float(&res.values[0][2], &res.values[2][0]);
	swap_float(&res.values[1][2], &res.values[2][1]);
	return (res);
}

t_vec3	mat3_get_column(t_mat3 m, int column)
{
	t_vec3	vec;

	vec.x = m.values[0][column];
	vec.y = m.values[1][column];
	vec.z = m.values[2][column];
	return (vec);
}
