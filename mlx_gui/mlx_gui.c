#include "mlx_gui.h"

#include <stdio.h>

int key_event(int keycode, int is_up, void *param)
{
	if (is_up)
		printf("Released %d\n", keycode);
	else
		printf("Pressed %d\n", keycode);
	return 0;
}

int keydown_event(int keycode, void *param)
{
	return key_event(keycode, 0, param);
}
int keyup_event(int keycode, void *param)
{
	return key_event(keycode, 1, param);
}

void toto()
{
	void	*mlx_ptr;
	void *win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1600, 900, "Wireframe");
	mlx_do_key_autorepeatoff(mlx_ptr);
	mlx_hook(win_ptr, 2, 0xFFFFFFFF, keydown_event, NULL);
	mlx_hook(win_ptr, 3, 0xFFFFFFFF, keyup_event, NULL);
	mlx_loop(mlx_ptr);
}