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

void set_tex_num(t_all *all, t_ver *v)
{
	if (v->step.x == 1 && v->step.y == 1)
	{
		if (v->wall == 'x')
			v->tex_num = 2;//W
		else
			v->tex_num = 1;//S
	}
	else if (v->step.x == 1 && v->step.y == -1)
	{
		if (v->wall == 'x')
			v->tex_num = 2;//W
		else
			v->tex_num = 0;//N
	}
	else if (v->step.x == -1 && v->step.y == 1)
	{
		if (v->wall == 'x')
			v->tex_num = 3;//E
		else
			v->tex_num = 1;//S
	}
	else if (v->step.x == -1 && v->step.y == -1)
	{
		if (v->wall == 'x')
			v->tex_num = 3;//E
		else
			v->tex_num = 0;//N
	}
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
	set_tex_num(all, v);
    //v->tex_num = all->map.map[v->pos.x][v->pos.y] - 1; // ..?
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

    init_add_to_buf(all, v);
    y = v->start;
    while (y < v->end)
    {
        //printf("tex %d\n", v->tex_num);
        v->tex.y = (int)v->tex_pos & (texHeight - 1);
        v->tex_pos += v->ratio;
        all->buf[y][x] = all->texture[v->tex_num][texHeight * v->tex.y + v->tex.x];
        //if (v->wall == 'y')
        y++;
    }
    all->z_buf[x] = v->wall_dist;
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
        //printf("%d %d\n", v->pos.x, v->pos.y);
        if (all->map.map[v->pos.x][v->pos.y] > 0)
             hit = 1;
    }
		//set_tex_num(all, v);
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




///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////




void sort_sprite(t_sprite *sprite, int size)
{
    t_pair tmp;
    int i;
    int j;
    
    i = 0;
    while (i < size)
    {
        j = i;
        while (j < size - 1)
        {
            if (sprite->dist[j] < sprite->dist[j + 1])
            {
                tmp.x = sprite->dist[j];
                tmp.y = sprite->order[j];
                sprite->dist[j] = sprite->dist[j + 1];
                sprite->order[j] = sprite->order[j + 1];
                sprite->dist[j + 1] = tmp.x;
                sprite->order[j + 1] = tmp.y;
            }
            j++;
        }
        i++;
    }
}

void get_sprite_dist(t_all *all, t_sprite *sprite)
{
    int i;

    i = 0;
    sprite->order = malloc(sizeof(int) * all->sprite_num);
    sprite->dist = malloc(sizeof(int) * all->sprite_num);
    while (i < all->sprite_num)
    {
        sprite->order[i] = i;
        sprite->dist[i] = hypot(all->pos.x - all->s_pos[i].x, all->pos.y - all->s_pos[i].y);
        i++;
    }
    sort_sprite(sprite, all->sprite_num);

}

void get_pos_x(t_all *all, t_sprite *s, int i)
{
    t_pos pos;
    double inv_det;

    pos.x = all->s_pos[s->order[i]].x - all->pos.x;
    pos.y = all->s_pos[s->order[i]].y - all->pos.y;
    inv_det = 1.0 / (all->plane.x * all->dir.y - all->dir.x * all->plane.y);
    s->transform.x = inv_det * (all->dir.y * pos.x - all->dir.x * pos.y);
    s->transform.y = inv_det * (-all->plane.y * pos.x + all->plane.x * pos.y);
    s->pos_x = (int)((all->win.x / 2) * (1 + s->transform.x / s->transform.y));
}

void init_sprite(t_all *all, t_sprite *s, int i)
{
    int tmp;
    
    get_pos_x(all, s, i);
	//int vMoveScreen = (int)(vMove / transformY);
    s->height = (int)fabs(all->win.y / s->transform.y) / 1; // 1 테스트 해보기
    tmp = -s->height / 2 + all->win.y / 2; // + movescreen
    s->start.y = tmp < 0 ? 0 : tmp;
    tmp = s->height / 2 + all->win.y / 2; //  + movescreen
    s->end.y = tmp >= all->win.y ? all->win.y - 1 : tmp;
    s->width = (int)fabs(all->win.y / s->transform.y); // /udiv
    tmp = -s->width / 2 + s->pos_x;
    s->start.x = tmp < 0 ? 0 : tmp;
    tmp = s->width / 2 + s->pos_x;
    s->end.x = tmp >= all->win.x ? all->win.x - 1 : tmp;
}

void add_to_buf_spr(t_all *all, t_sprite *s)
{
    int x;
    int y;
    int d;
    int color;

    x = s->start.x;
    while (x < s->end.x)
    {
        y = s->start.y;
        s->tex.x = (int)((256 * (x - (-s->width / 2 + s->pos_x)) * texWidth / s->width) / 256);
        if (s->transform.y > 0 && x > 0 && x < all->win.x && s->transform.y < all->z_buf[x])
            while (y < s->end.y)
            {
                d = y * 256 - all->win.y * 128 + s->height * 128;
                s->tex.y = ((d * texHeight) / s->height) / 256;
                color = all->texture[6][texWidth * s->tex.y + s->tex.x];
                if ((color & 0x00FFFFFF) != 0)
                    all->buf[y][x] = color;
                y++; 
            }
        x++;
    }
}

void end_spr(t_sprite *s)
{
	free(s->order);
	free(s->dist);
}

void sprite(t_all *all)
{
    int i;
    t_sprite sprite;

    get_sprite_dist(all, &sprite);
    i = 0;
    while (i < all->sprite_num)
    {
        init_sprite(all, &sprite, i);
        add_to_buf_spr(all, &sprite);
        i++;
    }
	end_spr(&sprite);
}

void ray_casting(t_all *all) 
{
    horizon(all);
    vertical(all);
    sprite(all);
}