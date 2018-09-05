/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 15:51:11 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/09/05 15:51:13 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "map_reader.h"
#include "mlx_gui.h"

int	main(int argc, char **argv)
{
	t_map			map;
	t_mlx_context	ctx;

	if (argc != 2)
	{
		ft_putendl("usage:\t./fdf file");
		return (0);
	}
	map = load_fdf(argv[1]);
	init_mlx(&ctx, map);
	return (0);
}
