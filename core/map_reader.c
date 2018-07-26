#include "map_reader.h"

#include "errors.h"
#include "get_next_line.h"
#include "libft.h"
#include "map_preprocess.h"

#include <unistd.h>
#include <fcntl.h>
#include <array.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

t_map	load_fdf(char const *filepath)
{
	t_map	map;
	t_array	line_array;

	line_array = load_text_lines(filepath);
	map.segment_array = parse_map_lines(line_array);
	compute_boundingbox(&map);
	do_center_map(&map);
	compute_colors(&map);
	free(line_array.data);
	print_stats(map.segment_array, "segment_array");
	shrink_to_fit(&map.segment_array);
	print_stats(map.segment_array, "segment_array");
	return map;
}

t_array	parse_map_lines(t_array txt_line_array)
{
	int		i;
	t_array	point_array;
	t_array	previous_point_array;
	t_array	segment_array;

	i = 0;
	segment_array = array_create(sizeof(t_segment), 16);
	while (i < txt_line_array.size)
	{
		point_array = generate_point_array(((char**)txt_line_array.data)[i], i);
		add_horizontal_segments(&segment_array, point_array);
		if (i >= 1)
		{
			add_vertical_segments(
					&segment_array, point_array, previous_point_array);
			free(previous_point_array.data);
		}
		previous_point_array = point_array;
		i++;
	}
	free(point_array.data);
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
		segment = (t_segment){prev_point_ptr[i], 0, point_ptr[i], 0};
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
		segment = (t_segment){point_ptr[i], 0, point_ptr[i + 1], 0};
		array_append(segment_array, &segment, 1);
		i++;
	}
}

t_array	load_text_lines(char const *filepath)
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
			array_append(&point_array, &point, 1);
			point.x++;
			while (ft_is_space(line[i]) == false && line[i] != '\0')
				i++;
		}
		else
			i++;
	}
	free(line);
	print_stats(point_array, "point_array");
	return (point_array);
}
