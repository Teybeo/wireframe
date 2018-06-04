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

void	vec3_subX(t_vec3 *a, t_vec3 b)
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
	res.z = 0;
	return res;
}

t_vec3 vec3_max_2D(t_vec3 a, t_vec3 b)
{
	t_vec3 res;
	res.x = fmaxf(a.x, b.x);
	res.y = fmaxf(a.y, b.y);
	res.z = 0;
	return res;
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

t_vec2i	vec3_round2D(t_vec3 vec)
{
	t_vec2i res;
	res.x = (int)roundf(vec.x);
	res.y = (int)roundf(vec.y);
	return res;
}

void	vec3_print(char const* msg, t_vec3 vec)
{
	printf("%s %g, %g, %g\n", msg, vec.x, vec.y, vec.z);
}
