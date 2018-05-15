#ifndef WIREFRAME_ARRAY_H
#define WIREFRAME_ARRAY_H

#include <stddef.h>

struct		s_array {
	void	*data;
	size_t	size;
	size_t	elem_size;
	size_t	capacity;
};

typedef struct s_array	t_array;

t_array	array_create(size_t elem_size, size_t count);
void	array_append(t_array *vec, void *data, size_t count);
void	print_data(t_array *vec);

#endif
