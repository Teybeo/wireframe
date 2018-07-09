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
	renderer->gradient[1].color = 0x00007700;
	renderer->gradient[2].color = 0x00FFFF88;
	renderer->gradient[3].color = 0x00880000;
	renderer->gradient[4].color = 0x00FFFFFF;
	renderer->gradient[5].color = 0x00FFFFFF;
	init_camera(&renderer->camera);
}

int get_color_from_height(t_renderer *renderer, float height)
{
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
	i--;
//	printf("height: %6g = %d\n", height, renderer->gradient[i].color);
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

	segment_ptr = renderer.map.segment_array.data;
	i = 0;

	float near = 0.1f;
	float far = 100.f;
	float ratio = (renderer.size.y / (float)renderer.size.x);
	// Distance from a projection screen of unit width
	float distance = 1.f / tanf((renderer.fov_angle / 2) * M_PI_F / 180);
	float z_factor = (-far + near) / (far - near);
	float z_translation = ((2 * far * near) / (far - near));

	t_mat4 model_view;
	t_mat4 rotation;
	t_mat4 translation;

	mat4_identity(&translation);
	mat4_translate_by(&translation, renderer.camera.pos);

	init_with_mat3(&rotation, renderer.camera.rotation);

	if (renderer.camera.mode == CAMERA_FREEFLY)
	{
		model_view = rotation;
//		mat4_mul(&model_view, &translation);
		model_view = mat4_mul2(model_view, translation);
	}
	else
	{
		model_view = translation;
//		mat4_mul(&model_view, &rotation);
		model_view = mat4_mul2(model_view, rotation);
	}

	t_vec3 vec_translation = renderer.camera.pos;

	if (renderer.camera.mode == CAMERA_FREEFLY)
		mat3_mul_vec3X(&renderer.camera.rotation, &vec_translation);

	while (i < renderer.map.segment_array.size)
	{
		t_vec3 a = segment_ptr[i].start;
		t_vec3 b = segment_ptr[i].end;

		t_vec3i aa;
		t_vec3i bb;
		aa.z = get_color_from_height(&renderer, a.y);
		bb.z = get_color_from_height(&renderer, b.y);

		a.y *= renderer.scale_factor;
		b.y *= renderer.scale_factor;
//		mat3_mul_vec3X(&renderer.camera.rotation, &a);
//		mat3_mul_vec3X(&renderer.camera.rotation, &b);
//		vec3_subXX(&a, vec_translation.x, vec_translation.y, vec_translation.z);
//		vec3_subXX(&b, vec_translation.x, vec_translation.y, vec_translation.z);
//
		mat4_mul_vec(&model_view, &a);
		mat4_mul_vec(&model_view, &b);

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
		vec3_mul_scalar_this(&a, 1 / a_w);
		vec3_mul_scalar_this(&b, 1 / b_w);

		// NDC to Window
		a.x = a.x * renderer.size.x + (renderer.size.x * 0.5f);
		a.y = -a.y * renderer.size.y + (renderer.size.y * 0.5f);
		b.x = b.x * renderer.size.x + (renderer.size.x * 0.5f);
		b.y = -b.y * renderer.size.y + (renderer.size.y * 0.5f);

		t_vec2i a_i = vec3_round2D(a);
		t_vec2i b_i = vec3_round2D(b);


		if (clip_line(&a_i, &b_i, renderer.size))
		{
//			draw_line(renderer, a_i, b_i);
			aa.x = a_i.x;
			aa.y = a_i.y;
			bb.x = b_i.x;
			bb.y = b_i.y;
			draw_line(&renderer, aa, bb);

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
		draw_line(&renderer, a_i, b_i);
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
//		vec3_print("Camera pos: ", renderer->camera.pos);
		printf("Frametime: %f ms, %f fps\n", duration, 1000 / duration);
		elapsed_time = 0;
	}
	timestamp = clock();
}
