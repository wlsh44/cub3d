/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 19:04:39 by jinhkim           #+#    #+#             */
/*   Updated: 2020/11/17 19:04:40 by jinhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		get_texture(t_all *all, char *line, int i)
{
	t_img	img;

	if (!namecheck(line, "xpm"))
		return (-5);
	return (load_image(all, all->texture[i], line, &img));
}

int		get_win(t_all *all, char *line)
{
	int	i;
	int	width;
	int	height;

	i = 0;
	width = ft_atoi(line, &i);
	height = ft_atoi(line, &i);
	if (width <= 0 || height <= 0)
		return (-3);
	all->win.x = width;
	all->win.y = height;
	if (all->win.x > 2560)
		all->win.x = 2560;
	if (all->win.y > 1400)
		all->win.y = 1400;
	all->img.x = all->win.x;
	all->img.y = all->win.y;
	return (0);
}

int		get_color(t_all *all, char *line, int num)
{
	int	i;
	int	j;
	int	r;
	int	g;
	int	b;

	if (line[0] == '.')
		return (get_texture(all, line, num));
	i = 0;
	r = ft_atoi(line, &i);
	i++;
	g = ft_atoi(line, &i);
	i++;
	b = ft_atoi(line, &i);
	i++;
	if (line[i] != '\0' || r > 255 || g > 255 || b > 255)
		return (-4);
	set_color(all, r * 256 * 256 + g * 256 + b, num);
	return (0);
}

int		parse_line(t_all *all, char *line)
{
	int	errno;

	errno = 0;
	if (line[0] == 'R' && line[1] == ' ')
		errno = get_win(all, line + 2);
	else if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		errno = get_texture(all, line + 3, 0);
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		errno = get_texture(all, line + 3, 1);
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		errno = get_texture(all, line + 3, 2);
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		errno = get_texture(all, line + 3, 3);
	else if (line[0] == 'F' && line[1] == ' ')
		errno = get_color(all, line + 2, 4);
	else if (line[0] == 'C' && line[1] == ' ')
		errno = get_color(all, line + 2, 5);
	else if (line[0] == 'S' && line[1] == ' ')
		errno = get_texture(all, line + 2, 6);
	else if (line[0] != 0)
		return (get_map_tmp(all, line));
	if (errno != 0)
		print_error(errno);
	return (errno);
}

void	parse(t_all *all, char *file)
{
	int		fd;
	int		res;
	char	*line;
	double	tmp;

	res = 1;
	if ((fd = open(file, O_RDONLY)) == -1)
		print_error(-1);
	while (res == 1)
	{
		res = get_next_line(fd, &line);
		if (parse_line(all, line) == -1)
			res = -1;
		free(line);
	}
	close(fd);
	if (!check_last_border(all) || map_parse(all))
		print_error(-2);
	tmp = all->pos.x;
	all->pos.x = all->pos.y;
	all->pos.y = tmp;
}
