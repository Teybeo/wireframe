#ifndef MLX_GUI_H
#define MLX_GUI_H

#include "renderer.h"
#include "mlx.h"

#define MLX_KEY_W 13
#define MLX_KEY_A 0
#define MLX_KEY_S 1
#define MLX_KEY_D 2
#define MLX_KEY_Q 12
#define MLX_KEY_Z 6

struct s_mlx_context
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*texture;
	t_renderer	renderer;
	t_array		segment_array;
};
typedef struct s_mlx_context t_mlx_context;

void init_mlx(t_mlx_context *ctx, t_array segment_array);

#endif
