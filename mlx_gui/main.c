#include <array.h>
#include <libft.h>
#include <map_reader.h>
#include "mlx_gui.h"

int	main(int argc, char **argv)
{
	t_array segment_array;

	if (argc != 2)
	{
		ft_putendl("usage:\t./fdf file");
		return (0);
	}
	segment_array = load_fdf(argv[1]);
	toto();
	return (0);
}
