/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 13:08:39 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/05/11 13:08:39 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <limits.h>

# define BUFF_SIZE (1)

# define GNL_OK (1)
# define GNL_ENDED (0)
# define GNL_ERROR (-1)

int	get_next_line(const int fd, char **line);

#endif
