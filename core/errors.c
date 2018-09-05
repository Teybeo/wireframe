/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 14:52:18 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/09/05 14:52:18 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

#include <libft.h>
#include <stdlib.h>

void	exit_with_message(char const *string)
{
	ft_putendl(string);
	exit(0);
}
