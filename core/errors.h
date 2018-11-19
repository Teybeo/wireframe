/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 14:53:12 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/11/19 14:23:30 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define DEV 1

# if DEV == 1
#  define ERROR_OPEN_FAILED "Couldn't open file"
#  define ERROR_EMPTY_FILE "File is empty"
# else
#  define ERROR_OPEN_FAILED "error"
#  define ERROR_EMPTY_FILE "error"
# endif

void	exit_with_message(char const *string);

#endif
