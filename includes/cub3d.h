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
#define KEY_PRESS 2
#define KEY_RELEASE 3

#define height 480
#define width 640

typedef struct	s_img
{
	void	*img;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}				t_img;

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

typedef struct s_all
{
    s_pos pos;
    s_dir dir;
    s_plane plane;
    
} t_all;

#endif