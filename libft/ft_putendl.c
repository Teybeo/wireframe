#include "libft.h"

#include <unistd.h>

void	ft_putendl(char const *s)
{
	if (ALLOW_SILENT_FAIL && (s == NULL))
		return ;
	write(STDOUT_FILENO, s, ft_strlen(s));
	write(STDOUT_FILENO, "\n", 1);
}
