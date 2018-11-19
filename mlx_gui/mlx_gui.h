/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_gui.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 15:53:06 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/11/19 15:02:47 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_GUI_H
# define MLX_GUI_H

# include "renderer.h"
# include "mlx.h"

# define MLX_KEY_W 13
# define MLX_KEY_A 0
# define MLX_KEY_S 1
# define MLX_KEY_D 2
# define MLX_KEY_Q 12
# define MLX_KEY_Z 6
# define MLX_KEY_C 8
# define MLX_KEY_R 15
# define MLX_KEY_P 35
# define MLX_KEY_T 17
# define MLX_KEY_F 3
# define MLX_KEY_ESC 53
# define MLX_KEY_CURSOR 50
# define MLX_KEY_UP 126
# define MLX_KEY_DOWN 125
# define MLX_KEY_LEFT 123
# define MLX_KEY_RIGHT 124
# define MLX_KEY_PLUS 69
# define MLX_KEY_MINUS 78
# define MLX_KEY_MULTIPLY 67
# define MLX_KEY_DIVIDE 75
# define MLX_KEY_MAX 256

typedef struct	s_mlx_context
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*texture;
	t_renderer	renderer;
	bool		is_mouse_captured;
}				t_mlx_context;

void			init_mlx(t_mlx_context *ctx, t_map map);

t_camera_key	get_camera_key(int keycode);
t_renderer_key	get_renderer_key(int keycode);
int				keydown_event(int keycode, void *param);
int				keyup_event(int keycode, void *param);

#endif
