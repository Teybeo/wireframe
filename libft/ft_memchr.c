#include <unistd.h>

int	ft_memchr(char const *data, ssize_t count, char c)
{
	int	i;

	i = -1;
	while (++i < count)
		if (data[i] == c)
			return (i);
	return (-1);
}
