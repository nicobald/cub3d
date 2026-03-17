# Executable's Name
NAME = Cub3D

# Directory
SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = includes
LIBFT_DIR = $(INCLUDE_DIR)/libft
MLX_DIR = $(INCLUDE_DIR)/minilibx-linux
MLX_REPO = https://github.com/42Paris/minilibx-linux.git

# Source files
SRCS = src/error_file.c \
	   src/get_next_line.c \
	   src/main.c \
	   src/parse_args.c \
	   src/parse_file.c \
	   src/parse_type.c \
	   src/utils.c \
	   src/utils_2.c \
	   src/mlx.c \
	   src/parse_map.c \

# Objets
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Compilating Flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g
INCLUDES = -I$(INCLUDE_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

# Libft
LIBFT = $(LIBFT_DIR)/libft.a

# Default rule
all: $(NAME)

# Compile executable
$(NAME): $(LIBFT) $(MLX_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

# Compile .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# MinilibX auto install + build
$(MLX_DIR):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		git clone $(MLX_REPO) $(MLX_DIR); \
	fi
	@$(MAKE) -C $(MLX_DIR)

# Clean
clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	@if [ -d "$(MLX_DIR)" ]; then $(MAKE) -C $(MLX_DIR) clean; fi

# Full clean
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	@if [ -d "$(MLX_DIR)" ]; then rm -rf $(MLX_DIR); fi

# Re
re: fclean all

.PHONY: all clean fclean re