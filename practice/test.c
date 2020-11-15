// #include <stdio.h>
// #include <math.h>
// #include <mlx.h>
// #include <stdlib.h>
// #include <unistd.h>

// #define mapWidth 24
// #define mapHeight 24
// #define height 480
// #define width 640
// #define texWidth 64
// #define texHeight 64

// #define W 13
// #define A 0
// #define S 1
// #define D 2
// #define ESC 53
// #define UPPER 126
// #define DOWN 125
// #define LEFT_ARROW 123
// #define RIGHT_ARROW 124

// int	Map[mapWidth][mapHeight] =
// 						{
// 							{8,8,8,8,8,8,8,8,8,8,8,4,4,6,4,4,6,4,6,4,4,4,6,4},
// 										{8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
// 										{8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,6},
// 										{8,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
// 										{8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
// 										{8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,6,6,6,0,6,4,6},
// 										{8,8,8,8,0,8,8,8,8,8,8,4,4,4,4,4,4,6,0,0,0,0,0,6},
// 										{7,7,7,7,0,7,7,7,7,0,8,0,8,0,8,0,8,4,0,4,0,6,0,6},
// 										{7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,0,0,0,0,0,6},
// 										{7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,0,0,0,0,4},
// 										{7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,6,0,6,0,6},
// 										{7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,4,6,0,6,6,6},
// 										{7,7,7,7,0,7,7,7,7,8,8,4,0,6,8,4,8,3,3,3,0,3,3,3},
// 										{2,2,2,2,0,2,2,2,2,4,6,4,0,0,6,0,6,3,0,0,0,0,0,3},
// 										{2,2,0,0,0,0,0,2,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
// 										{2,0,0,0,0,0,0,0,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
// 										{1,0,0,0,0,0,0,0,1,4,4,4,4,4,6,0,6,3,3,0,0,0,3,3},
// 										{2,0,0,0,0,0,0,0,2,2,2,1,2,2,2,6,6,0,0,5,0,5,0,5},
// 										{2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
// 										{2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
// 										{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
// 										{2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
// 										{2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
// 										{2,2,2,2,1,2,2,2,2,2,2,1,2,2,2,5,5,5,5,5,5,5,5,5}
// 						};

// typedef struct pos {
// 	double x;
// 	double y;
// } t_pos;

// typedef struct dir {
// 	double x;
// 	double y;
// } t_dir;

// typedef struct dist {
// 	double x;
// 	double y;
// } t_dist;

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

// typedef struct all {
// 	void	*mlx;
// 	void	*win;
// 	t_pos pos;
// 	t_dir dir;
// 	t_dir ray;
// 	t_dir plane;
// 	double camera;
// 	double moveSpeed;
// 	double rotSpeed;
// 	int		**buf;
// 	int		**texture;
// 	t_img img;
// } t_all;

// t_pos get_step(t_dist *side, t_dist delta, t_all *all, t_pos map) {
// 	t_pos step;

// 	if (all->ray.x < 0) {
// 		step.x = -1;
// 		side->x = (all->pos.x - map.x) * delta.x;
// 	} else {
// 		step.x = 1;
// 		side->x = (map.x + 1.0 - all->pos.x) * delta.x;
// 	}
// 	if (all->ray.y < 0) {
// 		step.y = -1;
// 		side->y = (all->pos.y - map.y) * delta.y;
// 	} else {
// 		step.y = 1;
// 		side->y = (map.y + 1.0 - all->pos.y) * delta.y;
// 	}
// 	return step;
// }

// void	verLine(t_all *all, int x, int y1, int y2, int color)
// {
// 	int	y;

// 	y = y1;
// 	while (y <= y2)
// 	{
// 		mlx_pixel_put(all->mlx, all->win, x, y, color);
// 		y++;
// 	}
// }

// void	draw(t_all *all)
// {
// 	for (int y = 0; y < height; y++)
// 	{
// 		for (int x = 0; x < width; x++)
// 		{
// 			all->img.data[y * width + x] = all->buf[y][x];
// 		}
// 	}
// 	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
// }

// void ray_casting(t_all *all) {
// // 	for(int y = 0; y < height; y++)
// // 	{
// // 		// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
// // 		float rayDirX0 = all->dir.x - all->plane.x;
// // 		float rayDirY0 = all->dir.y - all->plane.y;
// // 		float rayDirX1 = all->dir.x + all->plane.x;
// // 		float rayDirY1 = all->dir.y + all->plane.y;

// // 		// Current y position compared to the center of the screen (the horizon)
// // 		int p = y - height / 2;

// // 		// Vertical position of the camera.
// // 		float posZ = 0.5 * height;

// // 		// Horizontal distance from the camera to the floor for the current row.
// // 		// 0.5 is the z position exactly in the middle between floor and ceiling.
// // 		float rowDistance = posZ / p;

// // 		// calculate the real world step vector we have to add for each x (parallel to camera plane)
// // 		// adding step by step avoids multiplications with a weight in the inner loop
// // 		float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / WINW;
// // 		float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / WINW;

// // 		// real world coordinates of the leftmost column. This will be updated as we step to the right.
// // 		float floorX = all->pos.x + rowDistance * rayDirX0;
// // 		float floorY = all->pos.y + rowDistance * rayDirY0;
	
// // 		for(int x = 0; x < WINW; ++x)
// // 		{
// // 			// the cell coord is simply got from the integer parts of floorX and floorY
// // 			int cellX = (int)(floorX);
// // 			int cellY = (int)(floorY);

// // 			// get the texture coordinate from the fractional part
// // 			int tx = (int)(texWidth * (floorX - cellX)) & (texWidth - 1);
// // 			int ty = (int)(texHeight * (floorY - cellY)) & (texHeight - 1);

// // 			floorX += floorStepX;
// // 			floorY += floorStepY;

// // 			// choose texture and draw the pixel
// // 			int floorTexture = 3;
// // 			int ceilingTexture = 6;

// // 			int color;

// // 			// floor
// // 			color = all->texture[floorTexture][texWidth * ty + tx];
// // 			color = (color >> 1) & 8355711; // make a bit darker

// // 			all->buf[y][x] = color;

// // 			//ceiling (symmetrical, at screenHeight - y - 1 instead of y)
// // 			color = all->texture[ceilingTexture][texWidth * ty + tx];
// // 			color = (color >> 1) & 8355711; // make a bit darker

// // 			all->buf[height - y - 1][x] = color;
// // 		}
// // 	}
	
// 	for(int x = 0; x < width; x++)
// 	{
// 		double cameraX = 2 * x / (double)width - 1;
// 		double rayDirX = all->dir.x + all->plane.x * cameraX;
// 		double rayDirY = all->dir.y + all->plane.y * cameraX;
		
// 		int mapX = (int)all->pos.x;
// 		int mapY = (int)all->pos.y;

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
// 			sideDistX = (all->pos.x - mapX) * deltaDistX;
// 		}
// 		else
// 		{
// 			stepX = 1;
// 			sideDistX = (mapX + 1.0 - all->pos.x) * deltaDistX;
// 		}
// 		if (rayDirY < 0)
// 		{
// 			stepY = -1;
// 			sideDistY = (all->pos.y - mapY) * deltaDistY;
// 		}
// 		else
// 		{
// 			stepY = 1;
// 			sideDistY = (mapY + 1.0 - all->pos.y) * deltaDistY;
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
// 			if (Map[mapX][mapY] > 0) hit = 1;
// 		}
// 		if (side == 0)
// 			perpWallDist = (mapX - all->pos.x + (1 - stepX) / 2) / rayDirX;
// 		else
// 			perpWallDist = (mapY - all->pos.y + (1 - stepY) / 2) / rayDirY;

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
// 		int texNum = Map[mapX][mapY];

// 		// calculate value of wallX
// 		double wallX;
// 		if (side == 0)
// 			wallX = all->pos.y + perpWallDist * rayDirY;
// 		else
// 			wallX = all->pos.x + perpWallDist * rayDirX;
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

// 			int color = all->texture[texNum][texHeight * texY + texX];

// 			// make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
// 			if (side == 1)
// 				color = (color >> 1) & 8355711;

// 			all->buf[y][x] = color;
// 		}

// 		//FLOOR CASTING (vertical version, directly after drawing the vertical wall stripe for the current x)
// 		double floorXWall, floorYWall; //x, y position of the floor texel at the bottom of the wall

// 		//4 different wall directions possible
// 		if(side == 0 && rayDirX > 0)
// 		{
// 			floorXWall = mapX;
// 			floorYWall = mapY + wallX;
// 		}
// 		else if(side == 0 && rayDirX < 0)
// 		{
// 			floorXWall = mapX + 1.0;
// 			floorYWall = mapY + wallX;
// 		}
// 		else if(side == 1 && rayDirY > 0)
// 		{
// 			floorXWall = mapX + wallX;
// 			floorYWall = mapY;
// 		}
// 		else
// 		{
// 			floorXWall = mapX + wallX;
// 			floorYWall = mapY + 1.0;
// 		}

// 		double distWall, distPlayer, currentDist;

// 		distWall = perpWallDist;
// 		distPlayer = 0.0;

// 		if (drawEnd < 0) drawEnd = height; //becomes < 0 when the integer overflows

// 		//draw the floor from drawEnd to the bottom of the screen
// 		for(int y = drawEnd + 1; y < height; y++)
// 		{
// 			currentDist = height / (2.0 * y - height); //you could make a small lookup table for this instead

// 			double weight = (currentDist - distPlayer) / (distWall - distPlayer);

// 			double currentFloorX = weight * floorXWall + (1.0 - weight) * all->pos.x;
// 			double currentFloorY = weight * floorYWall + (1.0 - weight) * all->pos.y;

// 			int floorTexX, floorTexY;
// 			floorTexX = (int)(currentFloorX * texWidth) % texWidth;
// 			floorTexY = (int)(currentFloorY * texHeight) % texHeight;

// 			int checkerBoardPattern = ((int)(currentFloorX) + (int)(currentFloorY)) % 2;
// 			int floorTexture;
// 			if(checkerBoardPattern == 0) floorTexture = 3;
// 			else floorTexture = 4;

// 			//floor
// 			all->buf[y][x] = (all->texture[floorTexture][texWidth * floorTexY + floorTexX] >> 1) & 8355711;
// 			//ceiling (symmetrical!)
// 			all->buf[height - y][x] = all->texture[6][texWidth * floorTexY + floorTexX];
// 		}
// 	}
// }

// int main_loop(t_all *all) {
// 	ray_casting(all);
// 	draw(all);
// 	return 0;
// }

// int	key_press(int key, t_all *all)
// {
// 	if (key == W)
// 	{
// 		if (!Map[(int)(all->pos.x + all->dir.x * all->moveSpeed)][(int)(all->pos.y)])
// 			all->pos.x += all->dir.x * all->moveSpeed;
// 		if (!Map[(int)(all->pos.x)][(int)(all->pos.y + all->dir.y * all->moveSpeed)])
// 			all->pos.y += all->dir.y * all->moveSpeed;
// 	}
// 	//move backwards if no wall behind you
// 	if (key == S)
// 	{
// 		if (!Map[(int)(all->pos.x - all->dir.x * all->moveSpeed)][(int)(all->pos.y)])
// 			all->pos.x -= all->dir.x * all->moveSpeed;
// 		if (!Map[(int)(all->pos.x)][(int)(all->pos.y - all->dir.y * all->moveSpeed)])
// 			all->pos.y -= all->dir.y * all->moveSpeed;
// 	}
// 	//rotate to the right
// 	if (key == D)
// 	{
// 		//both camera direction and camera plane must be rotated
// 		double old_dir_x = all->dir.x;
// 		all->dir.x = all->dir.x * cos(-all->rotSpeed) - all->dir.y * sin(-all->rotSpeed);
// 		all->dir.y = old_dir_x * sin(-all->rotSpeed) + all->dir.y * cos(-all->rotSpeed);
// 		double oldPlaneX = all->plane.x;
// 		all->plane.x = all->plane.x * cos(-all->rotSpeed) - all->plane.y * sin(-all->rotSpeed);
// 		all->plane.y = oldPlaneX * sin(-all->rotSpeed) + all->plane.y * cos(-all->rotSpeed);
// 	}
// 	//rotate to the left
// 	if (key == A)
// 	{
// 		//both camera direction and camera plane must be rotated
// 		double old_dir_x = all->dir.x;
// 		all->dir.x = all->dir.x * cos(all->rotSpeed) - all->dir.y * sin(all->rotSpeed);
// 		all->dir.y = old_dir_x * sin(all->rotSpeed) + all->dir.y * cos(all->rotSpeed);
// 		double oldPlaneX = all->plane.x;
// 		all->plane.x = all->plane.x * cos(all->rotSpeed) - all->plane.y * sin(all->rotSpeed);
// 		all->plane.y = oldPlaneX * sin(all->rotSpeed) + all->plane.y * cos(all->rotSpeed);
// 	}
// 	if (key == ESC)
// 		exit(0);
// 	return (0);
// }

// void	load_image(t_all *all, int *texture, char *path, t_img *img)
// {
// 	img->img = mlx_xpm_file_to_image(all->mlx, path, &img->img_width, &img->img_height);
// 	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
// 	for (int y = 0; y < img->img_height; y++)
// 	{
// 		for (int x = 0; x < img->img_width; x++)
// 		{
// 			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
// 		}
// 	}
// 	mlx_destroy_image(all->mlx, img->img);
// }

// void	load_texture(t_all *all)
// {
// 	t_img	img;

// 	load_image(all, all->texture[0], "textures/eagle.xpm", &img);
// 	load_image(all, all->texture[1], "textures/redbrick.xpm", &img);
// 	load_image(all, all->texture[2], "textures/purplestone.xpm", &img);
// 	load_image(all, all->texture[3], "textures/greystone.xpm", &img);
// 	load_image(all, all->texture[4], "textures/bluestone.xpm", &img);
// 	load_image(all, all->texture[5], "textures/mossy.xpm", &img);
// 	load_image(all, all->texture[6], "textures/wood.xpm", &img);
// 	load_image(all, all->texture[7], "textures/colorstone.xpm", &img);
// }

// void init(t_all *all) {
// 	all->pos.x = 22;
// 	all->pos.y = 11.5;
// 	all->dir.x = -1.0;
// 	all->dir.y = 0;
// 	all->plane.x = 0;
// 	all->plane.y = 0.66;
// 	all->moveSpeed = 0.05;
// 	all->rotSpeed = 0.05;

// 	all->buf = (int **)malloc(sizeof(int *) * height);

// 	for (int i = 0; i < height; i++)
// 	{
// 		all->buf[i] = (int *)malloc(sizeof(int) * WINW);
// 	}

// 	for (int i = 0; i < height; i++)
// 	{
// 		for (int j = 0; j < WINW; j++)
// 		{
// 			all->buf[i][j] = 0;
// 		}
// 	}

// 	if (!(all->texture = (int **)malloc(sizeof(int *) * 8)))
// 		exit(0);
// 	for (int i = 0; i < 8; i++)
// 	{
// 		if (!(all->texture[i] = (int *)malloc(sizeof(int) * (texHeight * texWidth))))
// 			exit(0);
// 	}
// 	for (int i = 0; i < 8; i++)
// 	{
// 		for (int j = 0; j < texHeight * texWidth; j++)
// 		{
// 			all->texture[i][j] = 0;
// 		}
// 	}

// 	for (int x = 0; x < texWidth; x++)
// 	{
// 		for (int y = 0; y < texHeight; y++)
// 		{
// 			int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
// 			int ycolor = y * 256 / texHeight;
// 			int xycolor = y * 128 / texHeight + x * 128 / texWidth;
// 			all->texture[0][texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y); //flat red texture with black cross
// 			all->texture[1][texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
// 			all->texture[2][texWidth * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
// 			all->texture[3][texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
// 			all->texture[4][texWidth * y + x] = 256 * xorcolor; //xor green
// 			all->texture[5][texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
// 			all->texture[6][texWidth * y + x] = 65536 * ycolor; //red gradient
// 			all->texture[7][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
// 		}
// 	}
// 	load_texture(all);
// }

// int main() {
// 	t_all all;
// 	//t_img img2;
// 	all.mlx = mlx_init();
// 	init(&all);
// 	all.win = mlx_new_window(all.mlx, width, height, "test");
// 	all.img.img = mlx_new_image(all.mlx, width, height);
// 	//img2.img = mlx_xpm_file_to_image(all.mlx, "../textures/barrel.xpm", &img2.img_width, &img2.img_height);
// 	///printf("%p\n", img2.img);
// 	all.img.data = (int *)mlx_get_data_addr(all.img.img, &all.img.bpp, &all.img.size_l, &all.img.endian);
// 	mlx_loop_hook(all.mlx, &main_loop, &all);
// 	mlx_hook(all.win, 2, 0, &key_press, &all);
// 	mlx_loop(all.mlx);
// }
  
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_floor_ceiling_macos.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohlee <yohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 19:53:20 by yohlee            #+#    #+#             */
/*   Updated: 2020/07/21 08:11:30 by yohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define K_W 13
#define K_A 0
#define K_S 1
#define K_D 2
#define K_ESC 53
#define X_EVENT_KEY_PRESS	2
# define X_EVENT_KEY_RELEASE	3
#define X_EVENT_KEY_EXIT	17
#define texWidth 64
#define texHeight 64
#define mapWidth 24
#define mapHeight 24
#define width 640
#define height 480
#define numSprites 19

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

struct	Sprite
{
	double		x;
	double		y;
	int			texture;
};

struct Sprite	sprite[numSprites] =
{
	{20.5, 11.5, 10}, //green light in front of playerstart
	//green lights in every room
	// {18.5,4.5, 10},
	// {10.0,4.5, 10},
	// {10.0,12.5,10},
	// {3.5, 6.5, 10},
	// {3.5, 20.5,10},
	// {3.5, 14.5,10},
	// {14.5,20.5,10},
{20.5, 11.5, 10},
{20.5, 11.5, 10},
{20.5, 11.5, 10},
{20.5, 11.5, 10},
{20.5, 11.5, 10},
{20.5, 11.5, 10},
{20.5, 11.5, 10},
	// //row of pillars in front of wall: fisheye test
	// {18.5, 10.5, 9},
	// {18.5, 11.5, 9},
	// {18.5, 12.5, 9},
{20.5, 11.5, 10},
{20.5, 11.5, 10},
{20.5, 11.5, 10},
	// //some barrels around the map
	// {21.5, 1.5, 8},
	// {15.5, 1.5, 8},
	// {16.0, 1.8, 8},
	// {16.2, 1.2, 8},
	// {3.5,  2.5, 8},
	// {9.5, 15.5, 8},
	// {10.0, 15.1,8},
	// {10.5, 15.8,8},
	{20.5, 11.5, 10},
	{20.5, 11.5, 10},
	{20.5, 11.5, 10},
	{20.5, 11.5, 10},
	{20.5, 11.5, 10},
	{20.5, 11.5, 10},
	{20.5, 11.5, 10},
	{20.5, 11.5, 10},
};

int		spriteOrder[numSprites];
double	spriteDistance[numSprites];

typedef struct	s_info
{
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	void	*mlx;
	void	*win;
	int		key_a;
	int		key_w;
	int		key_s;
	int		key_d;
	int		key_esc;
	t_img	img;
	int		buf[height][width];
	double	zBuffer[width];
	int		**texture;
	double	moveSpeed;
	double	rotSpeed;
}				t_info;

typedef struct		s_pair
{
	double	first;
	int		second;
}					t_pair;

void	key_update(t_info *info);

static int	compare(const void *first, const void *second)
{
	if (*(int *)first > *(int *)second)
		return (1);
	else if (*(int *)first < *(int *)second)
		return (-1);
	else
		return (0);
}

void	sort_order(t_pair *orders, int amount)
{
	t_pair	tmp;

	for (int i = 0; i < amount; i++)
	{
		for (int j = 0; j < amount - 1; j++)
		{
			if (orders[j].first > orders[j + 1].first)
			{
				tmp.first = orders[j].first;
				tmp.second = orders[j].second;
				orders[j].first = orders[j + 1].first;
				orders[j].second = orders[j + 1].second;
				orders[j + 1].first = tmp.first;
				orders[j + 1].second = tmp.second;
			}
		}
	}
}

void	sortSprites(int *order, double *dist, int amount)
{
	t_pair	*sprites;

	//std::vector<std::pair<double, int>> sprites(amount);
	sprites = (t_pair*)malloc(sizeof(t_pair) * amount);
	for (int i = 0; i < amount; i++)
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
	}
	sort_order(sprites, amount);
	//std::sort(sprites.begin(), sprites.end());
	for (int i = 0; i < amount; i++)
	{
		dist[i] = sprites[amount - i - 1].first;
		order[i] = sprites[amount - i - 1].second;
	}
	free(sprites);
}

int	worldMap[mapWidth][mapHeight] =
									{
										{8,8,8,8,8,8,8,8,8,8,8,4,4,6,4,4,6,4,6,4,4,4,6,4},
										{8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
										{8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,6},
										{8,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
										{8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
										{8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,6,6,6,0,6,4,6},
										{8,8,8,8,0,8,8,8,8,8,8,4,4,4,4,4,4,6,0,0,0,0,0,6},
										{7,7,7,7,0,7,7,7,7,0,8,0,8,0,8,0,8,4,0,4,0,6,0,6},
										{7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,0,0,0,0,0,6},
										{7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,0,0,0,0,4},
										{7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,6,0,6,0,6},
										{7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,4,6,0,6,6,6},
										{7,7,7,7,0,7,7,7,7,8,8,4,0,6,8,4,8,3,3,3,0,3,3,3},
										{2,2,2,2,0,2,2,2,2,4,6,4,0,0,6,0,6,3,0,0,0,0,0,3},
										{2,2,0,0,0,0,0,2,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
										{2,0,0,0,0,0,0,0,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
										{1,0,0,0,0,0,0,0,1,4,4,4,4,4,6,0,6,3,3,0,0,0,3,3},
										{2,0,0,0,0,0,0,0,2,2,2,1,2,2,2,6,6,0,0,5,0,5,0,5},
										{2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
										{2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
										{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
										{2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
										{2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
										{2,2,2,2,1,2,2,2,2,2,2,1,2,2,2,5,5,5,5,5,5,5,5,5}
									};

void	draw(t_info *info)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			info->img.data[y * width + x] = info->buf[y][x];
		}
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}

void	calc(t_info *info)
{
	//FLOOR CASTING
	for(int y = height / 2 + 1; y < height; ++y)
	{
		// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		float rayDirX0 = info->dirX - info->planeX;
		float rayDirY0 = info->dirY - info->planeY;
		float rayDirX1 = info->dirX + info->planeX;
		float rayDirY1 = info->dirY + info->planeY;
		// Current y position compared to the center of the screen (the horizon)
		int p = y - height / 2;
		// Vertical position of the camera.
		float posZ = 0.5 * height;
		// Horizontal distance from the camera to the floor for the current row.
		// 0.5 is the z position exactly in the middle between floor and ceiling.
		float rowDistance = posZ / p;
		// calculate the real world step vector we have to add for each x (parallel to camera plane)
		// adding step by step avoids multiplications with a weight in the inner loop
		float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / width;
		float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / width;
		// real world coordinates of the leftmost column. This will be updated as we step to the right.
		float floorX = info->posX + rowDistance * rayDirX0;
		float floorY = info->posY + rowDistance * rayDirY0;
		for(int x = 0; x < width; ++x)
		{
			// the cell coord is simply got from the integer parts of floorX and floorY
			int cellX = (int)(floorX);
			int cellY = (int)(floorY);
			// get the texture coordinate from the fractional part
			int tx = (int)(texWidth * (floorX - cellX)) & (texWidth - 1);
			int ty = (int)(texHeight * (floorY - cellY)) & (texHeight - 1);
			floorX += floorStepX;
			floorY += floorStepY;
			// choose texture and draw the pixel
			int checkerBoardPattern = (int)(cellX + cellY) & 1;
			int floorTexture;
			if(checkerBoardPattern == 0) floorTexture = 3;
			else floorTexture = 4;
			int ceilingTexture = 6;
			int color;
			// floor
			color = info->texture[floorTexture][texWidth * ty + tx];
			color = (color >> 1) & 8355711; // make a bit darker
			info->buf[y][x] = color;
			//ceiling (symmetrical, at height - y - 1 instead of y)
			color = info->texture[ceilingTexture][texWidth * ty + tx];
			color = (color >> 1) & 8355711; // make a bit darker
			info->buf[height - y - 1][x] = color;
		}
	}
	//WALL CASTING
	for(int x = 0; x < width; x++)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)width - 1; //x-coordinate in camera space
		double rayDirX = info->dirX + info->planeX * cameraX;
		double rayDirY = info->dirY + info->planeY * cameraX;
		//which box of the map we're in
		int mapX = (int)info->posX;
		int mapY = (int)info->posY;
		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;
		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;
		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;
		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (info->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - info->posX) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (info->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - info->posY) * deltaDistY;
		}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if(sideDistX < sideDistY)
			{
			sideDistX += deltaDistX;
			mapX += stepX;
			side = 0;
			}
			else
			{
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
			}
			//Check if ray has hit a wall
			if(worldMap[mapX][mapY] > 0) hit = 1;
		}
		//Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
		if(side == 0) perpWallDist = (mapX - info->posX + (1 - stepX) / 2) / rayDirX;
		else          perpWallDist = (mapY - info->posY + (1 - stepY) / 2) / rayDirY;
		//Calculate height of line to draw on screen
		int lineHeight = (int)(height / perpWallDist);
		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + height / 2;
		if(drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + height / 2;
		if(drawEnd >= height) drawEnd = height - 1;
		//texturing calculations
		int texNum = worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!
		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if (side == 0) wallX = info->posY + perpWallDist * rayDirY;
		else           wallX = info->posX + perpWallDist * rayDirX;
		wallX -= floor((wallX));
		//x coordinate on the texture
		int texX = (int)(wallX * (double)texWidth);
		if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
		if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;
		// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * texHeight / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - height / 2 + lineHeight / 2) * step;
		for(int y = drawStart; y < drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;
			int color = info->texture[texNum][texHeight * texY + texX];
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if(side == 1) color = (color >> 1) & 8355711;
			info->buf[y][x] = color;
		}

		//SET THE ZBUFFER FOR THE SPRITE CASTING
		info->zBuffer[x] = perpWallDist; //perpendicular distance is used
	}

	// //SPRITE CASTING
	//sort sprites from far to close
	for(int i = 0; i < numSprites; i++)
	{
		spriteOrder[i] = i;
		spriteDistance[i] = ((info->posX - sprite[i].x) * (info->posX - sprite[i].x) + (info->posY - sprite[i].y) * (info->posY - sprite[i].y)); //sqrt not taken, unneeded
	}
	sortSprites(spriteOrder, spriteDistance, numSprites);
	//after sorting the sprites, do the projection and draw them
	for(int i = 0; i < numSprites; i++)
	{
		//translate sprite position to relative to camera
		double spriteX = sprite[spriteOrder[i]].x - info->posX;
		double spriteY = sprite[spriteOrder[i]].y - info->posY;

		//transform sprite with the inverse camera matrix
		// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
		// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
		// [ planeY   dirY ]                                          [ -planeY  planeX ]

		double invDet = 1.0 / (info->planeX * info->dirY - info->dirX * info->planeY); //required for correct matrix multiplication

		double transformX = invDet * (info->dirY * spriteX - info->dirX * spriteY);
		double transformY = invDet * (-info->planeY * spriteX + info->planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])

		int spriteScreenX = (int)((width / 2) * (1 + transformX / transformY));

		//parameters for scaling and moving the sprites
		#define uDiv 1
		#define vDiv 1
		#define vMove 0.0
		int vMoveScreen = (int)(vMove / transformY);

		//calculate height of the sprite on screen
		int spriteHeight = (int)fabs((height / transformY) / vDiv); //using "transformY" instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + height / 2 + vMoveScreen;
		if(drawStartY < 0) drawStartY = 0;
		int drawEndY = spriteHeight / 2 + height / 2 + vMoveScreen;
		if(drawEndY >= height) drawEndY = height - 1;

		//calculate width of the sprite
		int spriteWidth = (int)fabs((height / transformY) / uDiv);
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0) drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= width) drawEndX = width - 1;

		//loop through every vertical stripe of the sprite on screen
		for(int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)((256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256);
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if(transformY > 0 && stripe > 0 && stripe < width && transformY < info->zBuffer[stripe])
			for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
			{
				int d = (y-vMoveScreen) * 256 - height * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
				int texY = ((d * texHeight) / spriteHeight) / 256;
				int color = info->texture[sprite[spriteOrder[i]].texture][texWidth * texY + texX]; //get current color from the texture
				if((color & 0x00FFFFFF) != 0) info->buf[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
			}
		}
	}
}

int	main_loop(t_info *info)
{
	calc(info);
	draw(info);
	key_update(info);
	return (0);
}

void	key_update(t_info *info)
{
	if (info->key_w)
	{
		if (!worldMap[(int)(info->posX + info->dirX * info->moveSpeed)][(int)(info->posY)])
			info->posX += info->dirX * info->moveSpeed;
		if (!worldMap[(int)(info->posX)][(int)(info->posY + info->dirY * info->moveSpeed)])
			info->posY += info->dirY * info->moveSpeed;
	}
	//move backwards if no wall behind you
	if (info->key_s)
	{
		if (!worldMap[(int)(info->posX - info->dirX * info->moveSpeed)][(int)(info->posY)])
			info->posX -= info->dirX * info->moveSpeed;
		if (!worldMap[(int)(info->posX)][(int)(info->posY - info->dirY * info->moveSpeed)])
			info->posY -= info->dirY * info->moveSpeed;
	}
	//rotate to the right
	if (info->key_d)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(-info->rotSpeed) - info->dirY * sin(-info->rotSpeed);
		info->dirY = oldDirX * sin(-info->rotSpeed) + info->dirY * cos(-info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(-info->rotSpeed) - info->planeY * sin(-info->rotSpeed);
		info->planeY = oldPlaneX * sin(-info->rotSpeed) + info->planeY * cos(-info->rotSpeed);
	}
	//rotate to the left
	if (info->key_a)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(info->rotSpeed) - info->dirY * sin(info->rotSpeed);
		info->dirY = oldDirX * sin(info->rotSpeed) + info->dirY * cos(info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(info->rotSpeed) - info->planeY * sin(info->rotSpeed);
		info->planeY = oldPlaneX * sin(info->rotSpeed) + info->planeY * cos(info->rotSpeed);
	}
	if (info->key_esc)
		exit(0);
}

int		key_press(int key, t_info *info)
{
	if (key == K_ESC)
		exit(0);
	else if (key == K_W)
		info->key_w = 1;
	else if (key == K_A)
		info->key_a = 1;
	else if (key == K_S)
		info->key_s = 1;
	else if (key == K_D)
		info->key_d = 1;
	return (0);
}

int		key_release(int key, t_info *info)
{
	if (key == K_ESC)
		exit(0);
	else if (key == K_W)
		info->key_w = 0;
	else if (key == K_A)
		info->key_a = 0;
	else if (key == K_S)
		info->key_s = 0;
	else if (key == K_D)
		info->key_d = 0;
	return (0);
}

void	load_image(t_info *info, int *texture, char *path, t_img *img)
{
	img->img = mlx_xpm_file_to_image(info->mlx, path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	for (int y = 0; y < img->img_height; y++)
	{
		for (int x = 0; x < img->img_width; x++)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
		}
	}
	mlx_destroy_image(info->mlx, img->img);
}

void	load_texture(t_info *info)
{
	t_img	img;

	load_image(info, info->texture[0], "textures/eagle.xpm", &img);
	load_image(info, info->texture[1], "textures/redbrick.xpm", &img);
	load_image(info, info->texture[2], "textures/purplestone.xpm", &img);
	load_image(info, info->texture[3], "textures/greystone.xpm", &img);
	load_image(info, info->texture[4], "textures/bluestone.xpm", &img);
	load_image(info, info->texture[5], "textures/mossy.xpm", &img);
	load_image(info, info->texture[6], "textures/wood.xpm", &img);
	load_image(info, info->texture[7], "textures/colorstone.xpm", &img);
	load_image(info, info->texture[8], "textures/barrel.xpm", &img);
	load_image(info, info->texture[9], "textures/pillar.xpm", &img);
	load_image(info, info->texture[10], "textures/greenlight.xpm", &img);
}


int	main(void)
{
	t_info info;
	info.mlx = mlx_init();

	info.posX = 22.0;
	info.posY = 11.5;
	info.dirX = -1.0;
	info.dirY = 0.0;
	info.planeX = 0.0;
	info.planeY = 0.66;
	info.key_a = 0;
	info.key_w = 0;
	info.key_s = 0;
	info.key_d = 0;
	info.key_esc = 0;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			info.buf[i][j] = 0;
		}
	}

	if (!(info.texture = (int **)malloc(sizeof(int *) * 11)))
		return (-1);
	for (int i = 0; i < 11; i++)
	{
		if (!(info.texture[i] = (int *)malloc(sizeof(int) * (texHeight * texWidth))))
			return (-1);
	}
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < texHeight * texWidth; j++)
		{
			info.texture[i][j] = 0;
		}
	}
	load_texture(&info);

	info.moveSpeed = 0.05;
	info.rotSpeed = 0.05;
	
	info.win = mlx_new_window(info.mlx, width, height, "mlx");

	info.img.img = mlx_new_image(info.mlx, width, height);
	info.img.data = (int *)mlx_get_data_addr(info.img.img, &info.img.bpp, &info.img.size_l, &info.img.endian);
	mlx_loop_hook(info.mlx, &main_loop, &info);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_hook(info.win, X_EVENT_KEY_RELEASE, 0, &key_release, &info);

	mlx_loop(info.mlx);
}
