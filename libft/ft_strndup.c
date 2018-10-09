/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 18:43:32 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/10/09 18:43:32 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

char	*ft_strndup(const char *src, size_t count)
{
	char	*new;

	new = malloc(count + 1);
	if (new == NULL)
		return (NULL);
	new[count] = '\0';
	ft_memcpy(new, src, count);
	return (new);
}
