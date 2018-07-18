#include "map_preprocess.h"

#include "vec3.h"

#include <limits.h>

void compute_boundingbox(t_map *map)
{
	t_vec3		max;
	t_vec3		min;
	t_segment	*seg_ptr;

	min = (t_vec3){INT_MAX, INT_MAX, INT_MAX};
	max = (t_vec3){INT_MIN, INT_MIN, INT_MIN};

	seg_ptr = map->segment_array.data;
	int i;
	i = 0;
	while (i < map->segment_array.size)
	{
		min = vec3_min_2D(min, seg_ptr[i].start);
		min = vec3_min_2D(min, seg_ptr[i].end);

		max = vec3_max_2D(max, seg_ptr[i].start);
		max = vec3_max_2D(max, seg_ptr[i].end);
		i++;
	}
	map->min = min;
	map->max = max;
}

void	do_center_map(t_map *map)
{
	t_vec3 center;
	t_segment	*seg_ptr;

	center = vec3_mul_scalar(vec3_sub(map->max, map->min), 0.5);
	center.y = 0;
	seg_ptr = map->segment_array.data;
	int i;
	i = 0;
	while (i < map->segment_array.size)
	{
		seg_ptr[i].start = vec3_sub(seg_ptr[i].start, center);
		seg_ptr[i].end = vec3_sub(seg_ptr[i].end, center);
		i++;
	}
}
