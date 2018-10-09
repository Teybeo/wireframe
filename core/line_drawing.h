/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 15:02:59 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/10/09 17:50:57 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_DRAWING_H
# define LINE_DRAWING_H

# include "vec3.h"
# include "renderer.h"
# include "rgb.h"

struct	s_hax_x {
	int		x;
	float	y;
	float	z;
	t_rgb	color;
};
typedef struct s_hax_x	t_hax_x;

struct	s_hax_y {
	float	x;
	int		y;
	float	z;
	t_rgb	color;
};
typedef struct s_hax_y	t_hax_y;

void	draw_line(t_renderer *rndr, t_point a, t_point b);

#endif
