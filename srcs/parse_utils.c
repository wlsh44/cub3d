/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 19:04:34 by jinhkim           #+#    #+#             */
/*   Updated: 2020/11/17 19:04:35 by jinhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		get_next_line(int fd, char **line)
{
	int			read_size;
	char		buf[4096];
	static char	*save = NULL;

	if (line == NULL || fd < 0)
		return (-3);
	*line = NULL;
	read_size = 1;
	while (!(newline_check(save, read_size)))
	{
		if ((read_size = read(fd, buf, 4095)) == -1)
			return (-3);
		buf[read_size] = '\0';
		if ((save = buf_join(save, buf)) == NULL)
			return (-3);
	}
	if ((*line = get_line(save)) == NULL)
		return (-3);
	if (read_size == 0)
		free(save);
	if (read_size == 0)
		return (0);
	if ((save = save_trim(save)) == NULL)
		return (-3);
	return (1);
}

int		load_image(t_all *all, int *texture, char *path, t_img *img)
{
	int	x;
	int	y;

	y = 0;
	img->img = mlx_xpm_file_to_image(all->mlx, path, &img->x, &img->y);
	if (img->img == NULL)
		return (-6);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp,
										&img->size, &img->endian);
	while (y < img->y)
	{
		x = 0;
		while (x < img->x)
		{
			texture[img->x * y + x] = img->data[img->x * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(all->mlx, img->img);
	return (0);
}

void	set_color(t_all *all, int num, unsigned int color)
{
	int i;
	int j;

	i = 0;
	while (i < TEX_W)
	{
		j = 0;
		while (j < TEX_H)
		{
			all->texture[num][TEX_W * j + i] = color;
			j++;
		}
		i++;
	}
}
