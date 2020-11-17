/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_ver2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 19:05:05 by jinhkim           #+#    #+#             */
/*   Updated: 2020/11/17 19:05:06 by jinhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_dir(t_all *all, t_ver *v, int x)
{
	double	camera;

	camera = 2 * x / (double)(all->win.x) - 1;
	v->dir.x = all->dir.x + all->plane.x * camera;
	v->dir.y = all->dir.y + all->plane.y * camera;
}

void	init_dda(t_all *all, t_ver *v)
{
	v->pos.x = (int)all->pos.x;
	v->pos.y = (int)all->pos.y;
	v->delta_dist.x = fabs(1 / v->dir.x);
	v->delta_dist.y = fabs(1 / v->dir.y);
	if (v->dir.x < 0)
	{
		v->step.x = -1;
		v->side_dist.x = (all->pos.x - v->pos.x) * v->delta_dist.x;
	}
	else
	{
		v->step.x = 1;
		v->side_dist.x = (v->pos.x + 1.0 - all->pos.x) * v->delta_dist.x;
	}
	if (v->dir.y < 0)
	{
		v->step.y = -1;
		v->side_dist.y = (all->pos.y - v->pos.y) * v->delta_dist.y;
	}
	else
	{
		v->step.y = 1;
		v->side_dist.y = (v->pos.y + 1.0 - all->pos.y) * v->delta_dist.y;
	}
}

void	get_wall_dist(t_all *all, t_ver *v)
{
	if (v->wall == 'x')
		v->wall_dist = (v->pos.x - all->pos.x + (1 - v->step.x) / 2) / v->dir.x;
	else
		v->wall_dist = (v->pos.y - all->pos.y + (1 - v->step.y) / 2) / v->dir.y;
}
