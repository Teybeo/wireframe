/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 17:49:25 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/10/09 17:49:27 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RGB_H
# define RGB_H

# include <stdint.h>

# define R_SHIFT (16u)
# define G_SHIFT (8u)
# define B_SHIFT (0u)

struct		s_rgb
{
	float r;
	float g;
	float b;
};
typedef struct s_rgb	t_rgb;

t_rgb		rgb_add(t_rgb a, t_rgb b);
uint32_t	rgb_pack(t_rgb rgb);
t_rgb		rgb_unpack(int packed);
t_rgb		rgb_mul(t_rgb a, float factor);
t_rgb		get_rgb_incr(t_rgb start, t_rgb end, float extent);

#endif
