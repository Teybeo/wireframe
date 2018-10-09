/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 16:12:13 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/10/09 17:34:59 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sdl_gui.h"

int	main(int argc, char **argv)
{
	t_map		map;
	t_sdl_app	context;

	if (argc != 2)
	{
		ft_putendl("usage:\t./fdf file");
		return (0);
	}
	map = load_fdf(argv[1]);
	sdl_init(&context, map);
	sdl_run(&context);
	return (0);
}
