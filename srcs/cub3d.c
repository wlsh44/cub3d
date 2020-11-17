/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 19:03:54 by jinhkim           #+#    #+#             */
/*   Updated: 2020/11/17 19:03:55 by jinhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw(t_all *all)
{
	int	x;
	int	y;

	y = 0;
	while (y < all->win.y)
	{
		x = 0;
		while (x < all->win.x)
		{
			all->img.data[y * all->win.x + x] = all->buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(all->mlx, all->win.win, all->img.img, 0, 0);
}

int		main_loop(t_all *all)
{
	ray_casting(all);
	draw(all);
	return (0);
}

void	cubed(t_all *all, int save)
{
	all->win.win = mlx_new_window(all->mlx, all->img.x, all->img.y, "cub3D");
	all->img.img = mlx_new_image(all->mlx, all->img.x, all->img.y);
	all->img.data = (int *)mlx_get_data_addr(all->img.img, &all->img.bpp,
											&all->img.size, &all->img.endian);
	if (save == 1)
	{
		main_loop(all);
		bitmap(all);
		return ;
	}
	mlx_loop_hook(all->mlx, &main_loop, all);
	mlx_hook(all->win.win, KEY_PRESS, 0, &key_press, all);
	mlx_loop(all->mlx);
}
