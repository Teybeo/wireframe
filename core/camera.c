#include <libft.h>
#include "camera.h"
#include "stdio.h"

void init_camera(t_camera *camera)
{
	ft_memzero(camera, sizeof(t_camera));
	camera->pos = (t_vec3){0, 0, 5};
}

void camera_key_event(t_camera *camera, t_camera_key key, int state)
{
	printf("Received key: %d, state: %d\n", key, state);

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
}

void camera_update(t_camera *camera)
{
	t_vec3 delta;
	t_vec3 forward;
	t_vec3 upward;
	t_vec3 strafe;

	delta = (t_vec3){};
	forward = (t_vec3){0, 0, -1};
	upward = (t_vec3){0, 1, 0};
	strafe = (t_vec3){1, 0, 0};
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