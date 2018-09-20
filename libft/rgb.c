#include "rgb.h"

t_rgb	rgb_unpack(int packed)
{
	t_rgb res;

	res.r = (packed >> R_SHIFT) & 0xFF;
	res.g = (packed >> G_SHIFT) & 0xFF;
	res.b = (packed >> B_SHIFT) & 0xFF;
	return (res);
}

uint32_t	rgb_pack(t_rgb rgb)
{
	uint32_t res;

	res = 0;
	res += (uint8_t)rgb.r << R_SHIFT;
	res += (uint8_t)rgb.g << G_SHIFT;
	res += (uint8_t)rgb.b << B_SHIFT;
	return (res);
}

t_rgb	rgb_add(t_rgb a, t_rgb b)
{
	t_rgb res;
	res.r = a.r + b.r;
	res.g = a.g + b.g;
	res.b = a.b + b.b;
	return (res);
}

t_rgb	rgb_sub(t_rgb a, t_rgb b)
{
	t_rgb res;
	res.r = a.r - b.r;
	res.g = a.g - b.g;
	res.b = a.b - b.b;
	return (res);
}

t_rgb	rgb_mul(t_rgb a, float factor)
{
	a.r *= factor;
	a.g *= factor;
	a.b *= factor;
	return (a);
}