#ifndef VEC3_H
#define VEC3_H

struct s_vec3
{
	float x;
	float y;
	float z;
};
typedef struct s_vec3 t_vec3;

struct s_vec2i
{
	int x;
	int y;
};
typedef struct s_vec2i t_vec2i;

t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
void	vec3_print(t_vec3 vec);
t_vec3	vec3_clamp2D(t_vec3 a, t_vec3 limit);
t_vec3	vec3_max_2D(t_vec3 a, t_vec3 b);
t_vec3	vec3_min_2D(t_vec3 a, t_vec3 b);
t_vec3	vec3_mul_scalar(t_vec3 vec, float scalar);
t_vec2i	vec3_round2D(t_vec3 vec);

#endif
