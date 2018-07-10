#include "line_drawing.h"

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

void draw_line_x_axis(t_renderer *renderer, t_vec3i a, t_vec3i b, t_vec2i direction);
void draw_line_y_axis(t_renderer *renderer, t_vec3i a, t_vec3i b, t_vec2i direction);
void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void draw_line(t_renderer *renderer, t_vec3i a, t_vec3i b)
{
	t_vec2i increment;

//	printf("(%i, %i) to (%i, %i)\n", a.x, a.y, b.x, b.y);
	t_vec2i ab = (t_vec2i){b.x - a.x, b.y - a.y};

	increment.x = (ab.x > 0) ? 1 : -1;
	increment.y = (ab.y > 0) ? 1 : -1;

	if (abs(ab.x) >= abs(ab.y))
		draw_line_x_axis(renderer, a, b, increment);
	else
		draw_line_y_axis(renderer, a, b, increment);
}

void draw_line_x_axis(t_renderer *renderer, t_vec3i a, t_vec3i b, t_vec2i direction)
{
	t_vec2i ab;
	float coeff;
	float y;
	int x;
	float red_inc;
	float green_inc;
	float blue_inc;

	float red;
	float green;
	float blue;
	ab = (t_vec2i){b.x - a.x, b.y - a.y};
	if (ab.x == 0)
		return;
	coeff = fabsf((float)ab.y / ab.x);
	y = a.y;
	x = a.x;
	red_inc = (RED(b.z) - RED(a.z)) / (float)ab.x;
	green_inc = (GREEN(b.z) - GREEN(a.z)) / (float)ab.x;
	blue_inc = (BLUE(b.z) - BLUE(a.z)) / (float)ab.x;
	red = RED(a.z);
	green = GREEN(a.z);
	blue = BLUE(a.z);
	while (x != b.x)
	{
		int i = ((int)y * renderer->size.x) + x;
		renderer->pixels[i] = ((uint8_t)red << R_SHIFT)
							 + ((uint8_t)green << G_SHIFT)
							 + ((uint8_t)blue << B_SHIFT);
//		if (renderer.pixels[i] & 0xFF000000)
//			renderer.pixels[i] = 0x00FFFFFF;
		y += coeff * direction.y;
		x += direction.x;
		red += direction.x * red_inc;
		green += direction.x * green_inc;
		blue += direction.x * blue_inc;
//		printf("0x%08x\n", color);
	}
}

void draw_line_y_axis(t_renderer *renderer, t_vec3i a, t_vec3i b, t_vec2i direction)
{
	t_vec2i ab;
	float coeff;
	float x;
	int y;
	float red_inc;
	float green_inc;
	float blue_inc;

	float red;
	float green;
	float blue;
	ab = (t_vec2i){b.x - a.x, b.y - a.y};
	if (ab.y == 0)
		return;
	coeff = fabsf((float)ab.x / ab.y);
	x = a.x;
	y = a.y;
	red_inc = (RED(b.z) - RED(a.z)) / (float)ab.y;
	green_inc = (GREEN(b.z) - GREEN(a.z)) / (float)ab.y;
	blue_inc = (BLUE(b.z) - BLUE(a.z)) / (float)ab.y;
	red = RED(a.z);
	green = GREEN(a.z);
	blue = BLUE(a.z);
	while (y != b.y)
	{
		int i = (y * renderer->size.x) + (int)x;
		renderer->pixels[i] = ((uint8_t)red << R_SHIFT)
							 + ((uint8_t)green << G_SHIFT)
							 + ((uint8_t)blue << B_SHIFT);
//		if (renderer.pixels[i] & 0xFF000000)
//			renderer.pixels[i] = 0x00FFFFFF;
		x += coeff * direction.x;
		y += direction.y;
		red += direction.y * red_inc;
		green += direction.y * green_inc;
		blue += direction.y * blue_inc;
	}
}

