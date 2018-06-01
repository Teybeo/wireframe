#ifndef LINE_CLIPPING_H
#define LINE_CLIPPING_H

#include "vec3.h"

#define INSIDE 0  // 0000
#define LEFT 1    // 0001
#define RIGHT 2   // 0010
#define BOTTOM 4  // 0100
#define TOP 8     // 1000

int clip_line(t_vec2i *a, t_vec2i *b, t_vec2i window);

#endif
