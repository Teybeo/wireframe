/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_preprocess.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 16:06:44 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/09/18 16:07:35 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WIREFRAME_MAP_PREPROCESS_H
# define WIREFRAME_MAP_PREPROCESS_H

# include "map_reader.h"

# define GRADIENT_COUNT 6

struct	s_grad_step
{
	int		color;
	float	treshold;
};
typedef struct s_grad_step	t_grad_step;

void	do_center_map(t_map *map);
void	compute_boundingbox(t_map *map);
void	compute_colors(t_map *map);
int		get_color_from_height(t_map *map, t_grad_step *gradient, float h);

#endif
