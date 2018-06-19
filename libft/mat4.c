#include "mat4.h"
#include "libft.h"

void	mat4_identity(t_mat4 *m)
{
	ft_memzero(m->values, 16, sizeof(float));
	m->values[0][0] = 1;
	m->values[1][1] = 1;
	m->values[2][2] = 1;
	m->values[3][3] = 1;
}

void	init_with_mat3(t_mat4 *mat4, t_mat3 mat3)
{
	mat4->values[0][0] = mat3.values[0][0];
	mat4->values[0][1] = mat3.values[0][1];
	mat4->values[0][2] = mat3.values[0][2];
	mat4->values[0][3] = 0;

	mat4->values[1][0] = mat3.values[1][0];
	mat4->values[1][1] = mat3.values[1][1];
	mat4->values[1][2] = mat3.values[1][2];
	mat4->values[1][3] = 0;

	mat4->values[2][0] = mat3.values[2][0];
	mat4->values[2][1] = mat3.values[2][1];
	mat4->values[2][2] = mat3.values[2][2];
	mat4->values[2][3] = 0;

	mat4->values[3][0] = 0;
	mat4->values[3][1] = 0;
	mat4->values[3][2] = 0;
	mat4->values[3][3] = 1;
}

void	mat4_translate_by(t_mat4 *mat4, t_vec3 vec)
{
	mat4->values[0][3] += -vec.x;
	mat4->values[1][3] += -vec.y;
	mat4->values[2][3] += -vec.z;
}

void	mat4_mul_vec(t_mat4 *mat, t_vec3 *vec)
{
	t_vec3 temp = *vec;
	vec->x = temp.x * mat->values[0][0] +
			temp.y * mat->values[0][1] +
			temp.z * mat->values[0][2] +
			1 * mat->values[0][3];

	vec->y = temp.x * mat->values[1][0] +
			temp.y * mat->values[1][1] +
			temp.z * mat->values[1][2] +
			1 * mat->values[1][3];

	vec->z = temp.x * mat->values[2][0] +
			temp.y * mat->values[2][1] +
			temp.z * mat->values[2][2] +
			1 * mat->values[2][3];
}

void	mat4_mul(t_mat4 *a, t_mat4 *b)
{
	t_mat4 res;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			res.values[i][j] =
					a->values[i][0] * b->values[0][j] +
					a->values[i][1] * b->values[1][j] +
					a->values[i][2] * b->values[2][j] +
					a->values[i][3] * b->values[3][j];
		}
	}
	*a = res;
}