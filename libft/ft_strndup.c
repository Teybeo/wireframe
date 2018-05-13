#include "libft.h"

#include <stdlib.h>

char	*ft_strndup(const char *src, size_t count)
{
	char	*new;

	new = malloc(count + 1);
	if (new == NULL)
		return (NULL);
	new[count] = '\0';
	ft_memcpy(new, src, count);
	return (new);
}
