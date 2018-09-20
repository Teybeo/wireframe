#ifndef WIREFRAME_RGB_H
# define WIREFRAME_RGB_H

#include <stdint.h>

# define R_SHIFT (16u)
# define G_SHIFT (8u)
# define B_SHIFT (0u)

struct s_rgb
{
	float r;
	float g;
	float b;
};
typedef struct s_rgb t_rgb;

t_rgb		rgb_add(t_rgb a, t_rgb b);
t_rgb		rgb_sub(t_rgb a, t_rgb b);
uint32_t	rgb_pack(t_rgb rgb);
t_rgb		rgb_unpack(int packed);
t_rgb		rgb_mul(t_rgb a, float factor);

#endif
