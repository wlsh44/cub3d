/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 20:14:08 by jinhkim           #+#    #+#             */
/*   Updated: 2020/11/17 20:14:10 by jinhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include <math.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define W 13
# define A 0
# define S 1
# define D 2
# define ESC 53
# define LEFT 123
# define RIGHT 124
# define KEY_PRESS 2

# define TEX_W 64
# define TEX_H 64

# define MOVE_SPEED 0.1
# define ROT_SPEED 0.1

# define FLOOR 4
# define CEILING 5

# define K  0.01

typedef struct	s_img
{
	void		*img;
	int			*data;
	int			size;
	int			bpp;
	int			endian;
	int			x;
	int			y;
}				t_img;

typedef struct	s_ratio
{
	double		x;
	double		y;
}				t_ratio;

typedef struct	s_pos
{
	double		x;
	double		y;
}				t_pos;

typedef struct	s_dir
{
	double		x;
	double		y;
}				t_dir;

typedef struct	s_map
{
	int			x;
	int			y;
	int			**map;
	char		tmp[80][80];
}				t_map;

typedef struct	s_win
{
	void		*win;
	int			x;
	int			y;
}				t_win;

typedef struct	s_pair
{
	int			x;
	int			y;
}				t_pair;

typedef struct	s_sprite
{
	int			order[30];
	int			width;
	int			height;
	int			pos_x;
	double		dist[30];
	t_pair		tex;
	t_pair		start;
	t_pair		end;
	t_pos		transform;
}				t_sprite;

typedef struct	s_all
{
	t_win		win;
	t_img		img;
	t_pos		pos;
	t_dir		dir;
	t_dir		plane;
	t_map		map;
	t_pos		s_pos[30];
	void		*mlx;
	int			**buf;
	int			**texture;
	int			*z_buf;
	int			tex_num;
	int			sprite_num;
}				t_all;

typedef struct	s_ver
{
	t_dir		dir;
	t_pos		side_dist;
	t_pos		delta_dist;
	t_pair		tex;
	t_pair		pos;
	t_pair		step;
	char		wall;
	double		wall_dist;
	double		tex_pos;
	double		ratio;
	int			line_height;
	int			tex_num;
	int			start;
	int			end;
}				t_ver;

int				key_press(int key, t_all *all);
void			closed(t_all *all);

void			cubed(t_all *all, int save);

char			*get_line(char *save);
void			parse(t_all *all, char *file);
char			*save_trim(char *save);
char			*buf_join(char *save, char *buf);
int				newline_check(char *save, int read_size);

int				bitmap(t_all *all);

int				map_parse(t_all *all);
int				get_map_tmp(t_all *all, char *line);
int				check_srround(t_all *all, int y, int x);

void			print_error(int errno);

int				spaceskip(char *line, int *i);
int				ft_atoi(char *line, int *i);
int				namecheck(char *name, char *ext);
int				savecheck(char *name, char *save);
int				is_valid_map(t_all *all, int i, int j, int *flag);

int				get_next_line(int fd, char **line);
int				load_image(t_all *all, int *texture, char *path, t_img *img);
void			set_color(t_all *all, int num, unsigned int color);

void			ray_casting(t_all *all);

void			set_tex_num(t_all *all, t_ver *v);
void			init_add_to_buf(t_all *all, t_ver *v);
void			add_to_buf_ver(t_all *all, t_ver *v, int x);
void			dda_algorithm(t_all *all, t_ver *v);
void			get_dir(t_all *all, t_ver *v, int x);
void			init_dda(t_all *all, t_ver *v);

void			get_wall_dist(t_all *all, t_ver *v);
void			sort_sprite(t_sprite *s, int size);
void			get_sprite_dist(t_all *all, t_sprite *s);
void			get_pos_x(t_all *all, t_sprite *s, int i);
void			init_sprite(t_all *all, t_sprite *s, int i);
void			add_to_buf_spr(t_all *all, t_sprite *s);

void			get_camera_dir(t_all *all, t_dir *dir0, t_dir *dir1);
void			init_coordinates(t_all *all, t_pos *d, t_pos *floor, int y);
void			add_to_buf_hor(t_all *all, t_pos *d, t_pos *floor, int y);

int				check_last_border(t_all *all);
int				check_border(t_all *all, char *line);

void			position1(t_all *all, char pos);
void			position2(t_all *all, char pos);

#endif
