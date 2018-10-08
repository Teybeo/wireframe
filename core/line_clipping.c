/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_clipping.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 14:53:45 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/10/08 19:16:21 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_clipping.h"

/*
** Viewport is implicitly defined as [0, 0] -> [window.x, window.y]
** Maybe need to handle arbitrary viewport origin ?
*/

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

void	clip_point(t_vec2i a, t_vec2i b, t_vec2i window, t_area_code *code_ptr)
{
	t_vec2i ab;

	ab = (t_vec2i) {b.x - a.x, b.y - a.y};
	if (code_ptr->code & LEFT)
	{
		code_ptr->point->x = 0;
		code_ptr->point->y = a.y + (0 - a.x) * ab.y / ab.x;
	}
	else if (code_ptr->code & RIGHT)
	{
		code_ptr->point->x = window.x - 1;
		code_ptr->point->y = a.y + (window.x - a.x) * ab.y / ab.x;
	}
	else if (code_ptr->code & TOP)
	{
		code_ptr->point->x = a.x + (0 - a.y) * ab.x / ab.y;
		code_ptr->point->y = 0;
	}
	else if (code_ptr->code & BOTTOM)
	{
		code_ptr->point->x = a.x + (window.y - a.y) * ab.x / ab.y;
		code_ptr->point->y = window.y - 1;
	}
	code_ptr->code = get_area_code(*code_ptr->point, window);
}

/*
** Returns 1 when the 2 points are inside window
** Returns 0 when the 2 points have one or more common area (safe discard)
*/

int		clip_line_2D(t_vec2i *a, t_vec2i *b, t_vec2i window)
{
	t_area_code	code_a;
	t_area_code	code_b;
	t_area_code	*code_to_clip;

	code_a = (t_area_code){a, get_area_code(*a, window)};
	code_b = (t_area_code){b, get_area_code(*b, window)};
	while (42)
	{
		if ((code_a.code | code_b.code) == INSIDE)
			return (1);
		if (code_a.code & code_b.code)
			return (0);
		if (code_a.code != INSIDE)
			code_to_clip = &code_a;
		else
			code_to_clip = &code_b;
		clip_point(*a, *b, window, code_to_clip);
	}
}

int		clip_line(t_point *a, t_point *b, t_vec2i window)
{
	return (clip_line_2D((t_vec2i*)a, (t_vec2i*)b, window));
}
