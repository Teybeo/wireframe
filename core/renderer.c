#include "renderer.h"

#include "libft.h"
#include "map_reader.h"
#include "line_clipping.h"
#include "line_drawing.h"

#include <stdio.h>
#include <vec3.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <mat4.h>

void renderer_init(t_renderer *renderer, void* pixels, t_map map, t_vec2i size)
{
	ft_putendl("Core awaken");
	renderer->map = map;
	renderer->size = size;
	renderer->pixels = pixels;
	renderer->scale_factor = 0.25f;
	renderer->fov_angle = 90;
	renderer->gradient[0].treshold = 0;
	renderer->gradient[1].treshold = 0.01;
	renderer->gradient[2].treshold = 0.2;
	renderer->gradient[3].treshold = 0.5;
	renderer->gradient[4].treshold = 0.6;
	renderer->gradient[5].treshold = 1;
	renderer->gradient[0].color = 0x000000FF;
	renderer->gradient[1].color = 0x00008800;
	renderer->gradient[2].color = 0x00FFFF88;
	renderer->gradient[3].color = 0x00880000;
	renderer->gradient[4].color = 0x00FFFFFF;
	renderer->gradient[5].color = 0x00FFFFFF;
//	renderer->gradient[0].color = 0;
//	renderer->gradient[1].color = 1;
//	renderer->gradient[2].color = 2;
//	renderer->gradient[3].color = 3;
//	renderer->gradient[4].color = 4;
//	renderer->gradient[5].color = 5;
	renderer->depth_buffer = malloc(sizeof(float) * size.x * size.y);
	init_projection(&renderer->projection, 0.1, 100, size.x / size.y, renderer->fov_angle);
	init_camera(&renderer->camera);
}

int get_color_from_height(t_renderer *renderer, float height)
{
//	return 0x00FFFFFF;
	int i;
	float min;
	float max;
	float factor;

	height = (height - renderer->map.min.y) / (renderer->map.max.y - renderer->map.min.y);
	i = 0;
	while (i < GRADIENT_COUNT)
	{
		if (height < renderer->gradient[i].treshold)
			break;
		i++;
	}
	i = fminf(i, GRADIENT_COUNT - 1);
	i--;
//	printf("height: %6g = [%d -> %d]\n", height, i, i + 1);
//	return renderer->gradient[i].color;
	min = renderer->gradient[i].treshold;
	max = renderer->gradient[i + 1].treshold;
	factor = (height - min) / (max - min);
	return color_mix(factor, renderer->gradient[i].color, renderer->gradient[i + 1].color);
}

void renderer_draw(t_renderer renderer)
{
	t_segment *segment_ptr;
	int i;

	ft_memzero(renderer.pixels, renderer.size.x * renderer.size.y, sizeof(uint32_t));
	ft_memzero(renderer.depth_buffer, renderer.size.x * renderer.size.y, sizeof(float));

	segment_ptr = renderer.map.segment_array.data;
	i = 0;

	t_mat4 model_view;
	t_mat4 rotation;
	t_mat4 translation;
	t_mat4 model_clip;

	mat4_identity(&translation);
	mat4_translate_by(&translation, renderer.camera.pos);

	init_with_mat3(&rotation, renderer.camera.rotation);

	if (renderer.camera.mode == CAMERA_FREEFLY)
		mat4_mul_ptr(&model_view, &rotation, &translation);
	else
		mat4_mul_ptr(&model_view, &translation, &rotation);

	mat4_mul_ptr(&model_clip, &renderer.projection, &model_view);

	while (i < renderer.map.segment_array.size)
	{
		t_vec4 a = vec4(segment_ptr[i].start);
		t_vec4 b = vec4(segment_ptr[i].end);

		t_vec3i aa;
		t_vec3i bb;
		aa.z = segment_ptr[i].start_color;
		bb.z = segment_ptr[i].end_color;

//		aa.z = get_color_from_height(&renderer, a.y);
//		bb.z = get_color_from_height(&renderer, b.y);

		a.y *= renderer.scale_factor;
		b.y *= renderer.scale_factor;

		// Model to View to Clip
		mat4_mul_vec(&model_clip, &a);
		mat4_mul_vec(&model_clip, &b);
		// Discard line if one or both points outside clipping volume
		if ((a.x < -a.w || a.x > a.w)
			||	(a.y < -a.w || a.y > a.w)
			||	(a.z < -a.w || a.z > a.w)
			||	(b.x < -b.w || b.x > b.w)
			||	(b.y < -b.w || b.y > b.w)
			||	(b.z < -b.w || b.z > b.w)
			)
		{
			i++;
			continue;
		}
		// Clip to NDC
		// (We keep w untouched for depth usage)
		vec4_mul_scalar_this(&a, 1 / a.w);
		vec4_mul_scalar_this(&b, 1 / b.w);

		// NDC to Window
		a.x = a.x * renderer.size.x + (renderer.size.x * 0.5f);
		a.y = -a.y * renderer.size.y + (renderer.size.y * 0.5f);
		b.x = b.x * renderer.size.x + (renderer.size.x * 0.5f);
		b.y = -b.y * renderer.size.y + (renderer.size.y * 0.5f);

		t_vec2i a_i = vec4_round2D(a);
		t_vec2i b_i = vec4_round2D(b);

		if (clip_line(&a_i, &b_i, renderer.size))
		{
//			draw_line(renderer, a_i, b_i);
			aa.x = a_i.x;
			aa.y = a_i.y;
			bb.x = b_i.x;
			bb.y = b_i.y;
			draw_line(&renderer, aa, bb, -a.w, -b.w);
		}
		i++;
	}
}

void renderer_draw0(t_renderer renderer) {

	t_vec3 a = {500, 500, 0};
	t_vec3 b = {801, 800, 0};

	t_vec3i a_i;
	t_vec3i b_i;


	ft_memzero(renderer.pixels, renderer.size.x * renderer.size.y, sizeof(uint32_t));

	static int step_count = 8;
//	step_count = ((cos(clock() / 1000000.f) * 0.5) + 0.5f) * 1000;
	step_count = 10000;
//	printf("step_count: %d\n", step_count);
//	step_count;
	float angle;
	float step = (2 * M_PI_F) / step_count;
	for (angle = 0; angle < (2 * M_PI_F); angle += step)
	{
		b.x = a.x + cos(angle) * 400;
		b.y = a.x + sin(angle) * 400;
		a_i = vec3_round(a);
		b_i = vec3_round(b);
		a_i.z = 0x00FF0000;
		b_i.z = 0x000000FF;
		draw_line(&renderer, a_i, b_i, 0, 0);
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
//		t_vec2i a_i = vec3_round2D(a);
//		t_vec2i center_i = vec3_round2D(center);
//		draw_line(renderer, a_i, center_i);
	}
	if (angle > 360)
		angle = 0;
	angle += .5f;
	printf("Angle: %f\n", angle);

//	usleep(100000);
}


void renderer_event(t_renderer *renderer, t_renderer_key key)
{
	if (key == KEY_SCALE_UP)
		renderer->scale_factor *= 2;
	if (key == KEY_SCALE_DOWN)
		renderer->scale_factor *= 0.5f;
	if (key == KEY_FOV_UP)
		renderer->fov_angle += 5;
	if (key == KEY_FOV_DOWN)
		renderer->fov_angle -= 5;
}

void renderer_update(t_renderer *r)
{
	camera_update(&r->camera);
	init_projection(&r->projection, 0.1, 100, (float)r->size.y / r->size.x, r->fov_angle);

	static clock_t timestamp = 0;
	static float elapsed_time = 0;
	float duration = (clock() - timestamp) / (float)CLOCKS_PER_SEC;
	duration *= 1000;
	elapsed_time += duration;
	if (elapsed_time >= 20)
	{
//		vec3_print("Camera pos: ", r->camera.pos);
		printf("Frametime: %.0f ms, %.2f fps\n", duration, 1000 / duration);
		elapsed_time = 0;
	}
	timestamp = clock();
}
