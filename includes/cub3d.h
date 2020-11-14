#ifndef CUB3D_H
# define CUB3D_H

#include <mlx.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define W 13
#define A 0
#define S 1
#define D 2
#define ESC 53
#define LEFT 123
#define RIGHT 124
#define KEY_PRESS 2
#define KEY_RELEASE 3

#define height 480
#define width 640
#define texNum 11
#define texWidth 64
#define texHeight 64

#define MOVE_SPEED 0.05
#define ROT_SPEED 0.05

#define FLOOR 5
#define CEILING 6

typedef struct	s_img
{
	void	*img;
	int		*data;
	int		size;
	int		bpp;
	int		endian;
	int		x;
	int		y;
}				t_img;

typedef struct s_ratio
{
    double x;
    double y;
} t_ratio;

typedef struct s_pos
{
    double x;
    double y;
} t_pos;

typedef struct s_dir
{
    double x;
    double y;
} t_dir;

typedef struct s_plane
{
    double x;
    double y;
} t_plane;

typedef struct s_map
{
    int x;
    int y;
    int **map;
} t_map;

typedef struct s_all
{
    void *mlx;
    void *win;
    t_img img;
    t_pos pos;
    t_dir dir;
    t_plane plane;
    int **buf;
    int **texture;
    t_map map;

} t_all;

int key_press(int key, t_all *all);
void ray_casting(t_all *all);

#endif