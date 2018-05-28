#include "libft.h"

void	ft_memzero(void *src, size_t count)
{
	while (--count)
		((char*)src)[count] = 0;
}

