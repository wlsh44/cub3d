#include "../includes/cub3d.h"

void get_camera_dir(t_all *all, t_dir *dir0, t_dir *dir1)
{
    dir0->x = all->dir.x - all->plane.x;
    dir0->y = all->dir.y - all->plane.y;
    dir1->x = all->dir.x + all->plane.x;
    dir1->y = all->dir.y + all->plane.y;
}

void init_coordinates(t_all *all, t_pos *d, t_pos *floor, int y)
{
    t_dir dir0;
    t_dir dir1;
    int dz;
    double z;
    double row_dist;

    get_camera_dir(all, &dir0, &dir1);
    dz = y - all->win.y / 2;
    z = 0.5 * all->win.y;
    row_dist = z / dz;
    d->x = row_dist * (dir1.x - dir0.x) / all->win.x;
    d->y = row_dist * (dir1.y - dir0.y) / all->win.x;
    floor->x = all->pos.x + row_dist * dir0.x;
    floor->y = all->pos.y + row_dist * dir0.y;
}

void add_to_buf_hor(t_all *all, t_pos *d, t_pos *floor, int y)
{
    int x;
    int color;
    t_pair tex;

    x = 0;
    while (x < all->win.x)
    {
        tex.x = (int)(texWidth * (floor->x - (int)(floor->x))) & (texWidth - 1);
        tex.y = (int)(texHeight * (floor->y - (int)(floor->y))) & (texHeight - 1);
        floor->x += d->x;
        floor->y += d->y;
        color = all->texture[FLOOR][texWidth * tex.y + tex.x];
        all->buf[y][x] = color;
        color = all->texture[CEILING][texWidth * tex.y + tex.x];
        //add_to_buff("color: %x\n", color);
        all->buf[all->win.y - y - 1][x] = color;
        x++;
    }
}

void horizon(t_all *all)
{
    int y;
    int color;
    t_pos d;
    t_pos floor;

    y = all->win.y / 2 + 1;
    while (y < all->win.y)
    {
        init_coordinates(all, &d, &floor, y);
        add_to_buf_hor(all, &d, &floor, y);
        y++;
    }
}

void get_dir(t_all *all, t_ver *v, int x)
{
    double camera;

    camera = 2 * x / (double)(all->win.x) - 1;
    v->dir.x = all->dir.x + all->plane.x * camera;
    v->dir.y = all->dir.y + all->plane.y * camera;
}

void init_dda(t_all *all, t_ver *v)
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

void get_wall_dist(t_all *all, t_ver *v)
{
    if (v->wall == 'x')
        v->wall_dist = (v->pos.x - all->pos.x + (1 - v->step.x) / 2) / v->dir.x;
    else
        v->wall_dist = (v->pos.y - all->pos.y + (1 - v->step.y) / 2) / v->dir.y;
}

void init_add_to_buf(t_all *all, t_ver *v)
{
    int tmp;
    double wall_x;

    v->line_height = (int)(all->win.y / v->wall_dist);
    tmp = -v->line_height / 2 + all->win.y / 2;
    v->start = tmp < 0 ? 0 : tmp;
    tmp = v->line_height / 2 + all->win.y / 2;
    v->end = tmp >= all->win.y ? all->win.y - 1 : tmp;
    v->tex_num = all->map.map[v->pos.x][v->pos.y] - 1; // ..?
    wall_x = v->wall == 'x' ? all->pos.y + v->wall_dist * v->dir.y : all->pos.x + v->wall_dist * v->dir.x;
    wall_x -= floor(wall_x);
    v->tex.x = (int)(wall_x * (double)texWidth);
    if (v->wall == 'x' && v->dir.x > 0)
        v->tex.x = texWidth - v->tex.x - 1;
    else if (v->wall == 'y' && v->dir.y < 0)
        v->tex.x = texWidth - v->tex.x - 1;
    v->ratio = 1.0 * texHeight / v->line_height;
    v->tex_pos = (v->start - all->win.y / 2 + v->line_height / 2) * v->ratio;
}

void add_to_buf_ver(t_all *all, t_ver *v, int x)
{
    int y;
    int color;

    init_add_to_buf(all, v);
    y = v->start;
    while (y < v->end)
    {
        //printf("%d\n", v->tex_num);
        v->tex.y = (int)v->tex_pos & (texHeight - 1);
        v->tex_pos += v->ratio;
        all->buf[y][x] = all->texture[v->tex_num][texHeight * v->tex.y + v->tex.x];
        //if (v->wall == 'y')
        y++;
    }
    //all->z_buf[x] = v->wall_dist;
}

void dda_algorithm(t_all *all, t_ver *v)
{
    int hit;

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

void vertical(t_all *all)
{
    int x;
    t_ver v;

    x = 0;
    while (x < all->win.x)
    {
        get_dir(all, &v, x);
        init_dda(all, &v);
        dda_algorithm(all, &v);
        add_to_buf_ver(all, &v, x);
        x++;
    }
}

void ray_casting(t_all *all) 
{
    horizon(all);
    vertical(all);
    //sprite(all);
}