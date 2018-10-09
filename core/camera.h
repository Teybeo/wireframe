/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 14:52:03 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/10/09 17:04:36 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include <stdbool.h>
# include <mat3.h>

enum	e_camera_key {
	KEY_UNKNOWN,
	KEY_FORWARD,
	KEY_BACKWARD,
	KEY_RIGHT,
	KEY_LEFT,
	KEY_UPWARD,
	KEY_DOWNWARD,
	KEY_UP_ARROW,
	KEY_DOWN_ARROW,
	KEY_LEFT_ARROW,
	KEY_RIGHT_ARROW,
	KEY_CAMERA_MODE_TOGGLE,
	KEY_CAMERA_RESET,
	KEY_CAMERA_PRINT_POS,
	KEY_COUNT
};
typedef enum e_camera_key	t_camera_key;

enum	e_camera_mode
{
	CAMERA_FREEFLY,
	CAMERA_ORBIT
};
typedef enum e_camera_mode	t_camera_mode;

struct	s_camera {
	t_vec3			pos;
	t_mat3			rotation;
	float			y_angle;
	float			x_angle;
	float			speed_factor;
	t_camera_mode	mode;
	bool			key_state[KEY_COUNT];
};

typedef struct s_camera	t_camera;

void	init_camera(t_camera *camera, float speed_factor);
void	camera_key_event(t_camera *camera, t_camera_key key, int state);
void	camera_mouse_event(t_camera *camera, int x, int y);
void	camera_update(t_camera *camera);
void	compute_basis_vectors(t_camera *camera,
							t_vec3 *strafe, t_vec3 *upward, t_vec3 *backward);

#endif
