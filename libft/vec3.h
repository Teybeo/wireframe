#ifndef VEC3_H
#define VEC3_H

#define M_PI_F ((float)M_PI)
#define DEG_TO_RAD(X) (((X) / 180.f) * 3.14159f)

#define R_MASK (0x00FF0000)
#define G_MASK (0x0000FF00)
#define B_MASK (0x000000FF)

#define R_SHIFT (16u)
#define G_SHIFT (8u)
#define B_SHIFT (0u)

#define RED(x) ((x & R_MASK) >> R_SHIFT)
#define GREEN(x) ((x & G_MASK) >> G_SHIFT)
#define BLUE(x) ((x & B_MASK) >> B_SHIFT)


struct s_vec3
{
	float x;
	float y;
	float z;
};
typedef struct s_vec3 t_vec3;

struct s_vec4
{
	float x;
	float y;
	float z;
	float w;
};
typedef struct s_vec4 t_vec4;

struct s_vec3i
{
	int x;
	int y;
	int z;
};
typedef struct s_vec3i t_vec3i;

struct s_vec2i
{
	int x;
	int y;
};
typedef struct s_vec2i t_vec2i;

struct s_segment {
	int		start_idx;
	int		end_idx;
};
typedef struct s_segment t_segment;

t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);
t_vec3	vec3_clamp2D(t_vec3 a, t_vec2i limit);
t_vec3 vec3_max(t_vec3 a, t_vec3 b);
t_vec3 vec3_min(t_vec3 a, t_vec3 b);
float vec3_max_axis(t_vec3 a);
t_vec3	vec3_mul_scalar(t_vec3 vec, float scalar);
t_vec3i	vec3_round(t_vec3 vec);
t_vec2i	vec4_round2D(t_vec4 vec);
t_vec4	vec4(t_vec3 v);
int color_mix(float factor, int a, int b);
void	vec4_mul_scalar_this(t_vec4 *vec, float scalar);
void	vec3_sub_this(t_vec3 *a, t_vec3 b);
void	vec3_subXX(t_vec3 *a, float x, float y, float z);
void	vec3_print(char const *msg, t_vec3 vec);

#endif
