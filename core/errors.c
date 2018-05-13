#include "errors.h"

#include <libft.h>
#include <stdlib.h>

void	exit_with_message(char const *string)
{
	ft_putendl(string);
	exit(0);
}
