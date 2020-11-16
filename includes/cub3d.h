#ifndef CUB3D_H
# define CUB3D_H

#include <mlx.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define W 13
#define A 0
#define S 1
#define D 2
#define ESC 53
#define LEFT 123
#define RIGHT 124
#define KEY_PRESS 2
#define KEY_RELEASE 3

// #define height 480
// #define width 640
#define texNum 11
#define texWidth 64
#define texHeight 64

#define MOVE_SPEED 0.05
#define ROT_SPEED 0.05

#define FLOOR 4
#define CEILING 5

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

typedef struct s_map
{
    int x;
    int y;
    int **map;
	char tmp[50][50];
} t_map;

typedef struct s_win
{
    void *win;
    int x;
    int y;
} t_win;


// typedef struct s_sprite
// {
//     t_pos pos;

// }   t_sprite;

typedef struct s_pair
{
    int x;
    int y;
} t_pair;

typedef struct s_sprite
{
    int *order;
    int width;
    int height;
    int pos_x;
    double *dist;
    t_pair tex;
    t_pair start;
    t_pair end;
    t_pos transform;
    //t_pos pos;
}   t_sprite;


typedef struct s_all
{
    void *mlx;
    t_win win;
    t_img img;
    t_pos pos;
    t_dir dir;
    t_dir plane;
    int **buf;
    int **texture;
    int *z_buf;
    int tex_num;
    t_map map;
    int sprite_num;
    t_pos s_pos[30];
} t_all;

typedef struct s_ver
{
    t_dir dir;
    t_pos side_dist;
    t_pos delta_dist;
    t_pair tex;
    t_pair pos;
    t_pair step;
    char wall;
    double wall_dist;
    double tex_pos;
    double ratio;
    int line_height;
    int tex_num;
    int start;
    int end;
}   t_ver;

int key_press(int key, t_all *all);
void ray_casting(t_all *all);

char *get_line(char *save);
void parse(t_all *all, char *file);
char *save_trim(char *save);
char *buf_join(char *save, char *buf);
int newline_check(char *save, int read_size);
#endif