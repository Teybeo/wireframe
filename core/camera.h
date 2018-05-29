#ifndef CAMERA_H
#define CAMERA_H

#include <stdbool.h>
#include "map_reader.h"

enum e_camera_key {
	KEY_FORWARD,
	KEY_BACKWARD,
	KEY_RIGHT,
	KEY_LEFT,
	KEY_UPWARD,
	KEY_DOWNWARD,
};
typedef enum e_camera_key t_camera_key;

struct s_camera {
	t_vec3 pos;
	bool move_forward;
	bool move_backward;
	bool strafe_right;
	bool strafe_left;
	bool move_upward;
	bool move_downward;
};

typedef struct s_camera t_camera;

void	init_camera(t_camera *camera);
void	camera_key_event(t_camera *camera, t_camera_key key, int state);
void	camera_update(t_camera *camera);

#endif
