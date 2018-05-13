#ifndef LIBFT_H
# define LIBFT_H

#define ALLOW_SILENT_FAIL 0

#include <stddef.h>

void	ft_putendl(char const *s);
size_t	ft_strlen(char const *s);
int		ft_memchr(char const *data, ssize_t count, char c);
char	*ft_realloc(char *buffer, size_t size, size_t new_size);
void	*ft_memcpy(void *dst, const void *src, size_t count);
char	*ft_strndup(const char *src, size_t count);

#endif
