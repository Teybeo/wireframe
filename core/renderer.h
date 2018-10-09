/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 15:06:39 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/10/09 17:45:08 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WIREFRAME_RENDERER_H
# define WIREFRAME_RENDERER_H

# include "map_reader.h"
# include "camera.h"
# include "mat4.h"

# include <stdint.h>

enum	e_renderer_key {
	KEY_RUNKNOWN,
	KEY_SCALE_UP,
	KEY_SCALE_DOWN,
	KEY_FOV_UP,
	KEY_FOV_DOWN,
	KEY_PROJECTION_TOOGLE,
	KEY_FOG_TOOGLE,
	KEY_RCOUNT
};
typedef enum e_renderer_key	t_renderer_key;

struct	s_renderer {
	t_map		map;
	uint32_t	*pixels;
	float		*depth_buffer;
	t_vec2i		size;
	t_camera	camera;
	t_mat4		projection;
	float		scale_factor;
	float		fov_angle;
	char		use_perspective;
	char		use_fog;
};
typedef struct s_renderer	t_renderer;

void	renderer_init(t_renderer *r, void *pixels, t_map map, t_vec2i size);
void	renderer_event(t_renderer *renderer, t_renderer_key key);
void	renderer_update(t_renderer *r);
void	renderer_draw(t_renderer rndr);
void	compute_transform(t_renderer *renderer, t_mat4 *model_clip);

#endif
