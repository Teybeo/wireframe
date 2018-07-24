#include <math.h>
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
	mat4->values[0][3] -= vec.x;
	mat4->values[1][3] -= vec.y;
	mat4->values[2][3] -= vec.z;
}

void	mat4_mul_vec(t_mat4 *mat, t_vec4 *vec)
{
	t_vec4 temp = *vec;
	vec->x = temp.x * mat->values[0][0] +
			temp.y * mat->values[0][1] +
			temp.z * mat->values[0][2] +
			temp.w * mat->values[0][3];

	vec->y = temp.x * mat->values[1][0] +
			temp.y * mat->values[1][1] +
			temp.z * mat->values[1][2] +
			temp.w * mat->values[1][3];

	vec->z = temp.x * mat->values[2][0] +
			temp.y * mat->values[2][1] +
			temp.z * mat->values[2][2] +
			temp.w * mat->values[2][3];

	vec->w = temp.x * mat->values[3][0] +
			temp.y * mat->values[3][1] +
			temp.z * mat->values[3][2] +
			temp.w * mat->values[3][3];
}

void mat4_mul_ptr(t_mat4 *this, t_mat4 const *lhs, t_mat4 const *rhs)
{
	int i;
	int j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			this->values[i][j] =
					lhs->values[i][0] * rhs->values[0][j] +
					lhs->values[i][1] * rhs->values[1][j] +
					lhs->values[i][2] * rhs->values[2][j] +
					lhs->values[i][3] * rhs->values[3][j];
		}
	}
}

void mat4_mul_this(t_mat4 *lhs, t_mat4 const *rhs)
{
	t_mat4 res;
	int i;
	int j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			res.values[i][j] =
					lhs->values[i][0] * rhs->values[0][j] +
					lhs->values[i][1] * rhs->values[1][j] +
					lhs->values[i][2] * rhs->values[2][j] +
					lhs->values[i][3] * rhs->values[3][j];
		}
	}
	*lhs = res;
}

t_mat4 mat4_mul(t_mat4 lhs, t_mat4 rhs)
{
	t_mat4 res;
	int i;
	int j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			res.values[i][j] =
					lhs.values[i][0] * rhs.values[0][j] +
					lhs.values[i][1] * rhs.values[1][j] +
					lhs.values[i][2] * rhs.values[2][j] +
					lhs.values[i][3] * rhs.values[3][j];
		}
	}
	return res;
}

void set_perspective(t_mat4 *m, float near, float far, float aspect_ratio, float fov_angle)
{
	// Distance from a projection screen of unit width
	float distance = 1.f / tanf((fov_angle / 2) * M_PI_F / 180);
	float z_factor = (-far + near) / (far - near);
	float z_translation = ((2 * far * near) / (far - near));

	mat4_identity(m);
	m->values[0][0] = distance * aspect_ratio;
	m->values[1][1] = distance;
	m->values[2][2] = z_factor;
	m->values[2][3] = -z_translation;
	m->values[3][2] = -1;
	m->values[3][3] = 0;
}
#if 1
void	set_orthographic(t_mat4 *m, float width, float height, float zNear, float zFar)
{
	float right = (width / 2);
	float left = -(width / 2);
	float top = (height / 2);
	float bottom = -(height / 2);
	mat4_identity(m);
	m->values[0][0] =  2 / (right - left);
	m->values[1][1] =  2 / (top - bottom);
	m->values[2][2] = -2 / (zFar - zNear);
	m->values[0][3] = - (right + left) / (right - left);
	m->values[1][3] = - (top + bottom) / (top - bottom);
	m->values[2][3] = - (zFar + zNear) / (zFar - zNear);
}
#else
void	set_orthographic(t_mat4 *m, float width, float height, float zNear, float zFar)
{
	float right = (width / 2);
	float top = (height / 2);
	mat4_identity(m);
	m->values[0][0]  =  1 / right;
	m->values[1][1]  =  1 / top;
	m->values[2][2]  = -2 / (zFar - zNear);
}
#endif