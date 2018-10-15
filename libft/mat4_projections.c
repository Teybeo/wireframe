#include "mat4.h"

#include <math.h>

void	set_perspective(t_mat4 *m, float near, float far, float aspect_ratio, float fov_angle)
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
