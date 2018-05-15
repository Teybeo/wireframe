#ifndef MAP_READER_H
#define MAP_READER_H

struct s_point {
	int x;
	int y;
	int z;
};
typedef struct s_point t_point;

struct s_segment {
	t_point start;
	t_point end;
};
typedef struct s_segment t_segment;

struct s_segment_array {
	t_segment	*array;
	int			count;
};
typedef struct s_segment_array t_segment_array;

struct s_point_list {
	t_point	*point;
	int		count;
};
typedef struct s_point_list t_point_list;

void	load_fdf(char const *filepath);

#endif
