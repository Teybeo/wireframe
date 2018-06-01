#include "renderer.h"

#include "libft.h"
#include "map_reader.h"

#include <stdio.h>
#include <vec3.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

void draw_line(t_renderer renderer, t_vec3 a3, t_vec3 b3);
void draw_line_y_axis(t_renderer renderer, t_vec2i a, t_vec2i b, t_vec2i direction);
void draw_line_x_axis(t_renderer renderer, t_vec2i a, t_vec2i b, t_vec2i direction);

void renderer_init(t_renderer *renderer, void* pixels, t_array array, t_vec3 size)
{
	ft_putendl("Core awaken");
	renderer->segment_array = array;
	renderer->size = size;
	renderer->pixels = pixels;
	init_camera(&renderer->camera);
}

void renderer_draw0(t_renderer renderer) {

	t_vec3 a = {500, 500, 0};
	t_vec3 b = {801, 800, 0};

	ft_memzero(renderer.pixels, renderer.size.x * renderer.size.y * sizeof(uint32_t));

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
		draw_line(renderer, a, b);
	}
//	usleep(100000);
}

#define DEG_TO_RAD(X) (((X) / 180.f) * 3.14159f)

void renderer_draw1(t_renderer renderer) {

	t_vec3 center = {200, 200, 0};
	int length = 200;
	t_vec3 a;
	t_vec3 b;

	ft_memzero(renderer.pixels, renderer.size.x * renderer.size.y * sizeof(uint32_t));

	static float angle = 150;
	float rad = DEG_TO_RAD(angle);
	{
		a.x = cosf(rad) * length;
		a.y = sinf(rad) * length;
		a = vec3_add(a, center);
		b = vec3_sub(center, a);
//		draw_line(renderer, center, a);
		draw_line(renderer, a, center);
	}
	if (angle > 360)
		angle = 0;
	angle += .5f;
	printf("Angle: %f\n", angle);

//	usleep(100000);
}

void renderer_draw(t_renderer renderer)
{
	t_segment *segment_ptr;
	int i;

	ft_memzero(renderer.pixels, renderer.size.x * renderer.size.y * sizeof(uint32_t));

	segment_ptr = renderer.segment_array.data;
	i = 0;

	while (i < renderer.segment_array.size)
	{
		t_vec3 a = segment_ptr[i].start;
		t_vec3 b = segment_ptr[i].end;

		a.x *= 100;
		a.y *= 100;
		b.x *= 100;
		b.y *= 100;
		a.z = 0;
		b.z = 0;

		a = mat3_mul_vec3(&renderer.camera.rotation, a);
		b = mat3_mul_vec3(&renderer.camera.rotation, b);

		a = vec3_add(a, renderer.camera.pos);
		b = vec3_add(b, renderer.camera.pos);

		a = vec3_clamp2D(a, renderer.size);
		b = vec3_clamp2D(b, renderer.size);

		draw_line(renderer, a, b);
		i++;
	}
}

void draw_line(t_renderer renderer, t_vec3 a3, t_vec3 b3)
{
	t_vec2i a;
	t_vec2i b;
	t_vec2i increment;
	a = vec3_round2D(a3);
	b = vec3_round2D(b3);

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
		int i = ((int)y * (int)renderer.size.x) + x;

		if (i >= 0 && i < (renderer.size.x * renderer.size.y))
			renderer.pixels[i] = 0x00FFFFFF;
//		else
//			puts("NOPE");
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
		int i = (y * (int)renderer.size.x) + (int)x;
		if (i >= 0 && i < (renderer.size.x * renderer.size.y))
			renderer.pixels[i] = 0x00FFFFFF;
//		else
//			puts("NOPE");
		x += coeff * direction.x;
		y += direction.y;
	}
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
	if (elapsed_time >= 1000)
	{
		printf("Camera pos: ");
		vec3_print(renderer->camera.pos);
		printf("\n");
//		printf("Interval: %f\n", elapsed_time);	  glDeleteBuffers(1, &(ctx->vbuffer));
		elapsed_time = 0;
	}
	timestamp = clock();
}