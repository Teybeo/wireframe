#include <libft.h>
#include <math.h>
#include "camera.h"
#include "stdio.h"

void init_camera(t_camera *camera)
{
	ft_memzero(camera, 1, sizeof(t_camera));
	camera->pos = (t_vec3){0, 0, 50};
	camera->x_angle = 0;
	camera->y_angle = 0;
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
}

void camera_update(t_camera *camera)
{
	t_vec3 delta;
	t_vec3 forward;
	t_vec3 upward;
	t_vec3 strafe;

	if (camera->right_arrow)
		camera->y_angle -= 1;
	if (camera->left_arrow)
		camera->y_angle += 1;
	if (camera->up_arrow)
		camera->x_angle -= 1;
	if (camera->down_arrow)
		camera->x_angle += 1;

	t_mat3 test;
	mat3_set_rotation(-camera->x_angle, -camera->y_angle, &test);
	mat3_set_rotation(camera->x_angle, camera->y_angle, &camera->rotation);

	delta = (t_vec3){};
	forward = (t_vec3){0, 0, -1};
	upward = (t_vec3){0, -1, 0};
	strafe = (t_vec3){1, 0, 0};
	printf("\n");
	mat3_print("test matrix", &test);

	mat3_mul_vec3X(&test, &forward);
	mat3_mul_vec3X(&test, &strafe);
	mat3_mul_vec3X(&test, &upward);

	vec3_print("forward: ", forward);
	vec3_print("upward: ", upward);
	vec3_print("strafe: ", strafe);

	t_vec3 f, s, u;

	forward.x =  sinf(DEG_TO_RAD(-camera->y_angle)) * cosf(DEG_TO_RAD(-camera->x_angle));
	forward.y = -sinf(DEG_TO_RAD(-camera->x_angle));
	forward.z = -cosf(DEG_TO_RAD(-camera->y_angle)) * cosf(DEG_TO_RAD(-camera->x_angle));

	strafe.x = cosf(DEG_TO_RAD(-camera->y_angle));
	strafe.y = 0;
	strafe.z = sinf(DEG_TO_RAD(-camera->y_angle));

	vec3_print("f: ", f);
	vec3_print("u: ", u);
	vec3_print("s: ", s);

	if (camera->move_forward)
		delta = vec3_add(delta, forward);
	if (camera->move_backward)
		delta = vec3_sub(delta, forward);
	if (camera->strafe_right)
		delta = vec3_add(delta, strafe);
	if (camera->strafe_left)
		delta = vec3_sub(delta, strafe);
	if (camera->move_upward)
		delta = vec3_add(delta, upward);
	if (camera->move_downward)
		delta = vec3_sub(delta, upward);

	camera->pos = vec3_add(camera->pos, delta);
}