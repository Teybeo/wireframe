#include "map_preprocess.h"

#include "vec3.h"
#include "renderer.h"
#include <limits.h>
#include <math.h>
#include <stdlib.h>

void	compute_boundingbox(t_map *map)
{
	int		i;
	t_vec3	max;
	t_vec3	min;
	t_vec4	*vertex_ptr;

	min = (t_vec3){INT_MAX, INT_MAX, INT_MAX};
	max = (t_vec3){INT_MIN, INT_MIN, INT_MIN};
	vertex_ptr = map->vertex_array.data;
	i = 0;
	while (i < map->vertex_array.size)
	{
		min = vec3_min(min, *(t_vec3 *)(vertex_ptr + i));
		max = vec3_max(max, *(t_vec3 *)(vertex_ptr + i));
		i++;
	}
	map->min = min;
	map->max = max;
}

void	do_center_map(t_map *map)
{
	int		i;
	t_vec3	center;
	t_vec4	*vertex_ptr;

	center = vec3_mul_scalar(vec3_sub(map->max, map->min), 0.5);
	center.y = 0;
	vertex_ptr = map->vertex_array.data;
	i = 0;
	while (i < map->vertex_array.size)
	{
		vec3_sub_this((t_vec3 *)(vertex_ptr + i), center);
		i++;
	}
}

void	init_gradient(grad_step *gradient)
{
	gradient[0].treshold = 0;
	gradient[1].treshold = 0.01;
	gradient[2].treshold = 0.1;
	gradient[3].treshold = 0.4;
	gradient[4].treshold = 0.6;
	gradient[5].treshold = 1;
	gradient[0].color = 0x000000FF;
	gradient[1].color = 0x00008800;
	gradient[2].color = 0x00FFFF88;
	gradient[3].color = 0x00880000;
	gradient[4].color = 0x00FFFFFF;
	gradient[5].color = 0x00FFFFFF;
}

void	compute_colors(t_map *map)
{
	int			i;
	t_vec4		*vertex_ptr;

	grad_step	gradient[GRADIENT_COUNT];
	init_gradient(gradient);
	i = 0;
	vertex_ptr = map->vertex_array.data;
	while (i < map->vertex_array.size)
	{
		vertex_ptr[i].w = get_color_from_height2(map, gradient, vertex_ptr[i].y);
		i++;
	}
}

int		get_color_from_height2(t_map *map, grad_step *gradient, float height)
{
//	return 0x00FFFFFF;
	int		i;
	float	min;
	float	max;
	float	factor;

	height = (height - map->min.y) / (map->max.y - map->min.y);
	i = 0;
	while (i < GRADIENT_COUNT)
	{
		if (height < gradient[i].treshold)
			break ;
		i++;
	}
	i = fminf(i, GRADIENT_COUNT - 1);
	i--;
//	printf("height: %6g = [%d -> %d]\n", height, i, i + 1);
//	return renderer->gradient[i].color;
	min = gradient[i].treshold;
	max = gradient[i + 1].treshold;
	factor = (height - min) / (max - min);
	return (color_mix(factor, gradient[i].color, gradient[i + 1].color));
}
