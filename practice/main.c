#include <stdio.h>
#include <mlx.h>
#include <math.h>
#include <unistd.h>

#define TILE_SIZE 32
#define MAP_NUM_ROWS 11
#define MAP_NUM_COLS 15

#define FRONT 13
#define BACK 1
#define LEFT 0
#define RIGHT 2
#define ESC 53
#define UPPER 126
#define DOWN 125
#define LEFT_ARROW 123
#define RIGHT_ARROW 124

typedef struct t_map {
	int grid[11][15];
} map;

typedef struct s_mlx {
	void *mlx;
	void *mlx_win;
} t_mlx;

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

typedef struct s_vector {
	int x;
	int y;
} t_vector;

typedef struct s_player{
	t_vector vec;
	int radius;
	int turn_direction;
	int walk_direction;
	double rotation_angle;
	double move_speed;
	double rotation_speed;	
}	t_player;

void init_player (t_player *player) {
	player->vec.x = 240;
	player->vec.y = 176;
	player->radius = 3;
	player->turn_direction = 0;
	player->walk_direction = 0;
	player->rotation_angle = 0;
	player->move_speed = 2.0;
	player->rotation_speed = 2 * (M_PI / 180);
}

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

double get_radian(int num) {
	return num * (M_PI / 180);
}

void render_player(t_player *player, t_data *data) {
	for (double theta = 0; theta < 180; theta += 0.1) {
		for (double y = player->vec.y - player->radius * sin(get_radian(theta)); y < player->vec.y + player->radius * sin(get_radian(theta)); y += 0.1) {
			//printf("%f\n", y);
			//printf("%f\n", (get_radian(theta)));
			my_mlx_pixel_put(data, player->vec.x + player->radius * (1 - cos(get_radian(theta))), y, 0x00BFFF);
		}
	}
}

void init_map(map *m) {
	int map[11][15] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
            {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
            {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 15; j++) {
			m->grid[i][j] = map[i][j];
		}
	}
}

void setup() {
	//init objs

}

int key_press(int keycode, t_mlx *mlx) {
	//printf("%d\n", keycode);
	if (keycode == FRONT)
		write(1,"c", 1);
	return (0);
}

int close(int keycode, t_mlx *mlx) {
	if (keycode == ESC) {
		mlx_destroy_window(mlx->mlx, mlx->mlx_win);
		free(mlx);
		exit(0);
	}
	
	return (0);
}
void print_tile(map *m, int x, int y, int color, t_data *data) {
	for (int i = x - TILE_SIZE; i < x; i++) {
		for (int j = y - TILE_SIZE; j < y; j++) {
			my_mlx_pixel_put(data, i, j, color);
		}
	}
}

void render(map *m, t_data *data) {
	for (int i = 1; i <= MAP_NUM_ROWS; i++) {
		for (int j = 1; j <= MAP_NUM_COLS; j++) {
			int tile_x = j * TILE_SIZE;
			int tile_y = i * TILE_SIZE;
			int tile_color = m->grid[i - 1][j - 1] == 1 ? 0x111111 : 0xffffff;

			print_tile(m, tile_x, tile_y, tile_color, data);
			//printf("%d\n", i+j);
		}
	}
}

void update() {
	//update objs before render the next frame
}

void draw() {
	//render objs by frame
	update();
}


int main() {
	t_mlx *mlx;
	t_data img;
	t_data img2;
	map m;
	t_player player;
	init_map(&m);
	init_player(&player);
	printf("x: %d y: %d\n", player.vec.x, player.vec.y);
	printf("speed: %f\n",player.move_speed);
	printf("r: %d\n",player.radius);


	// for (int i = 0; i < 11; i++) {
	// 	for (int j = 0; j < 15; j++) {
	// 		printf("%d ", m.grid[i][j]);
	// 	}
	// 	printf("\n");
	// }

	mlx = (t_mlx*)malloc(sizeof(t_mlx));
	mlx->mlx = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx, 500, 500, "test");
	img.img = mlx_new_image(mlx->mlx, 500, 500);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	//img2.img = mlx_new_image(mlx, 300, 300);
	//img2.addr = mlx_get_data_addr(img2.img, &img2.bits_per_pixel, &img2.line_length, &img2.endian);
	render(&m, &img);
	render_player(&player, &img);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, img.img, 0, 0);
	mlx_hook(mlx->mlx_win, 2, 1L<<0, key_press, mlx);	
	mlx_loop(mlx->mlx);
}