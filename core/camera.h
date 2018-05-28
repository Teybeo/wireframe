#ifndef CAMERA_H
#define CAMERA_H

#include "map_reader.h"

struct s_camera {
	t_vec3 pos;
};

typedef struct s_camera t_camera;

void init_camera(t_camera *camera);

#endif
