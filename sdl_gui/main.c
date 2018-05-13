#include <stdio.h>
#include "libft.h"
#include "sdl_gui.h"
#include "renderer.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putendl("usage:\t./fdf file");
		return (0);
	}
	core_init(argv[1]);
	sdl_init();
	sdl_run();
	return (0);
}
