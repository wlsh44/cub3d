/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 19:05:19 by jinhkim           #+#    #+#             */
/*   Updated: 2020/11/17 19:05:20 by jinhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		spaceskip(char *line, int *i)
{
	while ((line[*i] == ' ' || line[*i] == '\t' || line[*i] == '\n')
	|| (line[*i] == '\r' || line[*i] == '\v' || line[*i] == '\f'))
		(*i)++;
	return (1);
}

int		ft_atoi(char *line, int *i)
{
	int	num;

	num = 0;
	spaceskip(line, i);
	while (line[*i] >= '0' && line[*i] <= '9')
	{
		num = num * 10 + (line[*i] - 48);
		(*i)++;
	}
	return (num);
}

int		namecheck(char *name, char *ext)
{
	int	i;

	i = 0;
	while (name[i] != '\0')
		i++;
	if ((i > 4 && name[i - 1] == ext[2] && name[i - 2] == ext[1])
		&& (name[i - 3] == ext[0] && name[i - 4] == '.'))
		return (1);
	return (0);
}

int		savecheck(char *name, char *save)
{
	int	i;

	i = 0;
	while (name[i] == save[i])
	{
		if (name[i] == '\0' && save[i] == '\0')
			return (1);
		i++;
	}
	return (0);
}

int		is_valid_map(t_all *all, int i, int j, int *flag)
{
	if (all->map.tmp[i][j] == 'W' || all->map.tmp[i][j] == 'N'
			|| all->map.tmp[i][j] == 'S' || all->map.tmp[i][j] == 'E')
	{
		if (all->map.tmp[i][j] == 'W' || all->map.tmp[i][j] == 'N')
			position1(all, all->map.tmp[i][j]);
		else
			position2(all, all->map.tmp[i][j]);
		all->pos.y = i;
		all->pos.x = j;
		(*flag)++;
		return (1);
	}
	else if (all->map.tmp[i][j] == ' ' && !check_srround(all, i, j))
		return (0);
	else if (all->map.tmp[i][j] == '2')
	{
		if (all->sprite_num == 29)
			print_error(-8);
		all->s_pos[all->sprite_num].x = i;
		all->s_pos[all->sprite_num++].y = j;
		return (1);
	}
	return (1);
}
