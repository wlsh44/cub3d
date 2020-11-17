CC = gcc

FLAGS = -g

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

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(FLAGS) -I $(HEADER) -lmlx -framework OpenGL -framework AppKit $(OBJS) -o $(NAME)

.c.o:
		$(CC) $(FLAGS) -I $(HEADER) -c $< -o $@

clean:
		rm -rf $(OBJS)

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re

