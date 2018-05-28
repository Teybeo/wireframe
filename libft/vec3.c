#include "vec3.h"

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	t_vec3 res;
	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}