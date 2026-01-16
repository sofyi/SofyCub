NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror 
INCLUDES = -IMLX42/include

# 🔍 كشف نظام التشغيل (Linux أو Darwin اللي هو Mac)
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
    # 🐧 Flags خاصين بـ Linux (Parrot/Ubuntu)
    MLX_FLAGS = -LMLX42/build -lmlx42 -lglfw -ldl -pthread -lm
else
    GLFW_LIB_DIR = /Users/$(USER)/goinfre/homebrew/lib
    MLX_FLAGS = -L$(GLFW_LIB_DIR) -lglfw \
                -LMLX42/build -lmlx42 \
                -framework Cocoa -framework OpenGL -framework IOKit
endif

MLX_DIR = MLX42
MLX_LIB = $(MLX_DIR)/build/libmlx42.a

SRCS = ./pars/pars.c ./pars/get_next_l.c ./pars/helper.c \
    ./pars/helper2.c ./pars/check.c ./pars/map_tool.c ./pars/free_fun.c\
    ./pars/check2.c ./pars/Libft2.c ./pars/LibftHelper.c ./pars/MapTols2.c\
	 ./raycasting/main.c ./raycasting/gun_anim.c ./raycasting/init_utils.c \
	 ./raycasting/minimap.c ./raycasting/movement.c ./raycasting/raycasting.c \
	 ./raycasting/render_utils.c  ./raycasting/textures.c \

OBJS = $(SRCS:.c=.o)

GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
RESET = \033[0m

all: mlx_install $(MLX_LIB) $(NAME)

mlx_install:
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "$(YELLOW)MLX library not found. Cloning MLX42 repository...$(RESET)"; \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX_DIR); \
	fi

$(MLX_LIB):
	@echo "$(YELLOW)Building MLX42...$(RESET)"
	@cmake -S $(MLX_DIR) -B $(MLX_DIR)/build -DCMAKE_BUILD_TYPE=Release
	@cmake --build $(MLX_DIR)/build -j4
	@echo "$(GREEN)MLX42 built successfully!$(RESET)"

$(NAME): $(OBJS)
	@echo "$(GREEN)Linking $(NAME)...$(RESET)"
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) $(INCLUDES) -o $(NAME)
	@echo "$(GREEN)Build complete!$(RESET)"

%.o: %.c
	@echo "$(GREEN)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJS)

fclean: clean
	@echo "$(RED)Cleaning $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@rm -rf $(MLX_DIR)/build
	@echo "$(RED)MLX42 build cleaned$(RESET)"

re: fclean all
s: all clean
.PHONY: all clean fclean re mlx_install