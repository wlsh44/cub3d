/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 19:04:13 by jinhkim           #+#    #+#             */
/*   Updated: 2020/11/17 19:04:15 by jinhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	move(int key, t_all *all)
{
	if (key == W)
	{
		if (!all->map.map[(int)(all->pos.x + all->dir.x * MOVE_SPEED)]
			[(int)all->pos.y])
			all->pos.x += all->dir.x * MOVE_SPEED;
		if (!all->map.map[(int)all->pos.x]
			[(int)(all->pos.y + all->dir.y * MOVE_SPEED)])
			all->pos.y += all->dir.y * MOVE_SPEED;
	}
	if (key == S)
	{
		if (!all->map.map[(int)(all->pos.x - all->dir.x * MOVE_SPEED)]
			[(int)all->pos.y])
			all->pos.x -= all->dir.x * MOVE_SPEED;
		if (!all->map.map[(int)all->pos.x]
			[(int)(all->pos.y - all->dir.y * MOVE_SPEED)])
			all->pos.y -= all->dir.y * MOVE_SPEED;
	}
}

void	strafe(int key, t_all *all)
{
	if (key == A)
	{
		if (!all->map.map[(int)(all->pos.x - all->dir.y * MOVE_SPEED)]
			[(int)all->pos.y])
			all->pos.x -= all->dir.y * MOVE_SPEED;
		if (!all->map.map[(int)all->pos.x]
			[(int)(all->pos.y + all->dir.x * MOVE_SPEED)])
			all->pos.y += all->dir.x * MOVE_SPEED;
	}
	if (key == D)
	{
		if (!all->map.map[(int)(all->pos.x + all->dir.y * MOVE_SPEED)]
			[(int)all->pos.y])
			all->pos.x += all->dir.y * MOVE_SPEED;
		if (!all->map.map[(int)all->pos.x]
			[(int)(all->pos.y - all->dir.x * MOVE_SPEED)])
			all->pos.y -= all->dir.x * MOVE_SPEED;
	}
}

void	rotate(int key, t_all *all)
{
	double	tmp;

	tmp = all->dir.x;
	if (key == LEFT)
	{
		all->dir.x = all->dir.x * cos(ROT_SPEED) - all->dir.y * sin(ROT_SPEED);
		all->dir.y = tmp * sin(ROT_SPEED) +
						all->dir.y * cos(ROT_SPEED);
		tmp = all->plane.x;
		all->plane.x = all->plane.x * cos(ROT_SPEED) -
						all->plane.y * sin(ROT_SPEED);
		all->plane.y = tmp * sin(ROT_SPEED) + all->plane.y * cos(ROT_SPEED);
	}
	if (key == RIGHT)
	{
		all->dir.x = all->dir.x * cos(-ROT_SPEED) -
						all->dir.y * sin(-ROT_SPEED);
		all->dir.y = tmp * sin(-ROT_SPEED) +
						all->dir.y * cos(-ROT_SPEED);
		tmp = all->plane.x;
		all->plane.x = all->plane.x * cos(-ROT_SPEED) -
						all->plane.y * sin(-ROT_SPEED);
		all->plane.y = tmp * sin(-ROT_SPEED) + all->plane.y * cos(-ROT_SPEED);
	}
}

void	closed(t_all *all)
{
	mlx_destroy_window(all->mlx, all->win.win);
	free(all->mlx);
	exit(0);
}

int		key_press(int key, t_all *all)
{
	if (key == W || key == S)
		move(key, all);
	else if (key == A || key == D)
		strafe(key, all);
	else if (key == LEFT || key == RIGHT)
		rotate(key, all);
	else if (key == ESC)
		closed(all);
	return (0);
}
