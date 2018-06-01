#ifndef MAP_READER_H
#define MAP_READER_H

#include <array.h>
#include "vec3.h"

t_array load_fdf(char const *filepath);

t_array	generate_point_array(char *line, int y);
t_array	load_map_lines(char const *filepath);
t_array	parse_map_lines(t_array line_array);
void	add_horizontal_segments(t_array *segment_array, t_array point_array);
void	add_vertical_segments(t_array *segment_array,
							  t_array point_array, t_array prev_point_array);


#endif
