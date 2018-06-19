#ifndef MAT4_H
#define MAT4_H

#include "mat3.h"

struct s_mat4
{
	float values[4][4];
};
typedef struct s_mat4 t_mat4;

void	init_with_mat3(t_mat4 *mat4, t_mat3 mat3);
void	mat4_translate_by(t_mat4 *mat4, t_vec3 vec);
void	mat4_mul_vec(t_mat4 *mat, t_vec3 *vec);
void	mat4_mul(t_mat4 *a, t_mat4 *b);
void	mat4_identity(t_mat4 *m);

#endif
