/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 17:36:16 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/10/09 17:36:16 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_reader.h"

#include "map_preprocess.h"

#include <stdlib.h>

t_map	load_fdf(char const *filepath)
{
	t_map	map;
	t_array	line_array;

	line_array = load_text_lines(filepath);
	parse_map_lines(&map, line_array);
	compute_boundingbox(&map);
	do_center_map(&map);
	compute_colors(&map);
	free(line_array.data);
	shrink_to_fit(&map.segment_array);
	shrink_to_fit(&map.vertex_array);
	print_stats(map.segment_array, "segment_array");
	print_stats(map.vertex_array, "vertex_array");
	return (map);
}
