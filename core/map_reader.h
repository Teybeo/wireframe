#ifndef MAP_READER_H
#define MAP_READER_H

#include <array.h>

struct s_point {
	int x;
	int y;
	int z;
};
typedef struct s_point t_point;

struct s_segment {
	t_point start;
	t_point end;
};
typedef struct s_segment t_segment;

t_array load_fdf(char const *filepath);

static t_array generate_point_array(char *line, int y);
static t_array	load_map_lines(char const *filepath);
static t_array parse_map_lines(t_array line_array);
void	add_horizontal_segments(t_array *segment_array, t_array point_array);
void	add_vertical_segments(t_array *segment_array,
							  t_array point_array, t_array prev_point_array);


#endif
