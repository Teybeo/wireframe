#include "map_reader.h"
#include "libft.h"
#include "sdl_gui.h"

int	main(int argc, char **argv)
{
	t_array segment_array;
	t_sdl_app context;

	if (argc != 2)
	{
		ft_putendl("usage:\t./fdf file");
		return (0);
	}
	segment_array = load_fdf(argv[1]);
	sdl_init(&context, segment_array);
	sdl_run(&context);
	return (0);
}
