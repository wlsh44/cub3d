/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_ver.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 19:04:58 by jinhkim           #+#    #+#             */
/*   Updated: 2020/11/17 19:04:59 by jinhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_tex_num(t_all *all, t_ver *v)
{
	if (v->step.x == 1 && v->step.y == 1)
	{
		v->tex_num = v->wall == 'x' ? 2 : 1;
	}
	else if (v->step.x == 1 && v->step.y == -1)
	{
		v->tex_num = v->wall == 'x' ? 2 : 0;
	}
	else if (v->step.x == -1 && v->step.y == 1)
	{
		v->tex_num = v->wall == 'x' ? 3 : 1;
	}
	else if (v->step.x == -1 && v->step.y == -1)
	{
		v->tex_num = v->wall == 'x' ? 3 : 0;
	}
}

void	init_add_to_buf(t_all *all, t_ver *v)
{
	int		tmp;
	double	wall_x;

	v->line_height = (int)(all->win.y / v->wall_dist);
	tmp = -v->line_height / 2 + all->win.y / 2;
	v->start = tmp < 0 ? 0 : tmp;
	tmp = v->line_height / 2 + all->win.y / 2;
	v->end = tmp >= all->win.y ? all->win.y - 1 : tmp;
	set_tex_num(all, v);
	wall_x = v->wall == 'x' ? all->pos.y + v->wall_dist * v->dir.y :
							all->pos.x + v->wall_dist * v->dir.x;
	wall_x -= floor(wall_x);
	v->tex.x = (int)(wall_x * (double)TEX_W);
	if (v->wall == 'x' && v->dir.x > 0)
		v->tex.x = TEX_W - v->tex.x - 1;
	else if (v->wall == 'y' && v->dir.y < 0)
		v->tex.x = TEX_W - v->tex.x - 1;
	v->ratio = 1.0 * TEX_H / v->line_height;
	v->tex_pos = (v->start - all->win.y / 2 + v->line_height / 2) * v->ratio;
}

void	add_to_buf_ver(t_all *all, t_ver *v, int x)
{
	int	y;

	init_add_to_buf(all, v);
	y = v->start;
	while (y < v->end)
	{
		v->tex.y = (int)v->tex_pos & (64 - 1);
		v->tex_pos += v->ratio;
		all->buf[y][x] = all->texture[v->tex_num]
						[TEX_H * v->tex.y + v->tex.x];
		y++;
	}
	all->z_buf[x] = v->wall_dist;
}

void	dda_algorithm(t_all *all, t_ver *v)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (v->side_dist.x < v->side_dist.y)
		{
			v->side_dist.x += v->delta_dist.x;
			v->pos.x += v->step.x;
			v->wall = 'x';
		}
		else
		{
			v->side_dist.y += v->delta_dist.y;
			v->pos.y += v->step.y;
			v->wall = 'y';
		}
		if (all->map.map[v->pos.x][v->pos.y] > 0)
			hit = 1;
	}
	get_wall_dist(all, v);
}
