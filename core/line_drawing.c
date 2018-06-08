#include "line_drawing.h"

#include <stdlib.h>
#include <math.h>

void draw_line_x_axis(t_renderer renderer, t_vec2i a, t_vec2i b, t_vec2i direction);
void draw_line_y_axis(t_renderer renderer, t_vec2i a, t_vec2i b, t_vec2i direction);

void draw_line(t_renderer renderer, t_vec2i a, t_vec2i b)
{
	t_vec2i increment;

//	printf("(%i, %i) to (%i, %i)\n", a.x, a.y, b.x, b.y);
	t_vec2i ab = (t_vec2i){b.x - a.x, b.y - a.y};

	increment.x = (ab.x > 0) ? 1 : -1;
	increment.y = (ab.y > 0) ? 1 : -1;
	if (abs(ab.x) > abs(ab.y))
		draw_line_x_axis(renderer, a, b, increment);
	else
		draw_line_y_axis(renderer, a, b, increment);
}

void draw_line_x_axis(t_renderer renderer, t_vec2i a, t_vec2i b, t_vec2i direction)
{
	t_vec2i ab = (t_vec2i){b.x - a.x, b.y - a.y};

	if (ab.x == 0)
		return;
	float coeff = fabsf((float)ab.y / ab.x);
	float y = a.y;
	int x = a.x;
	while (x != b.x)
	{
		int i = ((int)y * renderer.size.x) + x;
		renderer.pixels[i] += 0x00222222;
		if (renderer.pixels[i] & 0xFF000000)
			renderer.pixels[i] = 0x00FFFFFF;
		y += coeff * direction.y;
		x += direction.x;
	}
}

void draw_line_y_axis(t_renderer renderer, t_vec2i a, t_vec2i b, t_vec2i direction)
{
	t_vec2i ab = (t_vec2i){b.x - a.x, b.y - a.y};

	if (ab.y == 0)
		return;
	float coeff = fabsf((float)ab.x / ab.y);
	float x = a.x;
	int y = a.y;
	while (y != b.y)
	{
		int i = (y * renderer.size.x) + (int)x;
		renderer.pixels[i] += 0x00222222;
		if (renderer.pixels[i] & 0xFF000000)
			renderer.pixels[i] = 0x00FFFFFF;
		x += coeff * direction.x;
		y += direction.y;
	}
}
