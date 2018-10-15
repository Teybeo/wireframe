/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 17:51:07 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/10/15 15:07:40 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAT4_H
# define MAT4_H

# include "mat3.h"

struct	s_mat4
{
	float values[4][4];
};
typedef struct s_mat4	t_mat4;

void	init_with_mat3(t_mat4 *mat4, t_mat3 mat3);
void	mat4_translate_by(t_mat4 *mat4, t_vec3 vec);
void	mat4_mul_vec(t_mat4 *mat, t_vec4 *vec);
void	mat4_mul_ptr(t_mat4 *this, t_mat4 const *lhs, t_mat4 const *rhs);
void	mat4_identity(t_mat4 *m);
t_mat4	get_perspective(float near, float far, float aspect_ratio,
		float fov_angle);
t_mat4	get_orthographic(float width, float height, float near, float far);

#endif
