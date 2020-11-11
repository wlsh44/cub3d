#include <stdio.h>
#include <math.h>
#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>

#define mapWidth 24
#define mapHeight 24
#define WINH 480
#define WINW 640
#define texWidth 64
#define texHeight 64

#define W 13
#define A 0
#define S 1
#define D 2
#define ESC 53
#define UPPER 126
#define DOWN 125
#define LEFT_ARROW 123
#define RIGHT_ARROW 124

int	Map[mapWidth][mapHeight] =
						{
							{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
							{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
							{4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
							{4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
							{4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
							{4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
							{4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
							{4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
							{4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
							{4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
							{4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
							{4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
							{6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
							{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
							{6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
							{4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
							{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
							{4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
							{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
							{4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
							{4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
							{4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
							{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
							{4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
						};

typedef struct pos {
	double x;
	double y;
} t_pos;

typedef struct dir {
	double x;
	double y;
} t_dir;

typedef struct dist {
	double x;
	double y;
} t_dist;

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

typedef struct all {
	void	*mlx;
	void	*win;
	t_pos pos;
	t_dir dir;
	t_dir ray;
	t_dir plane;
	double camera;
	double moveSpeed;
	double rotSpeed;
	int		**buf;
	int		**texture;
	t_img img;
} t_all;

t_pos get_step(t_dist *side, t_dist delta, t_all *all, t_pos map) {
	t_pos step;

	if (all->ray.x < 0) {
		step.x = -1;
		side->x = (all->pos.x - map.x) * delta.x;
	} else {
		step.x = 1;
		side->x = (map.x + 1 - all->pos.x) * delta.x;
	}
	if (all->ray.y < 0) {
		step.y = -1;
		side->y = (all->pos.y - map.y) * delta.y;
	} else {
		step.y = 1;
		side->y = (map.y + 1 - all->pos.y) * delta.y;
	}
	return step;
}

void	verLine(t_all *all, int x, int y1, int y2, int color)
{
	int	y;

	y = y1;
	while (y <= y2)
	{
		mlx_pixel_put(all->mlx, all->win, x, y, color);
		y++;
	}
}

void	draw(t_all *all)
{
	for (int y = 0; y < WINH; y++)
	{
		for (int x = 0; x < WINW; x++)
		{
			all->img.data[y * WINW + x] = all->buf[y][x];
		}
	}
	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
}

void ray_casting(t_all *all) {
	int x;

	x = 0;
	while (x < WINW) {
		t_pos map;
		t_dist side;
		t_dist delta;
		t_pos step;
		int hit = 0;
		char wall;

		all->camera = 2 * x / (double)WINW - 1;
		all->ray.x = all->dir.x + all->plane.x * all->camera;
		all->ray.y = all->dir.y + all->plane.y * all->camera;

		map.x = (int)all->pos.x;
		map.y = (int)all->pos.y;

		delta.x = fabs(1 / all->ray.x);
		delta.y = fabs(1 / all->ray.y);
		step = get_step(&side, delta, all, map);

		while (hit == 0) {
			if (side.x < side.y) {
				side.x += delta.x;
				map.x += step.x;
				wall = 'x';
			} else {
				side.y += delta.y;
				map.y += step.y;
				wall = 'y';
			}
			if(Map[(int)map.x][(int)map.y] > 0)
				hit = 1;
		}

		double perp_wall_dist;

		if (wall == 'x') {
			perp_wall_dist = (map.x - all->pos.x + (1 - step.x) / 2) / all->ray.x;
		} else {
			perp_wall_dist = (map.y - all->pos.y + (1 - step.y) / 2) / all->ray.y;
		}

		int vertical = (int)(WINH / perp_wall_dist);
		int draw_start = -vertical / 2 + WINH / 2;
		if (draw_start < 0)
			draw_start = 0;
		int draw_end = vertical / 2 + WINH / 2;
		if (draw_end >= WINH)
			draw_end = WINH - 1;

		// int color;
		// switch(Map[(int)map.x][(int)map.y]) {
		// 	case 1: color = 0xFF3D3D; break;
		// 	case 2: color = 0x38D332; break;
		// 	case 3: color = 0x443BF7; break;
		// 	case 4: color = 0xFFFFFF; break;
		// 	default: color = 0xFFFA6D; break;
		// }

		// if (wall == 'y')
		// 	color = color / 2;

		// //draw line
		// verLine(all, x, draw_start, draw_end, color);
		int tex_num = Map[(int)map.x][(int)map.y] - 1;
		double wall_x;

		if (wall == 'x') {
			wall_x = all->pos.y + perp_wall_dist * all->ray.y;
		} else {
			wall_x = all->pos.x + perp_wall_dist * all->ray.x;
		}
		wall_x -= floor(wall_x);

		int tex_x = (int)(wall_x * texWidth);
		if (wall == 'x' && all->ray.x > 0) tex_x = texWidth - tex_x - 1;
		if (wall == 'y' && all->ray.y < 0) tex_x = texWidth - tex_x - 1;

		double h_ratio = 1.0 * texHeight / vertical;
		// Starting texture coordinate
		double texPos = (draw_start - WINH / 2 + vertical / 2) * h_ratio;
		for (int y = draw_start; y < draw_end; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (texHeight - 1);
			texPos += h_ratio;
			int color = all->texture[tex_num][texHeight * texY + tex_x];
			// make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if (wall == 'y')
				color = (color >> 1) & 8355711;
			all->buf[y][x] = color;
		}
		x++;
	}
	//draw line
}

int main_loop(t_all *all) {
	ray_casting(all);
	draw(all);
	return 0;
}

int	key_press(int key, t_all *all)
{
	if (key == W)
	{
		if (!Map[(int)(all->pos.x + all->dir.x * all->moveSpeed)][(int)(all->pos.y)])
			all->pos.x += all->dir.x * all->moveSpeed;
		if (!Map[(int)(all->pos.x)][(int)(all->pos.y + all->dir.y * all->moveSpeed)])
			all->pos.y += all->dir.y * all->moveSpeed;
	}
	//move backwards if no wall behind you
	if (key == S)
	{
		if (!Map[(int)(all->pos.x - all->dir.x * all->moveSpeed)][(int)(all->pos.y)])
			all->pos.x -= all->dir.x * all->moveSpeed;
		if (!Map[(int)(all->pos.x)][(int)(all->pos.y - all->dir.y * all->moveSpeed)])
			all->pos.y -= all->dir.y * all->moveSpeed;
	}
	//rotate to the right
	if (key == D)
	{
		//both camera direction and camera plane must be rotated
		double old_dir_x = all->dir.x;
		all->dir.x = all->dir.x * cos(-all->rotSpeed) - all->dir.y * sin(-all->rotSpeed);
		all->dir.y = old_dir_x * sin(-all->rotSpeed) + all->dir.y * cos(-all->rotSpeed);
		double oldPlaneX = all->plane.x;
		all->plane.x = all->plane.x * cos(-all->rotSpeed) - all->plane.y * sin(-all->rotSpeed);
		all->plane.y = oldPlaneX * sin(-all->rotSpeed) + all->plane.y * cos(-all->rotSpeed);
	}
	//rotate to the left
	if (key == A)
	{
		//both camera direction and camera plane must be rotated
		double old_dir_x = all->dir.x;
		all->dir.x = all->dir.x * cos(all->rotSpeed) - all->dir.y * sin(all->rotSpeed);
		all->dir.y = old_dir_x * sin(all->rotSpeed) + all->dir.y * cos(all->rotSpeed);
		double oldPlaneX = all->plane.x;
		all->plane.x = all->plane.x * cos(all->rotSpeed) - all->plane.y * sin(all->rotSpeed);
		all->plane.y = oldPlaneX * sin(all->rotSpeed) + all->plane.y * cos(all->rotSpeed);
	}
	if (key == ESC)
		exit(0);
	return (0);
}

void load_image(t_all *all, int *texture, char *path, t_img *img) {
			write(1, "2\n", 2);
	img->img = mlx_xpm_file_to_image(all->mlx, path, &img->img_width, &img->img_height);
	write(1, "3\n", 2);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);

	
			write(1, "1\n", 2);
	for (int y = 0; y < img->img_height; y++) {
		for (int x = 0; x < img->img_width; x++) {
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
		}
	}
	mlx_destroy_image(all->mlx, img->img);
}

void load_texture(t_all *all) {
	t_img img;
	write(1, "complete\n", 9);

	load_image(all, all->texture[0], "textures/barrel.xpm", &img);
	write(1, "complete\n", 9);
	load_image(all, all->texture[1], "textures/bluestone.xpm", &img);
	write(1, "complete\n", 9);
	load_image(all, all->texture[2], "textures/colorstone.xpm", &img);
	write(1, "complete\n", 9);
	load_image(all, all->texture[3], "textures/eagle.xpm", &img);
	write(1, "complete\n", 9);
	load_image(all, all->texture[4], "textures/greenlight.xpm", &img);
	write(1, "complete\n", 9);
	load_image(all, all->texture[5], "textures/mossy.xpm", &img);
	write(1, "complete\n", 9);
	load_image(all, all->texture[6], "textures/wood.xpm", &img);
	write(1, "complete\n", 9);
	load_image(all, all->texture[7], "textures/redbrick.xpm", &img);
	write(1, "complete\n", 9);
}

void init(t_all *all) {
	all->pos.x = 22;
	all->pos.y = 11.5;
	all->dir.x = -1.0;
	all->dir.y = 0;
	all->plane.x = 0;
	all->plane.y = 0.66;
	all->moveSpeed = 0.05;
	all->rotSpeed = 0.05;

	all->buf = (int **)malloc(sizeof(int *) * WINH);

	for (int i = 0; i < WINH; i++)
	{
		all->buf[i] = (int *)malloc(sizeof(int) * WINW);
	}

	for (int i = 0; i < WINH; i++)
	{
		for (int j = 0; j < WINW; j++)
		{
			all->buf[i][j] = 0;
		}
	}

	if (!(all->texture = (int **)malloc(sizeof(int *) * 8)))
		exit(0);
	for (int i = 0; i < 8; i++)
	{
		if (!(all->texture[i] = (int *)malloc(sizeof(int) * (texHeight * texWidth))))
			exit(0);
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < texHeight * texWidth; j++)
		{
			all->texture[i][j] = 0;
		}
	}

	// for (int x = 0; x < texWidth; x++)
	// {
	// 	for (int y = 0; y < texHeight; y++)
	// 	{
	// 		int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
	// 		int ycolor = y * 256 / texHeight;
	// 		int xycolor = y * 128 / texHeight + x * 128 / texWidth;
	// 		all->texture[0][texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y); //flat red texture with black cross
	// 		all->texture[1][texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
	// 		all->texture[2][texWidth * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
	// 		all->texture[3][texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
	// 		all->texture[4][texWidth * y + x] = 256 * xorcolor; //xor green
	// 		all->texture[5][texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
	// 		all->texture[6][texWidth * y + x] = 65536 * ycolor; //red gradient
	// 		all->texture[7][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
	// 	}
	// }
	load_texture(all);
}

int main() {
	t_all all;

	init(&all);
	all.mlx = mlx_init();
	all.win = mlx_new_window(all.mlx, WINW, WINH, "test");
	all.img.img = mlx_new_image(all.mlx, WINW, WINH);
	all.img.data = (int *)mlx_get_data_addr(all.img.img, &all.img.bpp, &all.img.size_l, &all.img.endian);
	mlx_loop_hook(all.mlx, &main_loop, &all);
	mlx_hook(all.win, 2, 0, &key_press, &all);
	mlx_loop(all.mlx);
}

// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   02_textured_raycast.c                              :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: yohlee <yohlee@student.42seoul.kr>         +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2020/06/26 15:18:03 by yohlee            #+#    #+#             */
// /*   Updated: 2020/07/21 08:09:54 by yohlee           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include <mlx.h>
// #include <math.h>
// #include <string.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #define X_EVENT_KEY_PRESS	2
// #define X_EVENT_KEY_EXIT	17
// #define texWidth 64
// #define texHeight 64
// #define mapWidth 24
// #define mapHeight 24
// #define width 640
// #define height 480
// #define K_W 13
// #define K_A 0
// #define K_S 1
// #define K_D 2
// #define K_ESC 53
// typedef struct	s_img
// {
// 	void	*img;
// 	int		*data;

// 	int		size_l;
// 	int		bpp;
// 	int		endian;
// 	int		img_width;
// 	int		img_height;
// }				t_img;

// typedef struct	s_info
// {
// 	double posX;
// 	double posY;
// 	double dirX;
// 	double dirY;
// 	double planeX;
// 	double planeY;
// 	void	*mlx;
// 	void	*win;
// 	t_img	img;
// 	int		buf[height][width];
// 	int		**texture;
// 	double	moveSpeed;
// 	double	rotSpeed;
// }				t_info;

// int	worldMap[mapWidth][mapHeight] =
// 						{
// 							{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
// 							{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
// 							{4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
// 							{4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
// 							{4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
// 							{4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
// 							{4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
// 							{4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
// 							{4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
// 							{4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
// 							{4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
// 							{4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
// 							{6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
// 							{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
// 							{6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
// 							{4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
// 							{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
// 							{4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
// 							{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
// 							{4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
// 							{4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
// 							{4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
// 							{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
// 							{4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
// 						};

// void	draw(t_info *info)
// {
// 	for (int y = 0; y < height; y++)
// 	{
// 		for (int x = 0; x < width; x++)
// 		{
// 			info->img.data[y * width + x] = info->buf[y][x];
// 		}
// 	}
// 	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
// }

// void	calc(t_info *info)
// {
// 	int	x;

// 	x = 0;
// 	while (x < width)
// 	{
// 		double cameraX = 2 * x / (double)width - 1;
// 		double rayDirX = info->dirX + info->planeX * cameraX;
// 		double rayDirY = info->dirY + info->planeY * cameraX;
		
// 		int mapX = (int)info->posX;
// 		int mapY = (int)info->posY;

// 		//length of ray from current position to next x or y-side
// 		double sideDistX;
// 		double sideDistY;
		
// 		 //length of ray from one x or y-side to next x or y-side
// 		double deltaDistX = fabs(1 / rayDirX);
// 		double deltaDistY = fabs(1 / rayDirY);
// 		double perpWallDist;
		
// 		//what direction to step in x or y-direction (either +1 or -1)
// 		int stepX;
// 		int stepY;
		
// 		int hit = 0; //was there a wall hit?
// 		int side; //was a NS or a EW wall hit?

// 		if (rayDirX < 0)
// 		{
// 			stepX = -1;
// 			sideDistX = (info->posX - mapX) * deltaDistX;
// 		}
// 		else
// 		{
// 			stepX = 1;
// 			sideDistX = (mapX + 1.0 - info->posX) * deltaDistX;
// 		}
// 		if (rayDirY < 0)
// 		{
// 			stepY = -1;
// 			sideDistY = (info->posY - mapY) * deltaDistY;
// 		}
// 		else
// 		{
// 			stepY = 1;
// 			sideDistY = (mapY + 1.0 - info->posY) * deltaDistY;
// 		}

// 		while (hit == 0)
// 		{
// 			//jump to next map square, OR in x-direction, OR in y-direction
// 			if (sideDistX < sideDistY)
// 			{
// 				sideDistX += deltaDistX;
// 				mapX += stepX;
// 				side = 0;
// 			}
// 			else
// 			{
// 				sideDistY += deltaDistY;
// 				mapY += stepY;
// 				side = 1;
// 			}
// 			//Check if ray has hit a wall
// 			if (worldMap[mapX][mapY] > 0) hit = 1;
// 		}
// 		if (side == 0)
// 			perpWallDist = (mapX - info->posX + (1 - stepX) / 2) / rayDirX;
// 		else
// 			perpWallDist = (mapY - info->posY + (1 - stepY) / 2) / rayDirY;

// 		//Calculate height of line to draw on screen
// 		int lineHeight = (int)(height / perpWallDist);

// 		//calculate lowest and highest pixel to fill in current stripe
// 		int drawStart = -lineHeight / 2 + height / 2;
// 		if(drawStart < 0)
// 			drawStart = 0;
// 		int drawEnd = lineHeight / 2 + height / 2;
// 		if(drawEnd >= height)
// 			drawEnd = height - 1;

// 		// texturing calculations
// 		int texNum = worldMap[mapX][mapY];

// 		// calculate value of wallX
// 		double wallX;
// 		if (side == 0)
// 			wallX = info->posY + perpWallDist * rayDirY;
// 		else
// 			wallX = info->posX + perpWallDist * rayDirX;
// 		wallX -= floor(wallX);

// 		// x coordinate on the texture
// 		int texX = (int)(wallX * (double)texWidth);
// 		if (side == 0 && rayDirX > 0)
// 			texX = texWidth - texX - 1;
// 		if (side == 1 && rayDirY < 0)
// 			texX = texWidth - texX - 1;

// 		// How much to increase the texture coordinate perscreen pixel
// 		double step = 1.0 * texHeight / lineHeight;
// 		// Starting texture coordinate
// 		double texPos = (drawStart - height / 2 + lineHeight / 2) * step;
// 		for (int y = drawStart; y < drawEnd; y++)
// 		{
// 			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
// 			int texY = (int)texPos & (texHeight - 1);
// 			texPos += step;
// 			int color = info->texture[texNum][texHeight * texY + texX];
// 			// make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
// 			if (side == 1)
// 				color = (color >> 1) & 8355711;
// 			info->buf[y][x] = color;
// 		}
// 		x++;
// 	}
// }

// int	main_loop(t_info *info)
// {
// 	calc(info);
// 	draw(info);
// 	return (0);
// }

// int	key_press(int key, t_info *info)
// {
// 	if (key == K_W)
// 	{
// 		if (!worldMap[(int)(info->posX + info->dirX * info->moveSpeed)][(int)(info->posY)])
// 			info->posX += info->dirX * info->moveSpeed;
// 		if (!worldMap[(int)(info->posX)][(int)(info->posY + info->dirY * info->moveSpeed)])
// 			info->posY += info->dirY * info->moveSpeed;
// 	}
// 	//move backwards if no wall behind you
// 	if (key == K_S)
// 	{
// 		if (!worldMap[(int)(info->posX - info->dirX * info->moveSpeed)][(int)(info->posY)])
// 			info->posX -= info->dirX * info->moveSpeed;
// 		if (!worldMap[(int)(info->posX)][(int)(info->posY - info->dirY * info->moveSpeed)])
// 			info->posY -= info->dirY * info->moveSpeed;
// 	}
// 	//rotate to the right
// 	if (key == K_D)
// 	{
// 		//both camera direction and camera plane must be rotated
// 		double oldDirX = info->dirX;
// 		info->dirX = info->dirX * cos(-info->rotSpeed) - info->dirY * sin(-info->rotSpeed);
// 		info->dirY = oldDirX * sin(-info->rotSpeed) + info->dirY * cos(-info->rotSpeed);
// 		double oldPlaneX = info->planeX;
// 		info->planeX = info->planeX * cos(-info->rotSpeed) - info->planeY * sin(-info->rotSpeed);
// 		info->planeY = oldPlaneX * sin(-info->rotSpeed) + info->planeY * cos(-info->rotSpeed);
// 	}
// 	//rotate to the left
// 	if (key == K_A)
// 	{
// 		//both camera direction and camera plane must be rotated
// 		double oldDirX = info->dirX;
// 		info->dirX = info->dirX * cos(info->rotSpeed) - info->dirY * sin(info->rotSpeed);
// 		info->dirY = oldDirX * sin(info->rotSpeed) + info->dirY * cos(info->rotSpeed);
// 		double oldPlaneX = info->planeX;
// 		info->planeX = info->planeX * cos(info->rotSpeed) - info->planeY * sin(info->rotSpeed);
// 		info->planeY = oldPlaneX * sin(info->rotSpeed) + info->planeY * cos(info->rotSpeed);
// 	}
// 	if (key == K_ESC)
// 		exit(0);
// 	return (0);
// }

// void	load_image(t_info *info, int *texture, char *path, t_img *img)
// {
// 	img->img = mlx_xpm_file_to_image(info->mlx, path, &img->img_width, &img->img_height);
// 	write(1, "1\n", 2);
// 	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
// 	write(1, "2\n", 2);

// 	for (int y = 0; y < img->img_height; y++)
// 	{
// 		for (int x = 0; x < img->img_width; x++)
// 		{
// 			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
// 		}
// 	}
// 	mlx_destroy_image(info->mlx, img->img);
// }

// void	load_texture(t_info *info)
// {
// 	t_img	img;

// 	load_image(info, info->texture[0], "textures/eagle.xpm", &img);
// 	load_image(info, info->texture[1], "textures/redbrick.xpm", &img);
// 	load_image(info, info->texture[2], "textures/purplestone.xpm", &img);
// 	load_image(info, info->texture[3], "textures/greystone.xpm", &img);
// 	load_image(info, info->texture[4], "textures/bluestone.xpm", &img);
// 	load_image(info, info->texture[5], "textures/mossy.xpm", &img);
// 	load_image(info, info->texture[6], "textures/wood.xpm", &img);
// 	load_image(info, info->texture[7], "textures/colorstone.xpm", &img);
// }

// int	main(void)
// {
// 	t_info info;
// 	info.mlx = mlx_init();

// 	info.posX = 22.0;
// 	info.posY = 11.5;
// 	info.dirX = -1.0;
// 	info.dirY = 0.0;
// 	info.planeX = 0.0;
// 	info.planeY = 0.66;

// 	for (int i = 0; i < height; i++)
// 	{
// 		for (int j = 0; j < width; j++)
// 		{
// 			info.buf[i][j] = 0;
// 		}
// 	}

// 	if (!(info.texture = (int **)malloc(sizeof(int *) * 8)))
// 		return (-1);
// 	for (int i = 0; i < 8; i++)
// 	{
// 		if (!(info.texture[i] = (int *)malloc(sizeof(int) * (texHeight * texWidth))))
// 			return (-1);
// 	}
// 	for (int i = 0; i < 8; i++)
// 	{
// 		for (int j = 0; j < texHeight * texWidth; j++)
// 		{
// 			info.texture[i][j] = 0;
// 		}
// 	}

// 	load_texture(&info);

// 	info.moveSpeed = 0.05;
// 	info.rotSpeed = 0.05;
	
// 	info.win = mlx_new_window(info.mlx, width, height, "mlx");

// 	info.img.img = mlx_new_image(info.mlx, width, height);
// 	info.img.data = (int *)mlx_get_data_addr(info.img.img, &info.img.bpp, &info.img.size_l, &info.img.endian);

// 	mlx_loop_hook(info.mlx, &main_loop, &info);
// 	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);

// 	mlx_loop(info.mlx);
// }