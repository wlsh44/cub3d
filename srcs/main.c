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

	y = 0;
	all->pos.x = 0;
	all->pos.y = 0;
	all->dir.x = -1.0;
	all->dir.y = 0;
	all->plane.x = 0;
	all->plane.y = 0.66;
	all->map.x = 0;
	all->map.y = 0;
	all->win.x = 0;
	all->win.y = 0;
	all->sprite_num = 0;
	all->texture = malloc(sizeof(int *) * 7);
	while (y < 7)
	{
		x = 0;
		all->texture[y] = malloc(sizeof(int) * (TEX_H * TEX_H));
		while (x < TEX_H * TEX_H)
			all->texture[y][x++] = 0;
		y++;
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
			all->buf[y][x++] = 0;
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
	if (argc == 3 && namecheck(argv[1], "cub") && savecheck(argv[2], "--save"))
		cub3d(argv[1], 1);
	else if (argc == 2 && namecheck(argv[1], "cub"))
		cub3d(argv[1], 0);
	else
		write(2, "Error : Invalid arguments\n", 26);
	return (0);
}
