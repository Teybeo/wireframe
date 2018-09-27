/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 16:10:42 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/09/27 19:52:21 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	renderer_init(t_renderer *r, void *pixels, t_map map, t_vec2i size)
{
	float speed_factor;

	ft_putendl("Core awaken");
	r->map = map;
	r->size = size;
	r->pixels = pixels;
	r->scale_factor = 0.25f;
	r->fov_angle = 90;
	r->depth_buffer = malloc(sizeof(float) * size.x * size.y);
	r->use_perspective = 1;
	set_perspective(&r->projection, 1, 100, size.x / size.y, r->fov_angle);
	speed_factor = vec3_max_axis(vec3_sub(r->map.max, r->map.min)) / 100;
	init_camera(&r->camera, speed_factor);
}

/*
** Z = [0, -1]
*/
bool	transform_point(t_renderer r, t_vec4 p, t_point *ptr_i, t_mat4 model_clip)
{
	ptr_i->color = (int)p.w;
	p.w = 1;
	p.y *= r.scale_factor;
	mat4_mul_vec(&model_clip, &p);
	if ((p.x < -p.w || p.x > p.w)
		|| (p.y < -p.w || p.y > p.w)
		|| (p.z < -p.w || p.z > p.w))
		return (false);
	vec4_mul_scalar_this(&p, 1 / p.w);
	p.x = p.x * r.size.x + (r.size.x * 0.5f);
	p.y = -p.y * r.size.y + (r.size.y * 0.5f);
	p.z = (p.z - 1) * 0.5f;
	vec4_round2D_point(p, ptr_i);
	ptr_i->z = p.z;
	return (true);
}

void	renderer_render_segment(t_renderer r, t_segment segment, t_mat4 model_clip)
{
	t_vec4	*vertex_ptr;
	t_vec4	a;
	t_vec4	b;
	t_point	aa;
	t_point	bb;

	vertex_ptr = r.map.vertex_array.data;
	a = vertex_ptr[segment.start_idx];
	b = vertex_ptr[segment.end_idx];
	if (transform_point(r, a, &aa, model_clip) == false)
		return ;
	if (transform_point(r, b, &bb, model_clip) == false)
		return ;
	if (clip_line(&aa, &bb, r.size))
		draw_line(&r, aa, bb);
}

#if 1

void	renderer_draw(t_renderer rndr)
{
	int			i;
	t_segment	*segment_ptr;
	t_mat4		model_clip;

	ft_memzero(rndr.pixels, rndr.size.x * rndr.size.y, sizeof(uint32_t));
	ft_memzero(rndr.depth_buffer, rndr.size.x * rndr.size.y, sizeof(float));
	segment_ptr = rndr.map.segment_array.data;
	compute_transform(&rndr, &model_clip);
	i = 0;
	while (i <= rndr.map.segment_array.size)
	{
		renderer_render_segment(rndr, segment_ptr[i], model_clip);
		i++;
	}
}

#else
void	renderer_draw(t_renderer renderer)
{
	int			i;
	t_segment	*segment_ptr;
	t_vec4		*vertex_ptr;
	t_mat4		model_clip;
	t_vec3i		aa;
	t_vec3i		bb;

	ft_memzero(renderer.pixels, renderer.size.x * renderer.size.y, sizeof(uint32_t));
	ft_memzero(renderer.depth_buffer, renderer.size.x * renderer.size.y, sizeof(float));
	segment_ptr = renderer.map.segment_array.data;
	vertex_ptr = renderer.map.vertex_array.data;
	i = 0;
	compute_transform(&renderer, &model_clip);
	while (i < renderer.map.segment_array.size)
	{
		t_vec4 a = vertex_ptr[segment_ptr[i].start_idx];
		t_vec4 b = vertex_ptr[segment_ptr[i].end_idx];

		aa.z = a.w;
		bb.z = b.w;
		a.w = 1;
		b.w = 1;

		a.y *= renderer.scale_factor;
		b.y *= renderer.scale_factor;

		// Model to View to Clip
		mat4_mul_vec(&model_clip, &a);
		mat4_mul_vec(&model_clip, &b);
		// Discard line if one or both points outside clipping volume
		if ((a.x < -a.w || a.x > a.w)
			|| (a.y < -a.w || a.y > a.w)
			|| (a.z < -a.w || a.z > a.w)
			|| (b.x < -b.w || b.x > b.w)
			|| (b.y < -b.w || b.y > b.w)
			|| (b.z < -b.w || b.z > b.w)
			)
		{
			i++;
			continue;
		}
		// Clip to NDC
		// (We keep vertex w untouched for depth tests later)
		vec4_mul_scalar_this(&a, 1 / a.w);
		vec4_mul_scalar_this(&b, 1 / b.w);

		// NDC to Window
		a.x =  a.x * renderer.size.x + (renderer.size.x * 0.5f);
		a.y = -a.y * renderer.size.y + (renderer.size.y * 0.5f);
		b.x =  b.x * renderer.size.x + (renderer.size.x * 0.5f);
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
			a.w = renderer.use_perspective ? a.w : a.z;
			b.w = renderer.use_perspective ? b.w : b.z;
			draw_line_old(&renderer, aa, bb, -a.w, -b.w);
		}
		i++;
	}
}
#endif

void	compute_transform(t_renderer *renderer, t_mat4 *model_clip)
{
	t_mat4 model_view;
	t_mat4 rotation;
	t_mat4 translation;

	mat4_identity(&translation);
	mat4_translate_by(&translation, renderer->camera.pos);
	init_with_mat3(&rotation, renderer->camera.rotation);
	if (renderer->camera.mode == CAMERA_FREEFLY)
		mat4_mul_ptr(&model_view, &rotation, &translation);
	else
		mat4_mul_ptr(&model_view, &translation, &rotation);
	mat4_mul_ptr(model_clip, &renderer->projection, &model_view);
}

void	renderer_event(t_renderer *renderer, t_renderer_key key)
{
	if (key == KEY_SCALE_UP)
		renderer->scale_factor *= 2;
	if (key == KEY_SCALE_DOWN)
		renderer->scale_factor *= 0.5f;
	if (key == KEY_FOV_UP)
		renderer->fov_angle += 5;
	if (key == KEY_FOV_DOWN)
		renderer->fov_angle -= 5;
	if (key == KEY_PROJECTION_TOOGLE)
		renderer->use_perspective ^= 1;
	if (key == KEY_FOG_TOOGLE)
		renderer->use_fog ^= 1;
}

void	renderer_update(t_renderer *r)
{
	static clock_t	timestamp = 0;
	static float	elapsed_time = 0;
	float			duration;
	float			aspect_ratio;

	aspect_ratio = (float)r->size.y / r->size.x;
	camera_update(&r->camera);
	if (r->use_perspective)
		set_perspective(&r->projection, 1, 100, aspect_ratio, r->fov_angle);
	else
		set_orthographic(&r->projection, r->size.x, r->size.y, -1000, 1000);
	duration = (clock() - timestamp) / (float)CLOCKS_PER_SEC;
	duration *= 1000;
	elapsed_time += duration;
	if (elapsed_time >= 20)
	{
		printf("Frametime: %.0f ms, %.2f fps\n", duration, 1000 / duration);
		elapsed_time = 0;
	}
	timestamp = clock();
}
