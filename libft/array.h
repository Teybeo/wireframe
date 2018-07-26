#ifndef WIREFRAME_ARRAY_H
#define WIREFRAME_ARRAY_H

#include <stddef.h>

struct		s_array {
	void	*data;
	int		size;
	size_t	elem_size;
	size_t	capacity;
};

typedef struct s_array	t_array;

t_array	array_create(size_t elem_size, size_t count);
void	array_append(t_array *vec, void *data, size_t count);
void	shrink_to_fit(t_array *vec);
void	print_stats(t_array arr, char *msg);
void	print_seg(t_array *vec);
void	print_vec4(t_array *vec);

#endif
