#SRCS = srcs/*.c
#OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

NAME = cub3D

SRC = cub3d.c \
		key.c \
		ray_casting.c \
		parse.c \
		gnl.c

#DIR_SRCS = ./srcs/

DIR_SRCS = ./srcs/

HEADER = ./includes/

LIBMLX = libmlx.dylib \
			libmlx.a

SRCS = $(addprefix $(DIR_SRCS), $(SRC))

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		$(MAKE) -C ./minilibx_mms
		$(MAKE) -C ./minilibx_opengl
		cp ./minilibx_mms/libmlx.dylib libmlx.dylib
		cp ./minilibx_opengl/libmlx.a libmlx.a
		$(CC) $(FLAGS) -I $(HEADER) $(LIBMLX) $(OBJS) -o $(NAME)

.c.o:
		$(CC) $(FLAGS) -I $(HEADER) -c $< -o $@

clean:
		rm -rf $(OBJS)

fclean: clean
		$(MAKE) clean -C ./minilibx_mms
		$(MAKE) clean -C ./minilibx_opengl
		rm -rf libmlx.dylib
		rm -rf libmlx.a
		rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re

