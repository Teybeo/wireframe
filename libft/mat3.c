#include "mat3.h"

#include <math.h>
#include "vec3.h"
#include "libft.h"

void mat3_set_identity(t_mat3 *m)
{
	ft_memzero(m, 3 * 3, sizeof(float));
	m->values[0][0] = 1;
	m->values[1][1] = 1;
	m->values[2][2] = 1;
}

t_mat3	mat3_mul2(t_mat3 a, t_mat3 b);

void mat3_set_rotation(float x_angle, float y_angle, t_mat3 *m)
{
	t_mat3 x_rotation;
	t_mat3 y_rotation;

	mat3_set_identity(&x_rotation);
	mat3_set_identity(&y_rotation);

	mat3_set_x_rotation(&x_rotation, x_angle);
	mat3_set_y_rotation(&y_rotation, y_angle);

	*m = mat3_mul2(x_rotation, y_rotation);
//	*m = mat3_mul(x_rotation, y_rotation);
}

/*
** .,     .,    .
** .,   cos,  sin
** .,  -sin,  cos
*/
void mat3_set_x_rotation(t_mat3 *m, float angle) {
	m->values[1][1] =  cosf(angle);
	m->values[1][2] =  sinf(angle);
	m->values[2][1] = -sinf(angle);
	m->values[2][2] =  cosf(angle);
}

/*
** cos, ., -sin
**   ., .,   .
** sin, ., cos
*/
void mat3_set_y_rotation(t_mat3 *m, float angle) {
	m->values[0][0] =  cosf(angle);
	m->values[0][2] =  sinf(angle);
	m->values[2][0] = -sinf(angle);
	m->values[2][2] =  cosf(angle);
}

void swap_float(float *a, float *b) {
	float temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

/*
** T(AB) = T(B) x T(A)
*/

t_mat3 mat3_transpose(t_mat3 m)
{
	t_mat3 res;

	res = m;
	swap_float(&res.values[0][1], &res.values[1][0]);
	swap_float(&res.values[0][2], &res.values[2][0]);
	swap_float(&res.values[1][2], &res.values[2][1]);
	return (res);
}

/*
** AB[i][j] = A.line[i] dot B.column[j]
*/

t_mat3 mat3_mul(t_mat3 lhs, t_mat3 rhs)
{
	t_mat3 res;
	int i;
	int j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			res.values[i][j] =
				lhs.values[i][0] * rhs.values[0][j] +
				lhs.values[i][1] * rhs.values[1][j] +
				lhs.values[i][2] * rhs.values[2][j];
		}
	}
	return res;
}

t_mat3	mat3_mul2(t_mat3 a, t_mat3 b)
{
	t_mat3 res;
	t_vec3 column;
	int i;

	i = -1;
	while (++i < 3)
	{
		column = mat3_get_column(b, i);
		mat3_mul_vec3X(&a, &column);
		res.values[0][i] = column.x;
		res.values[1][i] = column.y;
		res.values[2][i] = column.z;
	}
	return res;
}

t_vec3 mat3_mul_vec3(t_mat3 *m, t_vec3 vec) {
	t_vec3 result = vec;
	result.x = (vec.x * m->values[0][0] +
				vec.y * m->values[0][1] +
				vec.z * m->values[0][2]);

	result.y = (vec.x * m->values[1][0] +
				vec.y * m->values[1][1] +
				vec.z * m->values[1][2]);

	result.z = (vec.x * m->values[2][0] +
				vec.y * m->values[2][1] +
				vec.z * m->values[2][2]);

	return result;
}

void mat3_mul_vec3X(t_mat3 *m, t_vec3 *vec) {
	t_vec3 tmp = *vec;
	vec->x = (tmp.x * m->values[0][0] +
			  tmp.y * m->values[0][1] +
			  tmp.z * m->values[0][2]);

	vec->y = (tmp.x * m->values[1][0] +
			  tmp.y * m->values[1][1] +
			  tmp.z * m->values[1][2]);

	vec->z = (tmp.x * m->values[2][0] +
			  tmp.y * m->values[2][1] +
			  tmp.z * m->values[2][2]);
}

t_vec3	mat3_get_column(t_mat3 m, int column)
{
	t_vec3	vec;
	vec.x = m.values[0][column];
	vec.y = m.values[1][column];
	vec.z = m.values[2][column];
	return (vec);
}

#include <stdio.h>
void mat3_print(char const *msg, t_mat3 *m)
{
	printf("%s\n", msg);
	printf("%10.7g, %10.7g, %10.7g\n", m->values[0][0], m->values[0][1], m->values[0][2]);
	printf("%10.7g, %10.7g, %10.7g\n", m->values[1][0], m->values[1][1], m->values[1][2]);
	printf("%10.7g, %10.7g, %10.7g\n", m->values[2][0], m->values[2][1], m->values[2][2]);
}
