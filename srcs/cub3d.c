#include "../includes/cub3d.h"

void load_image(t_all *all, int *texture, char *path, t_img *img) {
    int x;
    int y;

    y = 0;
    img->img = mlx_xpm_file_to_image(all->mlx, path, &img->x, &img->y);
    img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size, &img->endian);
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
}

void load_texture(t_all *all) {
    t_img img;

    load_image(all, all->texture[0], "./textures/eagle.xpm", &img);
	load_image(all, all->texture[1], "./textures/redbrick.xpm", &img);
	load_image(all, all->texture[2], "./textures/purplestone.xpm", &img);
	load_image(all, all->texture[3], "./textures/greystone.xpm", &img);
	load_image(all, all->texture[4], "./textures/bluestone.xpm", &img);
	load_image(all, all->texture[5], "./textures/mossy.xpm", &img);
	load_image(all, all->texture[6], "./textures/wood.xpm", &img);
	load_image(all, all->texture[7], "textures/colorstone.xpm", &img);
	load_image(all, all->texture[8], "textures/barrel.xpm", &img);
	load_image(all, all->texture[9], "textures/pillar.xpm", &img);
	load_image(all, all->texture[10], "textures/greenlight.xpm", &img);
}

void	draw(t_all *all)
{
    int x;
    int y;

    y = 0;
	while (y < all->win.y)
	{
        //printf("as\n");
        x = 0;
		while (x < all->win.x)
		{
            //printf("%d\n", all->buf[y][x]);
			all->img.data[y * all->win.x + x] = all->buf[y][x];
            x++;
        }
        y++;
	}
	mlx_put_image_to_window(all->mlx, all->win.win, all->img.img, 0, 0);
}

int c;

int main_loop(t_all *all)
{
    //printf("%f\n", all->pos.x);
    ray_casting(all);
    draw(all);
    // if (c++ == 0)
    // {
    //     for (int y = 0; y < all->img.y; y++) {
    //         for (int x = 0; x < all->img.x; x++) {
    //             printf("%d ", all->buf[y][x]);
    //         }
    //         printf("\n");
    //     }
    //     // for (int i = 0; i < 5; i++)
    //     // printf("%d\n", all->texture[5][i]);
    // }
    return (0);
}

void cubed(t_all *all) {
    all->mlx = mlx_init();
    load_texture(all);


    
    all->win.win = mlx_new_window(all->mlx, all->img.x, all->img.y, "cub3d");
    all->img.img = mlx_new_image(all->mlx, all->img.x, all->img.y);
    all->img.data = (int *)mlx_get_data_addr(all->img.img, &all->img.bpp, &all->img.size, &all->img.endian);
    	//printf("%d\n", all->img.bpp);

    mlx_loop_hook(all->mlx, &main_loop, all);
    mlx_hook(all->win.win, KEY_PRESS, 0, &key_press, all);
    mlx_loop(all->mlx);
}

void mem_alloc(t_all *all) {
    int x;
    int y;

    y = 0;
    all->buf = malloc(sizeof(int *) * all->img.y);
    while (y < all->img.y) {
        x = 0;
        all->buf[y] = malloc(sizeof(int) * all->win.x);
        while (x < all->win.x)
        {
            all->buf[y][x++] = 0;
        }
        y++;
    }

    y = 0;
    all->texture = malloc(sizeof(int *) * texNum);
    while (y < texNum) {
        x = 0;
        all->texture[y] = malloc(sizeof(int) * (texHeight * texWidth));
        while (x < texWidth * texHeight) {
            all->texture[y][x++] = 0;
        }
        y++;
    }
    y = 0;
    all->map.map = malloc(sizeof(int *) * all->map.y);
    while (y < all->map.y) {
        x = 0;
        all->map.map[y] = malloc(sizeof(int) * all->map.x);
        while (x < all->map.x) {
            all->map.map[y][x++] = 0;
        }
        y++;
    }
}

int	worldMap[24][24] =
									{
										{8,8,8,8,8,8,8,8,8,8,8,4,4,6,4,4,6,4,6,4,4,4,6,4},
										{8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
										{8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,6},
										{8,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
										{8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
										{8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,6,6,6,0,6,4,6},
										{8,8,8,8,0,8,8,8,8,8,8,4,4,4,4,4,4,6,0,0,0,0,0,6},
										{7,7,7,7,0,7,7,7,7,0,8,0,8,0,8,0,8,4,0,4,0,6,0,6},
										{7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,0,0,0,0,0,6},
										{7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,0,0,0,0,4},
										{7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,6,0,6,0,6},
										{7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,4,6,0,6,6,6},
										{7,7,7,7,0,7,7,7,7,8,8,4,0,6,8,4,8,3,3,3,0,3,3,3},
										{2,2,2,2,0,2,2,2,2,4,6,4,0,0,6,0,6,3,0,0,0,0,0,3},
										{2,2,0,0,0,0,0,2,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
										{2,0,0,0,0,0,0,0,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
										{1,0,0,0,0,0,0,0,1,4,4,4,4,4,6,0,6,3,3,0,0,0,3,3},
										{2,0,0,0,0,0,0,0,2,2,2,1,2,2,2,6,6,0,0,5,0,5,0,5},
										{2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
										{2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
										{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
										{2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
										{2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
										{2,2,2,2,1,2,2,2,2,2,2,1,2,2,2,5,5,5,5,5,5,5,5,5}
									};


void init() {
    t_all all;

    all.pos.x = 22;
    all.pos.y = 11.5;
    all.dir.x = -1.0;
    all.dir.y = 0;
    all.buf = NULL;
    all.plane.x = 0;
    all.plane.y = 0.66;
    all.map.x = 24;
    all.map.y = 24;
    all.win.x = 640;
    all.win.y = 480;
    all.img.x = all.win.x;
    all.img.y = all.win.y;
    mem_alloc(&all);

    for (int i = 0; i < 24; i++) {
        for (int j = 0; j < 24; j++) {
            all.map.map[i][j] = worldMap[i][j];
        }
    }
    cubed(&all);
}

int main() {
    init();
}