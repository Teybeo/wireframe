#ifndef WIREFRAME_MAP_PREPROCESS_H
#define WIREFRAME_MAP_PREPROCESS_H

#include "map_reader.h"

typedef struct grad_step grad_step;

void	do_center_map(t_map *map);
void	compute_boundingbox(t_map *map);
void	compute_colors(t_map *map);
int		get_color_from_height2(t_map *map, grad_step *gradient, float h);

#endif
