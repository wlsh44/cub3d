/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 19:05:11 by jinhkim           #+#    #+#             */
/*   Updated: 2020/11/17 19:05:12 by jinhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	horizon(t_all *all)
{
	int		y;
	t_pos	d;
	t_pos	floor;

	y = all->win.y / 2 + 1;
	while (y < all->win.y)
	{
		init_coordinates(all, &d, &floor, y);
		add_to_buf_hor(all, &d, &floor, y);
		y++;
	}
}

void	vertical(t_all *all)
{
	int		x;
	t_ver	v;

	x = 0;
	while (x < all->win.x)
	{
		get_dir(all, &v, x);
		init_dda(all, &v);
		dda_algorithm(all, &v);
		add_to_buf_ver(all, &v, x);
		x++;
	}
}

void	sprite(t_all *all)
{
	int			i;
	t_sprite	sprite;

	get_sprite_dist(all, &sprite);
	i = 0;
	while (i < all->sprite_num)
	{
		init_sprite(all, &sprite, i);
		add_to_buf_spr(all, &sprite);
		i++;
	}
}

void	ray_casting(t_all *all)
{
	horizon(all);
	vertical(all);
	sprite(all);
}
