#include "renderer.h"

#include "libft.h"
#include "map_reader.h"
#include "line_clipping.h"

#include <stdio.h>
#include <vec3.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void draw_line(t_renderer renderer, t_vec2i a, t_vec2i b);
void draw_line_y_axis(t_renderer renderer, t_vec2i a, t_vec2i b, t_vec2i direction);
void draw_line_x_axis(t_renderer renderer, t_vec2i a, t_vec2i b, t_vec2i direction);

void renderer_init(t_renderer *renderer, void* pixels, t_array array, t_vec2i size)
{
	ft_putendl("Core awaken");
	renderer->segment_array = array;
	renderer->size = size;
	renderer->pixels = pixels;
	init_camera(&renderer->camera);
}

void renderer_draw(t_renderer renderer)
{
	t_segment *segment_ptr;
	int i;

	ft_memzero(renderer.pixels, renderer.size.x * renderer.size.y, sizeof(uint32_t));

	segment_ptr = renderer.segment_array.data;
	i = 0;

	float near = 0.1f;
	float far = 100.f;
	float ratio = (renderer.size.y / (float)renderer.size.x);
	float angle = 130;
	// Distance from a projection screen of unit width
	float distance = 1.f / tanf((angle / 2) * M_PI / 180);
	float z_factor = (-far + near) / (far - near);
	float z_translation = ((2 * far * near) / (far - near));

	while (i < renderer.segment_array.size)
	{
		t_vec3 a = segment_ptr[i].start;
		t_vec3 b = segment_ptr[i].end;

		a.z *= 0.05f;
		b.z *= 0.05f;

		vec3_subXX(&a, renderer.camera.pos.x, renderer.camera.pos.y, renderer.camera.pos.z);
		vec3_subXX(&b, renderer.camera.pos.x, renderer.camera.pos.y, renderer.camera.pos.z);

		a.y += 100;
		b.y += 100;

//		a.z += -100;
//		b.z += -100;

		mat3_mul_vec3X(&renderer.camera.rotation, &a);
		mat3_mul_vec3X(&renderer.camera.rotation, &b);
//
		// Eye to Clip
		float a_w = -a.z;
		float b_w = -b.z;
		a.x *= distance * ratio;
		a.y *= distance;
		b.x *= distance * ratio;
		b.y *= distance;

		a.z *= z_factor;
		a.z -= z_translation;
		b.z *= z_factor;
		b.z -= z_translation;

		// Discard line if one or both points outside clipping volume
		if ((a.x < -a_w || a.x > a_w)
			||	(a.y < -a_w || a.y > a_w)
			||	(a.z < -a_w || a.z > a_w)
			||	(b.x < -b_w || b.x > b_w)
			||	(b.y < -b_w || b.y > b_w)
			||	(b.z < -b_w || b.z > b_w)
				)
		{
			i++;
			continue;
		}
		// Clip to NDC
		a = vec3_mul_scalar(a, 1 / a_w);
		b = vec3_mul_scalar(b, 1 / b_w);

		// NDC to Window
		a.x = a.x * renderer.size.x + (renderer.size.x * 0.5f);
		a.y = a.y * renderer.size.y + (renderer.size.y * 0.5f);
		b.x = b.x * renderer.size.x + (renderer.size.x * 0.5f);
		b.y = b.y * renderer.size.y + (renderer.size.y * 0.5f);

		t_vec2i a_i = vec3_round2D(a);
		t_vec2i b_i = vec3_round2D(b);

		if (clip_line(&a_i, &b_i, renderer.size))
			draw_line(renderer, a_i, b_i);
		i++;
	}
}

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


void renderer_draw0(t_renderer renderer) {

	t_vec3 a = {500, 500, 0};
	t_vec3 b = {801, 800, 0};

	t_vec2i a_i;
	t_vec2i b_i;

	ft_memzero(renderer.pixels, renderer.size.x * renderer.size.y, sizeof(uint32_t));

	static int step_count = 8;
	step_count = ((cos(clock() / 1000000.f) * 0.5) + 0.5f) * 1000;
//	printf("step_count: %d\n", step_count);
//	step_count;
	float angle;
	float step = (2 * M_PI) / step_count;
	for (angle = 0; angle < (2 * M_PI); angle += step)
	{
		b.x = a.x + cos(angle) * 400;
		b.y = a.x + sin(angle) * 400;
		a_i = vec3_round2D(a);
		b_i = vec3_round2D(b);
		draw_line(renderer, a_i, b_i);
	}
//	usleep(100000);
}

void renderer_draw1(t_renderer renderer) {

	t_vec3 center = {200, 200, 0};
	int length = 200;
	t_vec3 a;
	t_vec3 b;

	ft_memzero(renderer.pixels, renderer.size.x * renderer.size.y, sizeof(uint32_t));

	static float angle = 150;
	float rad = DEG_TO_RAD(angle);
	{
		a.x = cosf(rad) * length;
		a.y = sinf(rad) * length;
		a = vec3_add(a, center);
		b = vec3_sub(center, a);
//		draw_line(renderer, center, a);
		t_vec2i a_i = vec3_round2D(a);
		t_vec2i center_i = vec3_round2D(center);
		draw_line(renderer, a_i, center_i);
	}
	if (angle > 360)
		angle = 0;
	angle += .5f;
	printf("Angle: %f\n", angle);

//	usleep(100000);
}


void renderer_event(t_renderer *renderer)
{
	renderer++;
}

void renderer_update(t_renderer *renderer)
{
	camera_update(&renderer->camera);

	static clock_t timestamp = 0;
	static float elapsed_time = 0;
	float duration = (clock() - timestamp) / (float)CLOCKS_PER_SEC;
	duration *= 1000;
	elapsed_time += duration;
	if (elapsed_time >= 20)
	{
		vec3_print("Camera pos: ", renderer->camera.pos);
//		printf("Interval: %fms\n", duration);
		elapsed_time = 0;
	}
	timestamp = clock();
}
