/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 18:59:31 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/10/09 18:59:31 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WIREFRAME_VECTOR_H
# define WIREFRAME_VECTOR_H

# include <stddef.h>

struct		s_vector {
	char	*data;
	size_t	size;
	size_t	capacity;
};

typedef struct s_vector	t_vector;

t_vector	ft_vector_create(size_t size);
void		ft_vector_append(t_vector *vec, char *data, size_t count);

#endif
