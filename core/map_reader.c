#include "map_reader.h"

#include "errors.h"
#include "get_next_line.h"
#include "libft.h"

#include <unistd.h>
#include <fcntl.h>
#include <array.h>
#include <math.h>
#include <stdio.h>

void	do_center_map(t_array *segment_array);

t_array	load_fdf(char const *filepath)
{
	t_array	line_array;
	t_array	segment_array;

	line_array = load_map_lines(filepath);
	segment_array = parse_map_lines(line_array);

	do_center_map(&segment_array);
	return segment_array;
}

t_array	parse_map_lines(t_array line_array)
{
	int		i;
	t_array	point_array;
	t_array	previous_point_array;
	t_array	segment_array;

	i = 0;
	segment_array = array_create(sizeof(t_segment), 16);
	while (i < line_array.size)
	{
		point_array = generate_point_array(((char**)line_array.data)[i], i);
		add_horizontal_segments(&segment_array, point_array);
		if (i >= 1)
			add_vertical_segments(
					&segment_array, point_array, previous_point_array);
		i++;
		previous_point_array = point_array;
	}
	return (segment_array);
}


void	add_vertical_segments(t_array *segment_array,
							  t_array point_array, t_array prev_point_array)
{
	int			i;
	int			count;
	t_segment	segment;
	t_vec3		*point_ptr;
	t_vec3		*prev_point_ptr;

	point_ptr = point_array.data;
	prev_point_ptr = prev_point_array.data;
	i = 0;
	count = (int)fminf(point_array.size, prev_point_array.size);
	while (i < count)
	{
		segment = (t_segment){prev_point_ptr[i], point_ptr[i]};
		array_append(segment_array, &segment, 1);
		i++;
	}
}

void	add_horizontal_segments(t_array *segment_array, t_array point_array)
{
	int			i;
	t_segment	segment;
	t_vec3		*point_ptr;

	point_ptr = point_array.data;
	i = 0;
	while ((i + 1) < point_array.size)
	{
		segment = (t_segment){point_ptr[i], point_ptr[i + 1]};
		array_append(segment_array, &segment, 1);
		i++;
	}
}

t_array	load_map_lines(char const *filepath)
{
	int		i;
	int		fd;
	char	*line;
	int		status;
	t_array	line_array;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		exit_with_message(ERROR_OPEN_FAILED);
	status = GNL_OK;
	line_array = array_create(sizeof(char*), 10);
	i = 0;
	while (status == GNL_OK)
	{
		status = get_next_line(fd, &line);
		if (status == GNL_OK)
			array_append(&line_array, &line, 1);
		i++;
	}
	return (line_array);
}

t_array	generate_point_array(char *line, int y)
{
	t_array	point_array;
	t_vec3	point;
	int		i;

	i = 0;
	point.x = 0;
	point.z = y;
	point_array = array_create(sizeof(t_vec3), 16);
	while (line[i] != '\0')
	{
		if (ft_is_space(line[i]) == false)
		{
			point.y = ft_atoi(&line[i]);

//			vec3_print("x: ", point);
			array_append(&point_array, &point, 1);
			point.x++;
			while (ft_is_space(line[i]) == false && line[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (point_array);
}

t_vec3 get_center(t_array *segment_array)
{
	t_vec3		max;
	t_vec3		min;
	t_segment	*seg_ptr;

	min = (t_vec3){INT_MAX, INT_MAX, INT_MAX};
	max = (t_vec3){INT_MIN, INT_MIN, INT_MIN};

	seg_ptr = segment_array->data;
	int i;
	i = 0;
	while (i < segment_array->size)
	{
		min = vec3_min_2D(min, seg_ptr[i].start);
		min = vec3_min_2D(min, seg_ptr[i].end);

		max = vec3_max_2D(max, seg_ptr[i].start);
		max = vec3_max_2D(max, seg_ptr[i].end);
		i++;
	}
	return vec3_mul_scalar(vec3_sub(max, min), 0.5);
}

void	do_center_map(t_array *segment_array)
{
	t_vec3 center;
	t_segment	*seg_ptr;

	center = get_center(segment_array);
	seg_ptr = segment_array->data;
	int i;
	i = 0;
	while (i < segment_array->size)
	{
		seg_ptr[i].start = vec3_sub(seg_ptr[i].start, center);
		seg_ptr[i].end = vec3_sub(seg_ptr[i].end, center);
		i++;
	}
}
