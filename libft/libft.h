#ifndef LIBFT_H
# define LIBFT_H

# ifdef __APPLE__
#  include <unistd.h>
# endif

# include <stddef.h>

#define true 1
#define false 0

int		ft_atoi(char const *str);
int		ft_is_space(char c);
void	ft_memzero(void *src, size_t elem_count, size_t elem_size);
int		ft_memchr(char const *data, ssize_t count, char c);
void	*ft_memcpy(void *dst, const void *src, size_t count);
void	ft_putendl(char const *s);
char	*ft_realloc(char *buffer, size_t size, size_t new_size);
size_t	ft_strlen(char const *s);
char	*ft_strndup(const char *src, size_t count);

#endif
