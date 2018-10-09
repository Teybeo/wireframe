/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_clipping.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 15:02:30 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/10/09 14:35:16 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_CLIPPING_H
# define LINE_CLIPPING_H

# include "vec3.h"

# define INSIDE	0
# define LEFT 	(1 << 0)
# define RIGHT 	(1 << 1)
# define BOTTOM	(1 << 2)
# define TOP 	(1 << 3)

struct	s_area_code
{
	t_vec2i	*point;
	char	code;
};
typedef struct s_area_code	t_area_code;

int		clip_line(t_point *a, t_point *b, t_vec2i window);

#endif
