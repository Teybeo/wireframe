#ifndef WIREFRAME_RENDERER_H
#define WIREFRAME_RENDERER_H

#include "map_reader.h"
#include "camera.h"

#include <array.h>
#include <stdint.h>

struct s_renderer {
	t_array		segment_array;
	uint32_t	*pixels;
	t_vec2i		size;
	t_camera	camera;
};
typedef struct s_renderer t_renderer;

void renderer_init(t_renderer *renderer, void *pixels, t_array array, t_vec2i size);
void renderer_event(t_renderer* renderer);
void renderer_update(t_renderer *renderer);
void renderer_draw(t_renderer renderer);


#endif //WIREFRAME_RENDERER_H
