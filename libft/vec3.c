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

void	vec4_round2D_point(t_vec4 vec, t_point *p)
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

void	vec3_print(char const *msg, t_vec3 vec)
{
	printf("%s %g, %g, %g\n", msg, vec.x, vec.y, vec.z);
}
