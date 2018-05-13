#include <stdlib.h>

char	*ft_realloc(char *buffer, size_t size, size_t new_size)
{
	char	*new_buffer;
	size_t	i;

	if (!(new_buffer = malloc(sizeof(char) * new_size)))
		return (0);
	i = 0;
	while (i < size)
	{
		new_buffer[i] = buffer[i];
		i++;
	}
	free(buffer);
	return (new_buffer);
}
