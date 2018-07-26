#include <stdlib.h>

char	*ft_realloc(char *buffer, size_t current_size, size_t new_size)
{
	char	*new_buffer;
	size_t	i;
	size_t	smallest_size;

	if (!(new_buffer = malloc(sizeof(char) * new_size)))
		return (0);
	i = 0;
	smallest_size = current_size < new_size ? current_size : new_size;
	while (i < smallest_size)
	{
		new_buffer[i] = buffer[i];
		i++;
	}
	free(buffer);
	return (new_buffer);
}
