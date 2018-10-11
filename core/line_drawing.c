/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 17:53:31 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/10/09 17:54:43 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_drawing.h"

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

bool	prepare_draw_line_x(t_point a, t_point b, t_hax_x *start, t_hax_x *incr)
{
	t_vec2i	ab;
	t_vec2i	direction;

	ab = (t_vec2i){b.x - a.x, b.y - a.y};
	if (ab.x == 0)
		return (false);
	direction.x = (ab.x > 0) ? 1 : -1;
	direction.y = (ab.y > 0) ? 1 : -1;
	start->x = a.x;
	start->y = a.y;
	start->z = a.z;
	start->color = rgb_unpack(a.color);
	incr->x = direction.x;
	incr->y = fabsf((float)ab.y / ab.x) * direction.y;
	incr->z = (b.z - a.z) / abs(ab.x);
	incr->color = get_rgb_incr(start->color, rgb_unpack(b.color), abs(ab.x));
	return (true);
}

void	draw_line_x_axis(t_renderer *rndr, t_point a, t_point b)
{
	t_hax_x	current;
	t_hax_x	increment;
	float	fog_atten;
	int		i;
	
	printf("%d, %d\n", a.x, a.y);
	printf("%d, %d\n", b.x, b.y);
	if (!prepare_draw_line_x(a, b, &current, &increment))
		return ;
	while (current.x != b.x)
	{
		i = ((int)current.y * rndr->size.x) + current.x;
		if (i > rndr->size.x * rndr->size.y || i < 0)
			printf("%d\n", i);
		if (rndr->depth_buffer[i] > current.z)
		{
			rndr->depth_buffer[i] = current.z;
			fog_atten = rndr->use_fog ? fminf(-current.z * 50, 1) : 1;
			rndr->pixels[i] = rgb_pack(rgb_mul(current.color, fog_atten));
		}
		current.y += increment.y;
		current.x += increment.x;
		current.z += increment.z;
		current.color = rgb_add(current.color, increment.color);
	}
}

bool	prepare_draw_line_y(t_point a, t_point b, t_hax_y *start, t_hax_y *incr)
{
	t_vec2i	ab;
	t_vec2i	direction;

	ab = (t_vec2i){b.x - a.x, b.y - a.y};
	direction.x = (ab.x > 0) ? 1 : -1;
	direction.y = (ab.y > 0) ? 1 : -1;
	if (ab.y == 0)
		return (false);
	start->x = a.x;
	start->y = a.y;
	start->z = a.z;
	start->color = rgb_unpack(a.color);
	incr->x = fabsf((float)ab.x / ab.y) * direction.x;
	incr->y = direction.y;
	incr->color = get_rgb_incr(start->color, rgb_unpack(b.color), abs(ab.y));
	incr->z = (b.z - a.z) / abs(ab.y);
	return (true);
}

void	draw_line_y_axis(t_renderer *renderer, t_point a, t_point b)
{
	t_hax_y	current;
	t_hax_y	increment;
	float	fog_atten;
	int		i;

	if (!prepare_draw_line_y(a, b, &current, &increment))
		return ;
	while (current.y != b.y)
	{
		i = (current.y * renderer->size.x) + (int)current.x;
		if (renderer->depth_buffer[i] > current.z)
		{
			renderer->depth_buffer[i] = current.z;
			fog_atten = renderer->use_fog ? fminf(-current.z * 50, 1) : 1;
			renderer->pixels[i] = rgb_pack(rgb_mul(current.color, fog_atten));
		}
		current.x += increment.x;
		current.y += increment.y;
		current.z += increment.z;
		current.color = rgb_add(current.color, increment.color);
	}
}

void	draw_line(t_renderer *rndr, t_point a, t_point b)
{
	t_vec2i ab;

	ab = (t_vec2i){b.x - a.x, b.y - a.y};
	if (abs(ab.x) >= abs(ab.y))
		draw_line_x_axis(rndr, a, b);
	else
		draw_line_y_axis(rndr, a, b);
}
