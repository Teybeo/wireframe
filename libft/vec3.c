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

void	vec3_subXX(t_vec3 *a, float x, float y, float z)
{
	a->x -= x;
	a->y -= y;
	a->z -= z;
}

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	t_vec3 res;
	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
	return res;
}

float		clamp(float a, float min, float max)
{
	if (a > max)
		return max;
	if (a < min)
		return min;
	return a;
}

t_vec3 vec3_clamp2D(t_vec3 a, t_vec2i limit)
{
	t_vec3 res;
	res.x = clamp(a.x, 0, limit.x - 1);
	res.y = clamp(a.y, 0, limit.y - 1);
	res.z = a.z;
	return res;
}

t_vec3 vec3_min_2D(t_vec3 a, t_vec3 b)
{
	t_vec3 res;
	res.x = fminf(a.x, b.x);
	res.y = fminf(a.y, b.y);
	res.z = fminf(a.z, b.z);
	return res;
}

t_vec3 vec3_max_2D(t_vec3 a, t_vec3 b)
{
	t_vec3 res;
	res.x = fmaxf(a.x, b.x);
	res.y = fmaxf(a.y, b.y);
	res.z = fmaxf(a.z, b.z);
	return res;
}

float vec3_max_axis(t_vec3 a)
{
	return fmaxf(a.x, fmaxf(a.y, a.z));
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
	return res;
}

t_vec3i	vec3_round(t_vec3 vec)
{
	t_vec3i res;
	res.x = (int)roundf(vec.x);
	res.y = (int)roundf(vec.y);
	res.z = (int)roundf(vec.z);
	return res;
}

t_vec2i	vec4_round2D(t_vec4 vec)
{
	t_vec2i res;
//	res.x = (int)roundf(vec.x);
//	res.y = (int)roundf(vec.y);
	res.x = (int)(vec.x + 0.5f);
	res.y = (int)(vec.y + 0.5f);
	return res;
}

int color_mix(float factor, int a, int b)
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;

	red = (1 - factor) * RED(a) + factor * RED(b);
	green = (1 - factor) * GREEN(a) + factor * GREEN(b);
	blue = (1 - factor) * BLUE(a) + factor * BLUE(b);

	return (red << R_SHIFT) + (green << G_SHIFT) + (blue << B_SHIFT);
}

void	vec3_print(char const* msg, t_vec3 vec)
{
	printf("%s %g, %g, %g\n", msg, vec.x, vec.y, vec.z);
}

t_vec4 vec4(t_vec3 v)
{
	t_vec4 res;
	res.x = v.x;
	res.y = v.y;
	res.z = v.z;
	res.w = 1;
	return res;
}
