/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_clipping.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 14:53:45 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/09/05 14:54:43 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_clipping.h"

/*
** Viewport is implicitly defined as [0, 0] -> [window.x, window.y]
** Maybe need to handle arbitrary viewport origin ?
*/
int		clip_line_int(t_vec2i *a, t_vec2i *b, t_vec2i window);

char	get_area_code(t_vec2i point, t_vec2i window)
{
	char area_code;

	area_code = 0;
	area_code |= (point.x < 0) * LEFT;
	area_code |= (point.x >= window.x) * RIGHT;
	area_code |= (point.y < 0) * TOP;
	area_code |= (point.y >= window.y) * BOTTOM;
	return (area_code);
}

int		clip_line(t_vec2i *a, t_vec2i *b, t_vec2i window)
{
	char	area_code_a;
	char	area_code_b;
	char	*code_to_clip;
	t_vec2i *point;

	area_code_a = get_area_code(*a, window);
	area_code_b = get_area_code(*b, window);
	while (42)
	{
		if ((area_code_a | area_code_b) == INSIDE)
			return (1);
		if ((area_code_a & area_code_b) != INSIDE)
			return (0);
		if (area_code_a != INSIDE)
		{
			point = a;
			code_to_clip = &area_code_a;
		}
		else if (area_code_b != INSIDE)
		{
			point = b;
			code_to_clip = &area_code_b;
		}
		if (*code_to_clip & LEFT)
		{
			point->y = a->y + (0 - a->x) * (b->y - a->y) / (b->x - a->x);
			point->x = 0;
		}
		else if (*code_to_clip & RIGHT)
		{
			point->y = a->y + (window.x - a->x) * (b->y - a->y) / (b->x - a->x);
			point->x = window.x - 1;
		}
		else if (*code_to_clip & TOP)
		{
			point->x = a->x + (0 - a->y) * (b->x - a->x) / (b->y - a->y);
			point->y = 0;
		}
		else if (*code_to_clip & BOTTOM)
		{
			point->x = a->x + (window.y - a->y) * (b->x - a->x) / (b->y - a->y);
			point->y = window.y - 1;
		}
		*code_to_clip = get_area_code(*point, window);
	}
}
