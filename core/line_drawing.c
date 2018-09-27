#include "line_drawing.h"

#include "rgb.h"

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

void	draw_line_x_axis(t_renderer *rndr, t_point a, t_point b);
void	draw_line_y_axis(t_renderer *renderer, t_point a, t_point b);

void	draw_line(t_renderer *rndr, t_point a, t_point b)
{
	t_vec2i ab;

	ab = (t_vec2i){b.x - a.x, b.y - a.y};
	if (abs(ab.x) >= abs(ab.y))
		draw_line_x_axis(rndr, a, b);
	else
		draw_line_y_axis(rndr, a, b);
}

t_rgb	get_color_increment(t_rgb start, t_rgb end, float extent)
{
	t_rgb inc;

	inc.r = (end.r - start.r) / extent;
	inc.g = (end.g - start.g) / extent;
	inc.b = (end.b - start.b) / extent;
	return (inc);
}

struct s_hax_x {
	int		x;
	float	y;
	float	z;
	t_rgb	color;
};
typedef struct s_hax_x t_hax_x;

bool	prepare_line_drawing_x(t_point a, t_point b, t_hax_x *start, t_hax_x *inc)
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
	inc->x = direction.x;
	inc->y = fabsf((float)ab.y / ab.x) * direction.y;
	inc->z = (b.z - a.z) / abs(ab.x);
	inc->color = get_color_increment(start->color, rgb_unpack(b.color), abs(ab.x));
	return (true);
}

void	draw_line_x_axis(t_renderer *rndr, t_point a, t_point b)
{
	t_hax_x	current;
	t_hax_x	increment;
	float	fog_atten;
	int		i;

	if (!prepare_line_drawing_x(a, b, &current, &increment))
		return ;
	while (current.x != b.x)
	{
		i = ((int)current.y * rndr->size.x) + current.x;
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

struct s_hax_y {
	float	x;
	int		y;
	float	z;
	t_rgb	color;
};
typedef struct s_hax_y t_hax_y;

bool prepare_line_drawing_y(t_point a, t_point b, t_hax_y *start, t_hax_y *increment)
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
	increment->x = fabsf((float)ab.x / ab.y) * direction.x;
	increment->y = direction.y;
	increment->color = get_color_increment(start->color, rgb_unpack(b.color), abs(ab.y));
	increment->z = (b.z - a.z) / abs(ab.y);
	return (true);
}

void	draw_line_y_axis(t_renderer *renderer, t_point a, t_point b)
{
	t_hax_y	current;
	t_hax_y	increment;
	float	fog_atten;
	int		i;

	if (!prepare_line_drawing_y(a, b, &current, &increment))
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
