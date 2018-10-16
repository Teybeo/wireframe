/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_update.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 17:42:27 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/10/09 17:42:27 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

#include <time.h>
#include <stdio.h>

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
	float	aspect_ratio;

	aspect_ratio = (float)r->size.y / r->size.x;
	if (r->use_perspective)
		r->projection = get_perspective(1, 100, aspect_ratio, r->fov_angle);
	else
		r->projection = get_orthographic(r->size.x, r->size.y, -1000, 1000);
	camera_update(&r->camera);
}
