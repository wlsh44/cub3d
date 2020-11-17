/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 19:05:14 by jinhkim           #+#    #+#             */
/*   Updated: 2020/11/17 19:05:15 by jinhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	sort_sprite(t_sprite *s, int size)
{
	t_pair	tmp;
	int		i;
	int		j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size - 1)
		{
			if (s->dist[j] < s->dist[j + 1])
			{
				tmp.x = s->dist[j];
				tmp.y = s->order[j];
				s->dist[j] = s->dist[j + 1];
				s->order[j] = s->order[j + 1];
				s->dist[j + 1] = tmp.x;
				s->order[j + 1] = tmp.y;
			}
			j++;
		}
		i++;
	}
}

void	get_sprite_dist(t_all *all, t_sprite *s)
{
	int	i;

	i = 0;
	while (i < all->sprite_num)
	{
		s->order[i] = 0;
		s->dist[i++] = 0;
	}
	i = 0;
	while (i < all->sprite_num)
	{
		s->order[i] = i;
		s->dist[i] = (all->pos.x - all->s_pos[i].x) *
					(all->pos.x - all->s_pos[i].x) +
					(all->pos.y - all->s_pos[i].y) *
					(all->pos.y - all->s_pos[i].y);
		i++;
	}
	sort_sprite(s, all->sprite_num);
}

void	get_pos_x(t_all *all, t_sprite *s, int i)
{
	t_pos	pos;
	double	inv_det;

	pos.x = all->s_pos[s->order[i]].x - all->pos.x;
	pos.y = all->s_pos[s->order[i]].y - all->pos.y;
	inv_det = 1.0 / (all->plane.x * all->dir.y - all->dir.x * all->plane.y);
	s->transform.x = inv_det * (all->dir.y * pos.x - all->dir.x * pos.y);
	s->transform.y = inv_det * (-all->plane.y * pos.x + all->plane.x * pos.y);
	s->pos_x = (int)((all->win.x / 2) * (1 + s->transform.x / s->transform.y));
}

void	init_sprite(t_all *all, t_sprite *s, int i)
{
	int	tmp;

	get_pos_x(all, s, i);
	s->height = (int)fabs(all->win.y / s->transform.y);
	tmp = -s->height / 2 + all->win.y / 2;
	s->start.y = tmp < 0 ? 0 : tmp;
	tmp = s->height / 2 + all->win.y / 2;
	s->end.y = tmp >= all->win.y ? all->win.y - 1 : tmp;
	s->width = (int)fabs(all->win.y / s->transform.y);
	tmp = -s->width / 2 + s->pos_x;
	s->start.x = tmp < 0 ? 0 : tmp;
	tmp = s->width / 2 + s->pos_x;
	s->end.x = tmp >= all->win.x ? all->win.x - 1 : tmp;
}

void	add_to_buf_spr(t_all *all, t_sprite *s)
{
	int	x;
	int	y;
	int	d;
	int	color;

	x = s->start.x;
	while (x < s->end.x)
	{
		y = s->start.y;
		s->tex.x = (int)((256 * (x - (-s->width / 2 + s->pos_x)) *
						TEX_W / s->width) / 256);
		if (s->transform.y > 0 && x > 0 && x < all->win.x &&
			s->transform.y < all->z_buf[x])
			while (y < s->end.y)
			{
				d = y * 256 - all->win.y * 128 + s->height * 128;
				s->tex.y = ((d * TEX_H) / s->height) / 256;
				color = all->texture[6][TEX_W * s->tex.y + s->tex.x];
				if ((color & 0x00FFFFFF) != 0)
					all->buf[y][x] = color;
				y++;
			}
		x++;
	}
}
