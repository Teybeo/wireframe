#include "map_reader.h"

#include "errors.h"
#include "get_next_line.h"
#include "libft.h"

#include <unistd.h>
#include <fcntl.h>
#include <array.h>
#include <printf.h>

static t_array generate_point_array(char *line, int y);
static t_array	load_map_lines(char const *filepath);
static void parse_map_lines(t_array line_array);

void	load_fdf(char const *filepath)
{
	t_array line_array;

	line_array = load_map_lines(filepath);
	parse_map_lines(line_array);
}

void parse_map_lines(t_array line_array)
{
	int i;

	i = 0;
	while (i < line_array.size)
	{
		generate_point_array(line_array.data + i, i);
		i++;
	}
}

t_array	load_map_lines(char const *filepath)
{
	int		fd;
	char	*line;
	int		status;
	t_array	line_array;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		exit_with_message(ERROR_OPEN_FAILED);
	status = GNL_OK;
	line_array = array_create(sizeof(char*), 10);
	int i = 0;
	while (status == GNL_OK)
	{
		status = get_next_line(fd, &line);
		printf("%p\n", (void *) line);
		array_append(&line_array, &line, 1);
		printf("%p\n", *((char**)line_array.data) + i);
		i++;
		ft_putendl(line);
	}

	print_data(&line_array);
	return (line_array);
}

t_array generate_point_array(char *line, int y)
{
	t_array	point_array;
	t_point	point;
	int		i;

	i = 0;
	point.x = 0;
	point.y = y;
	point_array = array_create(sizeof(t_point), 16);
	while (line[i] != '\0')
	{
		if (ft_is_space(line[i]) == false)
		{
			point.z = ft_atoi(&line[i]);
//			printf("x: %d, y: %d, z: %d\n", point.x, point.y, point.z);
			array_append(&point_array, &point, 1);
			point.x++;
			while (ft_is_space(line[i]) == false && line[i] != '\0')
				i++;
		}
		i++;
	}
	return (point_array);
}
