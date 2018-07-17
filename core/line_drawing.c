#include "line_drawing.h"

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

void draw_line_x_axis(t_renderer *renderer, t_vec3i a, t_vec3i b, t_vec2i direction,
					  float d, float d1);
void draw_line_y_axis(t_renderer *renderer, t_vec3i a, t_vec3i b, t_vec2i direction,
					  float d, float d1);
void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void draw_line(t_renderer *renderer, t_vec3i a, t_vec3i b, float a_z, float b_z)
{
	t_vec2i increment;

//	printf("(%i, %i) to (%i, %i)\n", a.x, a.y, b.x, b.y);
//	printf("(%g) to (%g)\n", a_z, b_z);
	t_vec2i ab = (t_vec2i){b.x - a.x, b.y - a.y};

	increment.x = (ab.x > 0) ? 1 : -1;
	increment.y = (ab.y > 0) ? 1 : -1;

	if (abs(ab.x) >= abs(ab.y))
		draw_line_x_axis(renderer, a, b, increment, a_z, b_z);
	else
		draw_line_y_axis(renderer, a, b, increment, a_z, b_z);
}

void draw_line_x_axis(t_renderer *renderer, t_vec3i a, t_vec3i b, t_vec2i direction,
					  float a_z, float b_z)
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
	red_inc = (RED(b.z) - RED(a.z)) / fabsf(ab.x);
	green_inc = (GREEN(b.z) - GREEN(a.z)) / fabsf(ab.x);
	blue_inc = (BLUE(b.z) - BLUE(a.z)) / fabsf(ab.x);
	red = RED(a.z);
	green = GREEN(a.z);
	blue = BLUE(a.z);
	float z_inc = (b_z - a_z) / fabsf(ab.x);
	float z = a_z;
	while (x != b.x)
	{
		int i = ((int)y * renderer->size.x) + x;
		if (renderer->depth_buffer[i] < z || renderer->depth_buffer[i] == 0)
		{
			renderer->depth_buffer[i] = z;
//			float z_scale = 1 - (fabsf(z) / 200);
			float z_scale = 1 - (fabsf(z) * 0.005f);
			z_scale = z_scale < 0 ? 0 : z_scale;
//			if (z_scale < 0 || z_scale > 1)
//				printf("z: %g\n", z);
//			renderer->pixels[i] = ((uint8_t) (((red / 255.f) * z_scale) * 255.f) << R_SHIFT)
//								  + ((uint8_t) (((green / 255.f) * z_scale) * 255.f) << G_SHIFT)
//								  + ((uint8_t) (((blue / 255.f) * z_scale) * 255.f) << B_SHIFT);
			renderer->pixels[i] = ((uint8_t)red << R_SHIFT)
								 + ((uint8_t)green << G_SHIFT)
								 + ((uint8_t)blue << B_SHIFT);
	//		if (renderer.pixels[i] & 0xFF000000)
	//			renderer.pixels[i] = 0x00FFFFFF;
		}
		y += coeff * direction.y;
		x += direction.x;
		red += red_inc;
		green += green_inc;
		blue += blue_inc;
		z += z_inc;
//		printf("0x%08x\n", color);
	}
}

void draw_line_y_axis(t_renderer *renderer, t_vec3i a, t_vec3i b, t_vec2i direction,
					  float a_z, float b_z)
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
	red_inc = (RED(b.z) - RED(a.z)) / fabsf(ab.y);
	green_inc = (GREEN(b.z) - GREEN(a.z)) / fabsf(ab.y);
	blue_inc = (BLUE(b.z) - BLUE(a.z)) / fabsf(ab.y);
	red = RED(a.z);
	green = GREEN(a.z);
	blue = BLUE(a.z);
	float z_inc = (b_z - a_z) / fabsf(ab.y);
	float z = a_z;
	while (y != b.y)
	{
		int i = (y * renderer->size.x) + (int)x;
		if (renderer->depth_buffer[i] < z || renderer->depth_buffer[i] == 0)
		{
			renderer->depth_buffer[i] = z;
//			red = ((red / 255.f) * fabsf(z)) * 255.f;
//			blue = ((blue / 255.f) * fabsf(z)) * 255.f;
//			green = ((green / 255.f) * fabsf(z)) * 255.f;
//			float z_scale = 1 - (fabsf(z) / 200);
			float z_scale = 1 - (fabsf(z) * 0.005f);
			z_scale = z_scale < 0 ? 0 : z_scale;
//			if (z_scale < 0 || z_scale > 1)
//				printf("z: %g -> %g\n", z, z_scale);
//			renderer->pixels[i] = ((uint8_t) (((red / 255.f) * z_scale) * 255.f) << R_SHIFT)
//								  + ((uint8_t) (((green / 255.f) * z_scale) * 255.f) << G_SHIFT)
//								  + ((uint8_t) (((blue / 255.f) * z_scale) * 255.f) << B_SHIFT);
			renderer->pixels[i] = ((uint8_t)red << R_SHIFT)
								  + ((uint8_t)green << G_SHIFT)
								  + ((uint8_t)blue << B_SHIFT);
//		if (renderer.pixels[i] & 0xFF000000)
//			renderer.pixels[i] = 0x00FFFFFF;
		}
		x += coeff * direction.x;
		y += direction.y;
		red += red_inc;
		green += green_inc;
		blue += blue_inc;
		z += z_inc;
	}
}

