#include "array.h"

#include "libft.h"

#include <stdlib.h>
#include <stdio.h>

t_array	array_create(size_t elem_size, size_t count)
{
	t_array vec;

	vec.capacity = count * 2;
	vec.size = 0;
	vec.elem_size = elem_size;
	vec.data = malloc(vec.capacity * vec.elem_size);
	return (vec);
}

void	array_append(t_array *vec, void *data, size_t count)
{
	if ((vec->size + count) > vec->capacity)
	{
		vec->data = ft_realloc(vec->data,
								vec->capacity * vec->elem_size,
								vec->capacity * vec->elem_size * 2);
		vec->capacity *= 2;
		return (array_append(vec, data, count));
	}
	ft_memcpy(vec->data + (vec->size * vec->elem_size), data,
			  count * vec->elem_size);
	vec->size += count;
}

void	shrink_to_fit(t_array *vec)
{
	vec->data = ft_realloc(vec->data,
						vec->capacity * vec->elem_size,
						vec->size * vec->elem_size);
	vec->capacity = (size_t)vec->size;
}

void	print_stats(t_array arr, char *msg)
{
	printf("%s: %.2f KB,  %i / %zu * %zu B\n",
		   msg,
		   (arr.capacity * arr.elem_size) / 1024.f,
		   arr.size, arr.capacity, arr.elem_size);
}

void	print_data(t_array *vec)
{
	int i;
	char **ptr = vec->data;

	i = 0;
	while (i < vec->size)
	{
		printf("[%d] %p: ", i, ptr + i);
		printf("%p\n", *(ptr + i));
		i++;
	}
}
