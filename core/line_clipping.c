/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_clipping.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 14:53:45 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/10/08 19:05:55 by tdarchiv         ###   ########.fr       */
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

//#define OLD_CLIP gre

#ifdef OLD_CLIP

/*
** Returns OK when the 2 points are inside window
 * Returns KO when the 2 points
**/

int		clip_line_2D(t_vec2i *a, t_vec2i *b, t_vec2i window)
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
		if (area_code_a & area_code_b)
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

#else

struct	s_area_code
{
	t_vec2i	*point;
	char	code;
};
typedef struct s_area_code	t_area_code;

void	clip_point(t_vec2i a, t_vec2i b, t_vec2i window, t_area_code *code_ptr);

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

#endif

int		clip_line_old(t_vec3i *a, t_vec3i *b, t_vec2i window)
{
	return (clip_line_2D((t_vec2i*)a, (t_vec2i*)b, window));
}

int		clip_line(t_point *a, t_point *b, t_vec2i window)
{
	return (clip_line_2D((t_vec2i*)a, (t_vec2i*)b, window));
}
