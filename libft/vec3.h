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
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
void	vec3_print(t_vec3 vec);
t_vec3 vec3_clamp2D(t_vec3 a, t_vec3 limit);

#endif
