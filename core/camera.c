#include <libft.h>
#include <math.h>
#include <stdlib.h>
#include "camera.h"
#include "stdio.h"

void init_camera(t_camera *camera, float speed_factor)
{
	ft_memzero(camera, 1, sizeof(t_camera));
	camera->pos = (t_vec3){0, 0, 0};
	camera->x_angle = 0;
	camera->y_angle = 0;
	camera->mode = CAMERA_FREEFLY;
	camera->speed_factor = speed_factor;
}

void camera_key_event(t_camera *camera, t_camera_key key, int state)
{
//	printf("Received key: %d, state: %d\n", key, state);

	if (key == KEY_FORWARD)
		camera->move_forward = (bool)state;
	if (key == KEY_BACKWARD)
		camera->move_backward = (bool)state;
	if (key == KEY_RIGHT)
		camera->strafe_right = (bool)state;
	if (key == KEY_LEFT)
		camera->strafe_left = (bool)state;
	if (key == KEY_UPWARD)
		camera->move_upward = (bool)state;
	if (key == KEY_DOWNWARD)
		camera->move_downward = (bool)state;
	if (key == KEY_DOWN_ARROW)
		camera->down_arrow = (bool)state;
	if (key == KEY_UP_ARROW)
		camera->up_arrow = (bool)state;
	if (key == KEY_RIGHT_ARROW)
		camera->right_arrow = (bool)state;
	if (key == KEY_LEFT_ARROW)
		camera->left_arrow = (bool)state;

	if (key == KEY_CAMERA_MODE_TOGGLE && state == 0)
		camera->mode = (t_camera_mode)!camera->mode;
	if (key == KEY_CAMERA_RESET && state == 0)
	{
		camera->pos = (t_vec3){0, 0, 0};
		camera->x_angle = 0;
		camera->y_angle = 0;
	}
	if (key == KEY_CAMERA_PRINT_POS && state == 0)
	{
		vec3_print("Camera pos: ", camera->pos);
		printf("x_angle: %g, y_angle: %g\n", camera->x_angle, camera->y_angle);
	}

}

void	camera_mouse_event(t_camera *camera, int x, int y)
{
	camera->y_angle -= x * 0.005f;
	camera->x_angle -= y * 0.005f;
}

void camera_update(t_camera *camera)
{
	t_vec3 delta;
	t_vec3 backward;
	t_vec3 upward;
	t_vec3 strafe;

	if (camera->right_arrow)
		camera->y_angle -= 0.05;
	if (camera->left_arrow)
		camera->y_angle += 0.05;
	if (camera->up_arrow)
		camera->x_angle += 0.05;
	if (camera->down_arrow)
		camera->x_angle -= 0.05;

	mat3_set_rotation(camera->x_angle, camera->y_angle, &camera->rotation);
	t_mat3 temp;
	mat3_set_rotation2(camera->x_angle, camera->y_angle, &temp);

	if (camera->mode == CAMERA_FREEFLY) {
		if (0)
		{
			backward.x =  sinf(camera->y_angle) * cosf(camera->x_angle);
			backward.y = -sinf(camera->x_angle);
			backward.z = cosf(camera->y_angle) * cosf(camera->x_angle);

			strafe.x = cosf(camera->y_angle);
			strafe.y = 0;
			strafe.z = sinf(-camera->y_angle);

			upward.x = sinf(camera->x_angle) * sinf(camera->y_angle);
			upward.y = cosf(camera->x_angle);
			upward.z = sinf(camera->x_angle) * cosf(camera->y_angle);
	//		upward = vec3_cross(strafe, backward);
		}
		else
		{
			strafe.x = temp.values[0][0];
			strafe.y = temp.values[1][0];
			strafe.z = temp.values[2][0];

			upward.x = temp.values[0][1];
			upward.y = temp.values[1][1];
			upward.z = temp.values[2][1];

			backward.x = temp.values[0][2];
			backward.y = temp.values[1][2];
			backward.z = temp.values[2][2];
		}
	}
	else {
		backward = (t_vec3){0, 0, 1};
		upward = (t_vec3){0, 1, 0};
		strafe = (t_vec3){1, 0, 0};
	}
	delta = (t_vec3){};

	if (camera->move_forward)
		delta = vec3_sub(delta, backward);
	if (camera->move_backward)
		delta = vec3_add(delta, backward);
	if (camera->strafe_right)
		delta = vec3_add(delta, strafe);
	if (camera->strafe_left)
		delta = vec3_sub(delta, strafe);
	if (camera->move_upward)
		delta = vec3_add(delta, upward);
	if (camera->move_downward)
		delta = vec3_sub(delta, upward);

	delta = vec3_mul_scalar(delta, camera->speed_factor);
	camera->pos = vec3_add(camera->pos, delta);
}
