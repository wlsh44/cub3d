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
    dz = y - height / 2;
    z = 0.5 * height;
    row_dist = z / dz;
    d->x = row_dist * (dir1.x - dir0.x) / width;
    d->y = row_dist * (dir1.y - dir0.y) / width;
    floor->x = all->pos.x + row_dist * dir0.x;
    floor->y = all->pos.y + row_dist * dir0.y;
}

void print_hor(t_all *all, t_pos *d, t_pos *floor, int y)
{
    int x;
    int color;
    t_pos tex;

    x = 0;
    while (x < width)
    {
        tex.x = (int)(texWidth * (floor->x - (int)(floor->x))) & (texWidth - 1);
        tex.y = (int)(texHeight * (floor->y - (int)(floor->y))) & (texHeight - 1);
        floor->x += d->x;
        floor->y += d->y;
        color = all->texture[FLOOR][texWidth * (int)tex.y + (int)tex.x];
        all->buf[y][x] = color;
        color = all->texture[CEILING][texWidth * (int)tex.y + (int)tex.x];
        //printf("color: %x\n", color);
        all->buf[height - y - 1][x] = color;
        x++;
    }
}

void horizon(t_all *all)
{
    int y;
    int color;
    t_pos d;
    t_pos floor;

    y = height / 2 + 1;
    while (y < height)
    {
        init_coordinates(all, &d, &floor, y);
        print_hor(all, &d, &floor, y);
        y++;
    }
}

void ray_casting(t_all *all) 
{
    horizon(all);
    //vertical(all);
    //sprite(all);
}