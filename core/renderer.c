/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 16:10:42 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/10/09 17:45:01 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

#include "libft.h"
#include "line_clipping.h"
#include "line_drawing.h"

#include <stdlib.h>

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
	r->use_fog = 0;
	set_perspective(&r->projection, 1, 100, size.x / size.y, r->fov_angle);
	speed_factor = vec3_max_axis(vec3_sub(r->map.max, r->map.min)) / 100;
	init_camera(&r->camera, speed_factor);
}

/*
** Z = [0, -1]
*/

bool	transform_point(t_renderer r, t_vec4 p, t_point *p_i, t_mat4 model_clip)
{
	p_i->color = (int)p.w;
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
	vec4_round2D_point(p, p_i);
	p_i->z = p.z;
	return (true);
}

void	renderer_draw_segment(t_renderer r, t_segment segmen, t_mat4 model_clip)
{
	t_vec4	*vertex_ptr;
	t_vec4	a;
	t_vec4	b;
	t_point	aa;
	t_point	bb;

	vertex_ptr = r.map.vertex_array.data;
	a = vertex_ptr[segmen.start_idx];
	b = vertex_ptr[segmen.end_idx];
	if (transform_point(r, a, &aa, model_clip) == false)
		return ;
	if (transform_point(r, b, &bb, model_clip) == false)
		return ;
	if (clip_line(&aa, &bb, r.size))
		draw_line(&r, aa, bb);
}

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
	while (i < rndr.map.segment_array.size)
	{
		renderer_draw_segment(rndr, segment_ptr[i], model_clip);
		i++;
	}
}

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
