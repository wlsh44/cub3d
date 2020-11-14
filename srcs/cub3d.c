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
	while (y < height)
	{
        //printf("as\n");
        x = 0;
		while (x < width)
		{
            //printf("%d\n", all->buf[y][x]);
			all->img.data[y * width + x] = all->buf[y][x];
            x++;
        }
        y++;
	}
	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
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

    all->img.x = width;
    all->img.y = height;
    
    all->win = mlx_new_window(all->mlx, all->img.x, all->img.y, "cub3d");
    all->img.img = mlx_new_image(all->mlx, all->img.x, all->img.y);
    all->img.data = (int *)mlx_get_data_addr(all->img.img, &all->img.bpp, &all->img.size, &all->img.endian);
    	//printf("%d\n", all->img.bpp);

    mlx_loop_hook(all->mlx, &main_loop, all);
    mlx_hook(all->win, KEY_PRESS, 0, &key_press, all);
    mlx_loop(all->mlx);
}

void mem_alloc(t_all *all) {
    int x;
    int y;

    y = 0;
    all->buf = malloc(sizeof(int *) * all->img.y);
    while (y < all->img.y) {
        x = 0;
        all->buf[y] = malloc(sizeof(int) * width);
        while (x < width)
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
    all.img.x = 480;
    all.img.y = 640;
    mem_alloc(&all);
    cubed(&all);
}

int main() {
    init();
}