/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 15:05:52 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/10/09 17:32:03 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_READER_H
# define MAP_READER_H

# include "array.h"
# include "vec3.h"

struct	s_map
{
	t_array segment_array;
	t_array vertex_array;
	t_vec3	min;
	t_vec3	max;
};
typedef struct s_map	t_map;

t_map	load_fdf(char const *filepath);

t_array	generate_point_array(char *line, int y);
t_array	load_text_lines(char const *filepath);
void	parse_map_lines(t_map *map, t_array txt_line_array);
void	add_horizontal_segments(t_map *map, t_array point_array);
void	add_vertical_segments(t_map *map,
							t_array point_array, t_array prev_point_array);
#endif
