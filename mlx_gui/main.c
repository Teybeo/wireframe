#include <array.h>
#include <libft.h>
#include <map_reader.h>
#include "mlx_gui.h"

#if   __STDC_VERSION__ >= 201112L
	#define __C_STD__ "11"
#elif __STDC_VERSION__ >= 199901L
	#define __C_STD__ "99"
#else
	#define __C_STD__ "90"
#endif

#pragma message(__C_STD__)

int	main(int argc, char **argv)
{
	t_map map;
	t_mlx_context ctx;

	if (argc != 2)
	{
		ft_putendl("usage:\t./fdf file");
		return (0);
	}
	map = load_fdf(argv[1]);
	init_mlx(&ctx, map);
	return (0);
}
