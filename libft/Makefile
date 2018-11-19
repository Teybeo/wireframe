NAME = libft.a

FILES += ft_atoi.c
FILES += ft_memchr.c
FILES += ft_memcpy.c
FILES += ft_memzero.c
FILES += ft_putendl.c
FILES += ft_realloc.c
FILES += ft_strndup.c
FILES += ft_strlen.c
FILES += ft_is_space.c
FILES += vector.c
FILES += array.c
FILES += get_next_line.c
FILES += rgb.c
FILES += vec3.c
FILES += vec3_part2.c
FILES += mat3.c
FILES += mat3_part2.c
FILES += mat4.c
FILES += mat4_projections.c

OBJS = $(FILES:.c=.o)

FLAGS = -Wall -Wextra -Werror
FLAGS += -O2 -march=native -flto

all: $(NAME)

# $^ is the dependencies of the rule
# $@ is the name of the rule
%.o : %.c
	gcc $(FLAGS) -o $@ -c $^

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all