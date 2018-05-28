#ifndef VEC3_H
#define VEC3_H

struct s_vec3
{
	int x;
	int y;
	int z;
};
typedef struct s_vec3 t_vec3;

t_vec3	vec3_add(t_vec3 a, t_vec3 b);

#endif
