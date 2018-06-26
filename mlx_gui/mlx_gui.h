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
#define MLX_KEY_C 8
#define MLX_KEY_R 15
#define MLX_KEY_ESC 53
#define MLX_KEY_UP 126
#define MLX_KEY_DOWN 125
#define MLX_KEY_LEFT 123
#define MLX_KEY_RIGHT 124
#define MLX_KEY_PLUS 69
#define MLX_KEY_MINUS 78
#define MLX_KEY_MULTIPLY 67
#define MLX_KEY_DIVIDE 75
#define MLX_KEY_MAX 256

struct s_mlx_context
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*texture;
	t_renderer	renderer;
	bool		is_mouse_captured;
};
typedef struct s_mlx_context t_mlx_context;

void init_mlx(t_mlx_context *ctx, t_map map);

#endif
