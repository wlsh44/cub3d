CC = gcc

FLAGS = -Wall -Wextra -Werror -fsanitize=address
NAME = cub3D

SRC = main.c \
		cub3d.c \
		key.c \
		ray.c \
		ray_ver.c \
		ray_ver2.c \
		ray_hor.c \
		sprite.c \
		parse.c \
		parse_map.c \
		parse_map2.c \
		parse_utils.c \
		gnl.c \
		bitmap.c \
		error.c \
		utils.c \

DIR_SRCS = ./srcs/

HEADER = ./includes/

SRCS = $(addprefix $(DIR_SRCS), $(SRC))

OBJS = $(SRCS:.c=.o)

MLX				= libmlx.dylib

all: $(NAME)

$(NAME): $(MLX) $(OBJS)
		#$(CC) $(FLAGS) -I $(HEADER) -lmlx -framework $(OBJS) -o $(NAME)
		$(CC) $(FLAGS) -I $(HEADER) -lmlx -framework OpenGL -framework AppKit $(MLX) $(OBJS) -o $(NAME)

$(MLX):
				@$(MAKE) -C minilibx_mms_20200219
				@mv minilibx_mms_20200219/$(MLX) .

.c.o:
		$(CC) $(FLAGS) -I $(HEADER) -c $< -o $@

clean:
		rm -rf $(OBJS) $(MLX)

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re

