#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t count)
{
	size_t i;

	i = 0;
	while (i < count)
	{
		((char*)dst)[i] = ((char*)src)[i];
		i++;
	}
	return (dst);
}
