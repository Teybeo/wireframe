/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 16:01:17 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/10/09 17:32:03 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
#include <stdbool.h>

void	parse_map_lines(t_map *map, t_array txt_line_array)
{
	int		i;
	t_array	point_array;
	t_array	previous_point_array;

	i = 0;
	map->segment_array = array_create(sizeof(t_segment), 16);
	map->vertex_array = array_create(sizeof(t_vec4), 16);
	while (i < txt_line_array.size)
	{
		point_array = generate_point_array(((char**)txt_line_array.data)[i], i);
		add_horizontal_segments(map, point_array);
		if (i >= 1)
		{
			add_vertical_segments(map, point_array, previous_point_array);
			free(previous_point_array.data);
		}
		array_append(&map->vertex_array, point_array.data,
				(size_t)point_array.size);
		previous_point_array = point_array;
		i++;
	}
	free(point_array.data);
}

void	add_horizontal_segments(t_map *map, t_array point_array)
{
	int			i;
	int			base_index;
	t_segment	segment;

	base_index = map->vertex_array.size;
	i = 0;
	while ((i + 1) < point_array.size)
	{
		segment = (t_segment){base_index + i, base_index + i + 1};
		array_append(&map->segment_array, &segment, 1);
		i++;
	}
}

void	add_vertical_segments(t_map *map,
							t_array point_array, t_array prev_point_array)
{
	int			i;
	int			count;
	int			up_base_index;
	int			down_base_index;
	t_segment	segment;

	up_base_index = map->vertex_array.size - prev_point_array.size;
	down_base_index = map->vertex_array.size;
	i = 0;
	count = (int)fminf(point_array.size, prev_point_array.size);
	while (i < count)
	{
		segment = (t_segment){i + up_base_index, i + down_base_index};
		array_append(&map->segment_array, &segment, 1);
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
	line_array = array_create(sizeof(char*), 256);
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
	t_vec4	point;
	int		i;

	i = 0;
	point.x = 0;
	point.z = y;
	point.w = 0;
	point_array = array_create(sizeof(t_vec4), 256);
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
