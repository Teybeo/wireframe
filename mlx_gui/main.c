#include <array.h>
#include <libft.h>
#include <map_reader.h>
#include "mlx_gui.h"

int	main(int argc, char **argv)
{
	t_array segment_array;
	t_mlx_context ctx;

	if (argc != 2)
	{
		ft_putendl("usage:\t./fdf file");
		return (0);
	}
	segment_array = load_fdf(argv[1]);
	init_mlx(&ctx, segment_array);
	return (0);
}
