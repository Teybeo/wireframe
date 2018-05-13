/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 13:11:51 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/05/11 16:45:42 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include "libft.h"
#include "vector.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

t_vector	*get_vector_for_fd(const int fd)
{
	static t_vector	vector_array[FOPEN_MAX];

	if (vector_array[fd].capacity == 0)
		vector_array[fd] = ft_vector_create(64);
	return (&vector_array[fd]);
}

int			handle_last_read(t_vector *vector, char **line)
{
	if (vector->size == 0)
		return (GNL_ENDED);
	*line = ft_strndup(vector->data, vector->size);
	vector->size = 0;
	return (GNL_OK);
}

int			get_next_line(const int fd, char **line)
{
	char		buffer[BUFF_SIZE];
	ssize_t		read_return;
	t_vector	*vec;
	int			end_index;

	if (line == NULL || fd < 0 || fd > FOPEN_MAX)
		return (GNL_ERROR);
	vec = get_vector_for_fd(fd);
	while ((read_return = read(fd, buffer, BUFF_SIZE)) != GNL_ERROR)
	{
		ft_vector_append(vec, buffer, (size_t)read_return);
		end_index = ft_memchr(vec->data, vec->size, '\n');
		if (end_index > -1)
		{
			*line = ft_strndup(vec->data, (size_t)end_index);
			end_index++;
			ft_memcpy(vec->data, vec->data + end_index, vec->size - end_index);
			vec->size -= end_index;
			return (GNL_OK);
		}
		if (read_return == GNL_ENDED)
			return (handle_last_read(vec, line));
	}
	return (read_return);
}
