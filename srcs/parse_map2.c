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
