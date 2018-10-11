/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 17:48:09 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/10/11 17:48:09 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

# define M_PI_F ((float)M_PI)
# define DEG_TO_RAD(X) (((X) / 180.f) * 3.14159f)

# define R_MASK (0x00FF0000)
# define G_MASK (0x0000FF00)
# define B_MASK (0x000000FF)

# define R_SHIFT (16u)
# define G_SHIFT (8u)
# define B_SHIFT (0u)

# define RED(x) ((x & R_MASK) >> R_SHIFT)
# define GREEN(x) ((x & G_MASK) >> G_SHIFT)
# define BLUE(x) ((x & B_MASK) >> B_SHIFT)

struct	s_vec3 {
	float x;
	float y;
	float z;
};

struct	s_vec4
{
	float x;
	float y;
	float z;
	float w;
};

struct	s_point {
	int		x;
	int		y;
	float	z;
	int		color;
};

struct	s_vec2i {
	int x;
	int y;
};

struct	s_segment {
	int		start_idx;
	int		end_idx;
};

typedef struct s_vec3	t_vec3;
typedef struct s_vec4	t_vec4;
typedef struct s_point	t_point;
typedef struct s_vec2i	t_vec2i;
typedef struct s_segment	t_segment;

t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
void	vec3_sub_this(t_vec3 *a, t_vec3 b);
t_vec3	vec3_mul_scalar(t_vec3 vec, float scalar);
void	vec4_mul_scalar_this(t_vec4 *vec, float scalar);

t_vec3	vec3_max(t_vec3 a, t_vec3 b);
t_vec3	vec3_min(t_vec3 a, t_vec3 b);
float	vec3_max_axis(t_vec3 a);
void	vec4_round2_point(t_vec4 vec, t_point *p);
int		color_mix(float factor, int a, int b);
void	vec3_print(char const *msg, t_vec3 vec);

#endif
