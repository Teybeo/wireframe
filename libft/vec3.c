#include "vec3.h"

#include <stdio.h>

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

int		clamp(int a, int min, int max)
{
	if (a > max)
		return max;
	if (a < min)
		return min;
	return a;
}

t_vec3 vec3_clamp2D(t_vec3 a, t_vec3 limit)
{
	t_vec3 res;
	res.x = clamp(a.x, 0, limit.x - 1);
	res.y = clamp(a.y, 0, limit.y - 1);
	res.z = a.z;
	return res;
}

void	vec3_print(t_vec3 vec)
{
	printf("%d, %d, %d", vec.x, vec.y, vec.z);
}