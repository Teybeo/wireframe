NAME = fdf

SRCS += core/map_reader.c
SRCS += core/map_loader.c
SRCS += core/map_preprocess.c
SRCS += core/renderer.c
SRCS += core/renderer_update.c
SRCS += core/camera.c
SRCS += core/errors.c
SRCS += core/line_clipping.c
SRCS += core/line_drawing.c

OBJS =  $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror

LIBS = -l ft -L libft
INCLUDES = -I libft/ -I core/

##### MLX

MLX_SRCS += mlx_gui/main.c
MLX_SRCS += mlx_gui/mlx_gui.c
MLX_SRCS += mlx_gui/mlx_keyboard.c

MLX_OBJS =  $(MLX_SRCS:.c=.o)
MLX_INCLUDES = -I mlx_gui/ -I minilibx_macos/
# Custom MLX with added mlx_set_relative_mouse_mode()
MLX_LIBS = -l mlx -L minilibx_macos
MLX_LIBS += -framework OpenGL -framework AppKit

##### SDL

SDL_SRCS += sdl_gui/main.c
SDL_SRCS += sdl_gui/sdl_gui.c
SDL_SRCS += sdl_gui/sdl_keyboard.c

SDL_OBJS = $(SDL_SRCS:.c=.o)
SDL_CFLAGS = $(shell sdl2-config --cflags)
SDL_LDFLAGS = $(shell sdl2-config --libs)

ifeq ($(MAKECMDGOALS), sdl)
OBJS += $(SDL_OBJS)
INCLUDES += $(SDL_CFLAGS)
LIBS += $(SDL_LDFLAGS)
else
OBJS += $(MLX_OBJS)
INCLUDES += $(MLX_INCLUDES)
LIBS += $(MLX_LIBS)
endif

all: $(NAME)

mlx sdl: $(NAME)

$(NAME): $(OBJS)
	make -C ./libft
	gcc -o $(NAME) $(OBJS) $(INCLUDES) $(LIBS)

# $^ is the dependencies of the rule
# $@ is the name of the rule
%.o : %.c
	gcc $(FLAGS) -c $^ $(INCLUDES) -o $@

clean :
	make clean -C ./libft
	rm -f $(OBJS) $(MLX_OBJS) $(SDL_OBJS)

fclean : clean
	make fclean -C ./libft
	rm -f $(NAME)

re : fclean $(NAME)
