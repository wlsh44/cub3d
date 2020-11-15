#include "../includes/cub3d.h"

void move(int key, t_all *all) {
    //printf("%d\n", (int)(all->pos.x + all->dir.x * MOVE_SPEED));
    if (key == W)
    {
        if (!all->map.map[(int)(all->pos.x + all->dir.x * MOVE_SPEED)]
            [(int)all->pos.y])
            all->pos.x += all->dir.x * MOVE_SPEED;
        if (!all->map.map[(int)all->pos.x]
            [(int)(all->pos.y + all->dir.y * MOVE_SPEED)])
            all->pos.y += all->dir.y * MOVE_SPEED;
    }
    if (key == S)
    {
        if (!all->map.map[(int)(all->pos.x - all->dir.x * MOVE_SPEED)]
            [(int)all->pos.y])
            all->pos.x -= all->dir.x * MOVE_SPEED;
        if (!all->map.map[(int)all->pos.x]
            [(int)(all->pos.y - all->dir.y * MOVE_SPEED)])
            all->pos.y -= all->dir.y * MOVE_SPEED;
    }
}

//회전행렬 이용한 벡터 회전
void strafe(int key, t_all *all) {
    double tmp;
    
    tmp = all->dir.x;
    if (key == LEFT)
    {
        all->dir.x = all->dir.x * cos(ROT_SPEED) - all->dir.y * sin(ROT_SPEED);
        all->dir.y = tmp * sin(ROT_SPEED) + all->dir.y * cos(ROT_SPEED);
        tmp = all->plane.x;
        all->plane.x = all->plane.x * cos(ROT_SPEED) - all->plane.y * sin(ROT_SPEED);
        all->plane.y = tmp * sin(ROT_SPEED) + all->plane.y * cos(ROT_SPEED);
    }
    if (key == RIGHT)
    {
        all->dir.x = all->dir.x * cos(-ROT_SPEED) - all->dir.y * sin(-ROT_SPEED);
        all->dir.y = tmp * sin(-ROT_SPEED) + all->dir.y * cos(-ROT_SPEED);
        tmp = all->plane.x;
        all->plane.x = all->plane.x * cos(-ROT_SPEED) - all->plane.y * sin(-ROT_SPEED);
        all->plane.y = tmp * sin(-ROT_SPEED) + all->plane.y * cos(-ROT_SPEED);
    }
}

void closed(t_all *all)
{
    mlx_destroy_window(all->mlx, all->win.win);
    free(all->mlx);
    exit(0);
}

int key_press(int key, t_all *all) {
    if (key == W || key == S)
        move(key, all);
    else if (key == LEFT || key == RIGHT)
        strafe(key, all);
    else if (key == ESC)
        closed(all);
    return (0);
}