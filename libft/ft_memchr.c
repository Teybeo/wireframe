/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 18:39:19 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/10/09 18:39:19 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_memchr(char const *data, ssize_t count, char c)
{
	int	i;

	i = -1;
	while (++i < count)
		if (data[i] == c)
			return (i);
	return (-1);
}
