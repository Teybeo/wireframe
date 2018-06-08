#ifndef WIREFRAME_RENDERER_H
#define WIREFRAME_RENDERER_H

#include "map_reader.h"
#include "camera.h"

#include <array.h>
#include <stdint.h>

#define M_PI_F ((float)M_PI)

enum e_renderer_key {
	KEY_RUNKNOWN,
	KEY_SCALE_UP,
	KEY_SCALE_DOWN,
	KEY_FOV_UP,
	KEY_FOV_DOWN,
	KEY_RCOUNT,
};
typedef enum e_renderer_key t_renderer_key;

struct s_renderer {
	t_array		segment_array;
	uint32_t	*pixels;
	t_vec2i		size;
	t_camera	camera;
	float		scale_factor;
	float		fov_angle;
};
typedef struct s_renderer t_renderer;

void renderer_init(t_renderer *renderer, void *pixels, t_array array, t_vec2i size);
void renderer_event(t_renderer* renderer, t_renderer_key key);
void renderer_update(t_renderer *renderer);
void renderer_draw(t_renderer renderer);


#endif //WIREFRAME_RENDERER_H
