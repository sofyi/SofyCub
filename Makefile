NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror 
INCLUDES = -IMLX42/include

GLFW_LIB_DIR = /Users/slamhaou/.brew/lib
MLX_FLAGS = -L$(GLFW_LIB_DIR) -lglfw \
            -LMLX42/build -lmlx42 \
            -framework Cocoa -framework OpenGL -framework IOKit


MLX_DIR = MLX42
MLX_LIB = $(MLX_DIR)/build/libmlx42.a

SRCS = ./pars/pars.c ./pars/get_next_l.c ./pars/helper.c \
    ./pars/helper2.c ./pars/check.c ./pars/map_tool.c ./pars/free_fun.c\
    ./pars/check2.c ./pars/Libft2.c ./pars/LibftHelper.c ./pars/MapTols2.c\
	 main.c ./raycasting/gun_anim.c ./raycasting/init_utils.c \
	 ./raycasting/minimap.c ./raycasting/movement.c ./raycasting/raycasting.c \
	 ./raycasting/render_utils.c  ./raycasting/textures.c ./raycasting/rayc_utils.c\

OBJS = $(SRCS:.c=.o)

all: mlx_install $(MLX_LIB) $(NAME)

mlx_install:
	@if [ ! -d "$(MLX_DIR)" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX_DIR); \
	fi

$(MLX_LIB):
	@cmake -S $(MLX_DIR) -B $(MLX_DIR)/build -DCMAKE_BUILD_TYPE=Release
	@cmake --build $(MLX_DIR)/build -j4

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) $(INCLUDES) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(MLX_DIR)/build

re: fclean all
s: all clean
.PHONY: all clean fclean re mlx_install