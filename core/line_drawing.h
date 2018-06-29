#ifndef LINE_DRAWING_H
#define LINE_DRAWING_H

#include "vec3.h"
#include "renderer.h"

#define R_MASK (0x00FF0000)
#define G_MASK (0x0000FF00)
#define B_MASK (0x000000FF)

#define R_SHIFT (1 << 16)
#define G_SHIFT (1 << 8)
#define B_SHIFT (1 << 0)

#define RED(x) ((x & R_MASK) >> 16)
#define GREEN(x) ((x & G_MASK) >> 8)
#define BLUE(x) ((x & B_MASK) >> 0)

void draw_line(t_renderer renderer, t_vec3i a, t_vec3i b);

#endif
