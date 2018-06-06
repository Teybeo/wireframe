#ifndef MAT3_H
#define MAT3_H

#include "vec3.h"

struct s_mat3
{
	float values[3][3];
};
typedef struct s_mat3 t_mat3;

t_mat3	mat3_mul(t_mat3 lhs, t_mat3 rhs);
void	mat3_set_rotation(float x_angle, float y_angle, t_mat3 *m);
void	mat3_set_y_rotation(t_mat3 *m, float angle);
void	mat3_set_x_rotation(t_mat3 *m, float angle);
t_vec3	mat3_mul_vec3(t_mat3 *m, t_vec3 vec);
void	mat3_set_identity(t_mat3 *m);
inline void mat3_mul_vec3X(t_mat3 *m, t_vec3 *vec);
void mat3_print(char const *msg, t_mat3 *m);

#endif
