/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_clipping.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 15:02:30 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/09/05 15:02:30 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_CLIPPING_H
# define LINE_CLIPPING_H

# include "vec3.h"

# define INSIDE	0
# define LEFT 	(1 << 1)
# define RIGHT 	(1 << 2)
# define BOTTOM	(1 << 3)
# define TOP 	(1 << 4)

int clip_line(t_vec2i *a, t_vec2i *b, t_vec2i window);

#endif
