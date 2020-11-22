/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 19:04:19 by jinhkim           #+#    #+#             */
/*   Updated: 2020/11/17 19:04:20 by jinhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	first_init(t_all *all)
{
	int	x;
	int	y;

	y = -1;
	all->dir.x = -1.0;
	all->dir.y = 0;
	all->plane.x = 0;
	all->plane.y = 0.66;
	all->map.x = 0;
	all->map.y = 0;
	all->win.x = 0;
	all->win.y = 0;
	all->tex_num = 0;
	all->sprite_num = 0;
	all->texture = malloc(sizeof(int *) * 7);
	while (++y < 7)
	{
		x = 0;
		all->texture[y] = malloc(sizeof(int) * (TEX_H * TEX_H));
		while (x < TEX_H * TEX_H)
		{
			all->map.tmp[y][x] = 0;
			all->texture[y][x++] = 0;
		}
	}
}

void	second_init(t_all *all)
{
	int	y;
	int	x;

	y = 0;
	all->buf = malloc(sizeof(int *) * all->win.y);
	while (y < all->img.y)
	{
		x = 0;
		all->buf[y] = malloc(sizeof(int) * all->win.x);
		while (x < all->win.x)
			all->buf[y][x++] = -1;
		y++;
	}
	all->z_buf = malloc(sizeof(int) * all->win.x);
}

void	cub3d(char *file, int save)
{
	t_all	all;

	first_init(&all);
	all.mlx = mlx_init();
	parse(&all, file);
	second_init(&all);
	cubed(&all, save);
}

int		main(int argc, char *argv[])
{
	if (argc == 3)
	{
		if (!namecheck(argv[1], "cub"))
			print_error(-1);
		if (!savecheck(argv[2], "--save"))
			print_error(0);
		cub3d(argv[1], 1);
	}
	else if (argc == 2)
	{
		if (!namecheck(argv[1], "cub"))
			print_error(-1);
		cub3d(argv[1], 0);
	}
	else
		print_error(0);
	return (0);
}
