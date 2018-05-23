#ifndef WIREFRAME_RENDERER_H
#define WIREFRAME_RENDERER_H

#include <array.h>
#include <stdint.h>
#include "map_reader.h"

struct s_renderer {
	t_array		segment_array;
	uint32_t	*pixels;
	t_point		size;
};
typedef struct s_renderer t_renderer;

void renderer_init(t_renderer *renderer, t_array array, t_point point);
void renderer_draw(t_renderer renderer);
void renderer_event(t_renderer* renderer);

#endif //WIREFRAME_RENDERER_H
