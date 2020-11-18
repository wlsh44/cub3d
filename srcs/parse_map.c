/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 19:04:28 by jinhkim           #+#    #+#             */
/*   Updated: 2020/11/17 19:04:28 by jinhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		get_map_tmp(t_all *all, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (line == NULL)
		return (-1);
	if (!check_border(all, line))
		print_error(-2);
	while (line[i] == '\t')
	{
		all->map.tmp[all->map.y][j++] = ' ';
		while (j % 4 != 0)
			all->map.tmp[all->map.y][j++] = ' ';
		i++;
	}
	while (line[i] != 0 && j < 80)
		all->map.tmp[all->map.y][j++] = line[i++];
	all->map.tmp[all->map.y][j] = 0;
	if (all->map.x < j)
		all->map.x = j;
	if (++all->map.y == 80 || all->map.x == 80)
		print_error(-2);
	return (0);
}

void	map_alloc(t_all *all)
{
	int	y;
	int	x;

	y = 0;
	if (!(all->map.map = malloc(sizeof(int *) * all->map.y)))
		print_error(-7);
	while (y < all->map.y)
	{
		x = 0;
		if (!(all->map.map[y] = malloc(sizeof(int) * all->map.x)))
			print_error(-7);
		while (x < all->map.x)
		{
			if (all->map.tmp[y][x] == ' ' || all->map.tmp[y][x] == '1')
				all->map.map[y][x] = 1;
			else
				all->map.map[y][x] = 0;
			x++;
		}
		y++;
	}
}

int		check_srround(t_all *all, int y, int x)
{
	if (y == 0 && (all->map.tmp[y + 1][x] == '0' ||
		all->map.tmp[y + 1][x] == '2'))
		return (0);
	else if (y == all->map.y - 1 && (all->map.tmp[y - 1][x] == '0' ||
								all->map.tmp[y - 1][x] == '2'))
		return (0);
	else if ((y != 0 && y != all->map.y - 1) &&
			(all->map.tmp[y + 1][x] == '0' || all->map.tmp[y - 1][x] == '0' ||
			all->map.tmp[y + 1][x] == '2' || all->map.tmp[y - 1][x] == '2'))
		return (0);
	if (x == 0 && (all->map.tmp[y][x + 1] == '0' ||
					all->map.tmp[y][x + 1] == '2'))
		return (0);
	else if (x == all->map.x - 1 && (all->map.tmp[y][x - 1] == '0' ||
									all->map.tmp[y][x - 1] == '2'))
		return (0);
	else if ((x != 0 && x != all->map.x - 1) &&
			(all->map.tmp[y][x + 1] == '0' || all->map.tmp[y][x - 1] == '0' ||
			all->map.tmp[y][x + 1] == '2' || all->map.tmp[y][x - 1] == '2'))
		return (0);
	return (1);
}

int		check_map(t_all *all)
{
	int	flag;
	int	i;
	int	j;

	i = -1;
	flag = 0;
	while (++i < all->map.y)
	{
		j = -1;
		while (++j < all->map.x)
			if (!is_valid_map(all, i, j, &flag))
				return (0);
	}
	if (flag != 1)
		return (0);
	return (1);
}

int		map_parse(t_all *all)
{
	if (!check_map(all))
		return (-1);
	map_alloc(all);
	return (0);
}
