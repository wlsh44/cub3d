/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 22:24:08 by jinhkim           #+#    #+#             */
/*   Updated: 2020/11/17 22:24:10 by jinhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		check_last_border(t_all *all)
{
	int	i;

	i = 0;
	while (all->map.tmp[all->map.y - 1][i] != 0)
	{
		if (all->map.tmp[all->map.y - 1][i] == '0')
			return (0);
		i++;
	}
	return (1);
}

int		check_border(t_all *all, char *line)
{
	int	i;
	int	len;

	i = 0;
	spaceskip(line, &i);
	len = i;
	while (line[len] != 0)
		len++;
	if (all->map.y == 0)
		while (line[i] != 0)
		{
			if (line[i] == '0')
				return (0);
			i++;
		}
	else if (line[0] == '0' || line[len - 1] == '0')
		return (0);
	return (1);
}

void	position1(t_all *all, char pos)
{
	double	tmp;

	tmp = all->dir.x;
	if (pos == 'N')
	{
		all->dir.x = all->dir.x * cos(A) - all->dir.y * sin(A);
		all->dir.y = tmp * sin(A) +
						all->dir.y * cos(A);
		tmp = all->plane.x;
		all->plane.x = all->plane.x * cos(A) -
						all->plane.y * sin(A);
		all->plane.y = tmp * sin(A) + all->plane.y * cos(A);
	}
	if (pos == 'W')
	{
		all->dir.x = all->dir.x * cos(M_PI / 2 + A) -
						all->dir.y * sin(M_PI / 2 + A);
		all->dir.y = tmp * sin(M_PI / 2 + A) +
						all->dir.y * cos(M_PI / 2 + A);
		tmp = all->plane.x;
		all->plane.x = all->plane.x * cos(M_PI / 2 + A) -
						all->plane.y * sin(M_PI / 2 + A);
		all->plane.y = tmp * sin(M_PI / 2 + A) +
						all->plane.y * cos(M_PI / 2 + A);
	}
}

void	position2(t_all *all, char pos)
{
	double	tmp;

	tmp = all->dir.x;
	if (pos == 'E')
	{
		all->dir.x = all->dir.x * cos(-M_PI / 2 + A) -
		all->dir.y * sin(-M_PI / 2 + A);
		all->dir.y = tmp * sin(-M_PI / 2 + A) +
						all->dir.y * cos(-M_PI / 2 + A);
		tmp = all->plane.x;
		all->plane.x = all->plane.x * cos(-M_PI / 2 + A) -
						all->plane.y * sin(-M_PI / 2 + A);
		all->plane.y = tmp * sin(-M_PI / 2 + A) +
						all->plane.y * cos(-M_PI / 2 + A);
	}
	if (pos == 'S')
	{
		all->dir.x = all->dir.x * cos(M_PI + A) -
						all->dir.y * sin(M_PI + A);
		all->dir.y = tmp * sin(M_PI + A) + all->dir.y * cos(M_PI + A);
		tmp = all->plane.x;
		all->plane.x = all->plane.x * cos(M_PI + A) -
						all->plane.y * sin(M_PI + A);
		all->plane.y = tmp * sin(M_PI + A) + all->plane.y * cos(M_PI + A);
	}
}
