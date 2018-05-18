#include "map_reader.h"
#include "libft.h"
#include "sdl_gui.h"
#include "renderer.h"

int	main(int argc, char **argv)
{
	t_array segment_array;
	t_sdl_context context;

	if (argc != 2)
	{
		ft_putendl("usage:\t./fdf file");
		return (0);
	}
	segment_array = load_fdf(argv[1]);
	renderer_init();
	sdl_init(&context);
	sdl_run(&context, segment_array);
	return (0);
}
