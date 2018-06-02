#ifndef CAMERA_H
#define CAMERA_H

#include <stdbool.h>
#include <mat3.h>
#include "map_reader.h"

enum e_camera_key {
	KEY_FORWARD,
	KEY_BACKWARD,
	KEY_RIGHT,
	KEY_LEFT,
	KEY_UPWARD,
	KEY_DOWNWARD,
	KEY_UP_ARROW,
	KEY_DOWN_ARROW,
	KEY_LEFT_ARROW,
	KEY_RIGHT_ARROW,
	KEY_COUNT,
};
typedef enum e_camera_key t_camera_key;

struct s_camera {
	t_vec3 pos;
	t_mat3 rotation;
	float y_angle;
	float x_angle;
	bool move_forward;
	bool move_backward;
	bool strafe_right;
	bool strafe_left;
	bool move_upward;
	bool move_downward;
	bool up_arrow;
	bool down_arrow;
	bool left_arrow;
	bool right_arrow;
};

typedef struct s_camera t_camera;

void	init_camera(t_camera *camera);
void	camera_key_event(t_camera *camera, t_camera_key key, int state);
void	camera_update(t_camera *camera);

#endif
