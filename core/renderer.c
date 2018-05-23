#include "renderer.h"

#include "libft.h"
#include "map_reader.h"
#include "../../../.brew/Cellar/sdl2/2.0.8/include/SDL2/SDL_system.h"

#include <stdio.h>

void draw_line(t_renderer renderer, t_point a, t_point b);
void draw_line_x_axis(t_renderer renderer, t_point a, t_point b, int direction);
void draw_line_y_axis(t_renderer renderer, t_point a, t_point b, int direction);

void renderer_init(t_renderer *renderer, t_array array, t_point size)
{
	ft_putendl("Core awaken");
	renderer->segment_array = array;
	renderer->size = size;
	renderer->pixels = malloc(sizeof(uint32_t) * size.x * size.y);
}

void renderer_draw(t_renderer renderer) {

	t_point a = {500, 500};
	t_point b = {801, 800};
	srand(time(NULL));
	float lol = fabsf(cos(clock() / 500000000.f));
	for (int i = 0; i < renderer.size.x * renderer.size.y; ++i) {
		renderer.pixels[i] = lol * 0xFFFF0000;
	}

	static int step_count = 0;
	step_count = ((cos(clock() / 1000000.f) * 0.5) + 0.5f) * 10000;
	printf("step_count: %d\n", step_count);
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

void renderer_draw2(t_renderer renderer)
{
	t_segment *segment_ptr;
	int i;

	segment_ptr = renderer.segment_array.data;
	i = 0;

	while (i < renderer.segment_array.size)
	{
		t_point a = segment_ptr[i].start;
		t_point b = segment_ptr[i].end;
		a.x *= 10;
		a.y += 10;
		b.x *= 10;
		
		draw_line(renderer, a, b);
		i++;
	}
}

void draw_line(t_renderer renderer, t_point a, t_point b) {

	t_point ab = (t_point){b.x - a.x, b.y - a.y};
	t_point tmp;
	t_point increment;

	if (abs(ab.x) > abs(ab.y))
	{
		if (ab.x < 0)
			increment.x = -1;
		else
			increment.x = 1;
		draw_line_x_axis(renderer, a, b, increment.x);
	}
	else
	{
		if (ab.y < 0)
			increment.y = -1;
		else
			increment.y = 1;
		draw_line_y_axis(renderer, a, b, increment.y);
	}
}

void draw_line_x_axis(t_renderer renderer, t_point a, t_point b, int direction)
{

//	printf("(%d, %d) to (%d, %d)\n", a.x, a.y, b.x, b.y);
	t_point ab = (t_point){b.x - a.x, b.y - a.y};

	if (ab.x == 0)
		return;
	float coeff = (float)ab.y / ab.x;
	float y = a.y;
	int x = a.x;
	while (x != b.x)
	{
		int i = (((int)y * renderer.size.x) + x);
//		printf("%d\n", i);
		renderer.pixels[i] = 0xFFFFFFFF;
		y += coeff;
		x += direction;
	}
}
void draw_line_y_axis(t_renderer renderer, t_point a, t_point b, int direction)
{

	t_point ab = (t_point){b.x - a.x, b.y - a.y};

	if (ab.y == 0)
		return;
	float coeff = (float)ab.x / ab.y;
	float x = a.x;
	int y = a.y;
	while (y != b.y)
	{
		int i = (int) (((int)y * renderer.size.x) + x);
//		printf("%d\n", i);
		renderer.pixels[i] = 0xFFFFFFFF;
		x += coeff;
		y += direction;
	}
}

void renderer_event(t_renderer *renderer)
{

}
