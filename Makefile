# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: utilisateur <utilisateur@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/03 15:04:11 by nbaldes           #+#    #+#              #
#    Updated: 2026/03/05 16:36:19 by utilisateur      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Executable's Name
NAME = Cub3D

# Directory
SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = includes
LIBFT_DIR = $(INCLUDE_DIR)/libft

# Source files
SRCS = src/main.c \

# Objets
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Compilating Flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g 
INCLUDES = -I$(INCLUDE_DIR) -I$(LIBFT_DIR) -I/usr/include
LDFLAGS = -g #-L./includes/minilibx-linux -lmlx -lXext -lX11
# Libft
LIBFT = $(LIBFT_DIR)/libft.a

# Colors
GREEN = \033[0;32m
RESET = \033[0m

# Default's Rules
all: $(NAME)

# Compiling executable
$(NAME): $(LIBFT) $(PIPEX) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)✔ Compilation réussie !$(RESET)"

# Compiling files .o into obj's directory
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compiling Libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Cleaning Object
clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

# Full Cleaning
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

#  Full Recompiling
re: fclean all

.PHONY: all clean fclean re