/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 18:58:39 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/10/09 18:58:39 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "vector.h"

#include <stdlib.h>

t_vector	ft_vector_create(size_t size)
{
	t_vector vec;

	vec.capacity = size * 2;
	vec.size = 0;
	vec.data = malloc(vec.capacity);
	return (vec);
}

void		ft_vector_append(t_vector *vec, char *data, size_t count)
{
	if ((vec->size + count) > vec->capacity)
	{
		vec->data = ft_realloc(vec->data, vec->capacity, vec->capacity * 2);
		vec->capacity *= 2;
		return (ft_vector_append(vec, data, count));
	}
	ft_memcpy(vec->data + vec->size, data, count);
	vec->size += count;
}
