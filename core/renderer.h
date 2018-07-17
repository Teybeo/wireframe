#ifndef WIREFRAME_RENDERER_H
#define WIREFRAME_RENDERER_H

#include "map_reader.h"
#include "camera.h"
#include "mat4.h"

#include <array.h>
#include <stdint.h>

#define GRADIENT_COUNT 6

enum e_renderer_key {
	KEY_RUNKNOWN,
	KEY_SCALE_UP,
	KEY_SCALE_DOWN,
	KEY_FOV_UP,
	KEY_FOV_DOWN,
	KEY_RCOUNT
};
typedef enum e_renderer_key t_renderer_key;

struct grad_step
{
	int		color;
	float	treshold;
};
typedef struct grad_step grad_step;

struct s_renderer {
	t_map		map;
	uint32_t	*pixels;
	float		*depth_buffer;
	t_vec2i		size;
	t_camera	camera;
	grad_step	gradient[GRADIENT_COUNT];
	t_mat4		projection;
	float		scale_factor;
	float		fov_angle;
};
typedef struct s_renderer t_renderer;

void renderer_init(t_renderer *renderer, void *pixels, t_map map, t_vec2i size);
void renderer_event(t_renderer* renderer, t_renderer_key key);
void renderer_update(t_renderer *r);
void renderer_draw(t_renderer renderer);
void renderer_draw0(t_renderer renderer);


#endif
