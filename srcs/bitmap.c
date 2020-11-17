/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 19:03:41 by jinhkim           #+#    #+#             */
/*   Updated: 2020/11/17 19:03:47 by jinhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_bdata(t_all *s, int fd)
{
	int				i;
	int				j;
	unsigned char	buffer[4];

	i = s->win.x * (s->win.y - 1);
	while (i >= 0)
	{
		j = 0;
		while (j < s->win.x)
		{
			buffer[0] = (unsigned char)(s->img.data[i] % 256);
			buffer[1] = (unsigned char)(s->img.data[i] / 256 % 256);
			buffer[2] = (unsigned char)(s->img.data[i] / 256 / 256 % 256);
			buffer[3] = (unsigned char)(0);
			write(fd, buffer, 4);
			i++;
			j++;
		}
		i -= 2 * s->win.x;
	}
}

void	ft_binfo(t_all *s, int fd)
{
	int				n;
	unsigned char	header[40];

	n = 0;
	while (n < 40)
		header[n++] = (unsigned char)(0);
	header[0] = (unsigned char)(40);
	n = s->win.x;
	header[4] = (unsigned char)(n % 256);
	header[5] = (unsigned char)(n / 256 % 256);
	header[6] = (unsigned char)(n / 256 / 256 % 256);
	header[7] = (unsigned char)(n / 256 / 256 / 256);
	n = s->win.y;
	header[8] = (unsigned char)(n % 256);
	header[9] = (unsigned char)(n / 256 % 256);
	header[10] = (unsigned char)(n / 256 / 256 % 256);
	header[11] = (unsigned char)(n / 256 / 256 / 256);
	header[12] = (unsigned char)(1);
	header[14] = (unsigned char)(32);
	write(fd, header, 40);
}

void	ft_bfile(t_all *s, int fd)
{
	int				n;
	unsigned char	header[14];

	n = 0;
	while (n < 14)
		header[n++] = (unsigned char)(0);
	header[0] = (unsigned char)(66);
	header[1] = (unsigned char)(77);
	n = s->win.x * s->win.y * 4 + 54;
	header[2] = (unsigned char)(n % 256);
	header[3] = (unsigned char)(n / 256 % 256);
	header[4] = (unsigned char)(n / 256 / 256 % 256);
	header[5] = (unsigned char)(n / 256 / 256 / 256);
	header[10] = (unsigned char)(54);
	write(fd, header, 14);
}

int		bitmap(t_all *all)
{
	int		fd;

	fd = open("bitmap.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	ft_bfile(all, fd);
	ft_binfo(all, fd);
	ft_bdata(all, fd);
	close(fd);
	closed(all);
	return (1);
}
