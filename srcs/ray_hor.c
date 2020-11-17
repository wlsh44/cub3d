/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 19:04:52 by jinhkim           #+#    #+#             */
/*   Updated: 2020/11/17 19:04:53 by jinhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_camera_dir(t_all *all, t_dir *dir0, t_dir *dir1)
{
	dir0->x = all->dir.x - all->plane.x;
	dir0->y = all->dir.y - all->plane.y;
	dir1->x = all->dir.x + all->plane.x;
	dir1->y = all->dir.y + all->plane.y;
}

void	init_coordinates(t_all *all, t_pos *d, t_pos *floor, int y)
{
	t_dir	dir0;
	t_dir	dir1;
	int		dz;
	double	z;
	double	row_dist;

	get_camera_dir(all, &dir0, &dir1);
	dz = y - all->win.y / 2;
	z = 0.5 * all->win.y;
	row_dist = z / dz;
	d->x = row_dist * (dir1.x - dir0.x) / all->win.x;
	d->y = row_dist * (dir1.y - dir0.y) / all->win.x;
	floor->x = all->pos.x + row_dist * dir0.x;
	floor->y = all->pos.y + row_dist * dir0.y;
}

void	add_to_buf_hor(t_all *all, t_pos *d, t_pos *floor, int y)
{
	int		x;
	int		color;
	t_pair	tex;

	x = 0;
	while (x < all->win.x)
	{
		tex.x = (int)(64 * (floor->x - (int)(floor->x))) & (64 - 1);
		tex.y = (int)(64 * (floor->y - (int)(floor->y))) & (64 - 1);
		floor->x += d->x;
		floor->y += d->y;
		color = all->texture[FLOOR][TEX_W * tex.y + tex.x];
		all->buf[y][x] = color;
		color = all->texture[CEILING][TEX_W * tex.y + tex.x];
		all->buf[all->win.y - y - 1][x] = color;
		x++;
	}
}
