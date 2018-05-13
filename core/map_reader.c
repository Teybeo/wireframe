#include "map_reader.h"

#include "errors.h"
#include "get_next_line.h"
#include "libft.h"

#include <unistd.h>
#include <fcntl.h>

void	read_map(char const *filepath)
{
	int		fd;
	char	*line;
	int		status;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		exit_with_message(ERROR_OPEN_FAILED);
	status = GNL_OK;
	while (status == GNL_OK)
	{
		status = get_next_line(fd, &line);
		ft_putendl(line);
	}
}
