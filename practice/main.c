#include <stdio.h>
#include <mlx.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>

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
} t_map;


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

typedef struct s_mlx {
	void *mlx;
	void *mlx_win;
	t_data img;
	t_player player;
	t_map m;
} t_mlx;

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

void zero_exception(t_vector s, t_vector e, t_data *data) {
	
}

double get_distance(t_vector s, t_vector e) {
	return sqrt((e.x - s.x) * (e.x - s.x) + (e.y - s.y) * (e.y - s.y));
}

void line(t_vector s, t_vector e, t_data *data) {
	int m;
	int new_m;
	int d;
	
	d = get_distance(s, e);
	if (e.x - s.x == 0) {
		if (e.y >= s.y) {
			for (int y = s.y; y < e.y; y++) {
				my_mlx_pixel_put(data, s.x, y, 0x00BFFF);
			}
		} else {
			for (int y = e.y; y < s.y; y++) {
				my_mlx_pixel_put(data, s.x, y, 0x00BFFF);
			}
		}
	}
	else {
		m = (e.y - s.y) / (e.x - s.x);
		for (int x = 0; x < 500; x++) {
			for (int y = 0; y < 500; y++) {
				t_vector tmp;

				tmp.x = x;
				tmp.y = y;
				if (x - s.x != 0 && get_distance(s, tmp) <= d) {
					new_m = (y - s.y) / (x - s.x);
					if (new_m == m) {
						my_mlx_pixel_put(data, x, y, 0x00BFFF);
					}
				}
			}
		}
	}
}

void render_player(t_player *player, t_data *data) {
	t_vector sight;
	
	player->vec.x = cos(player->rotation_angle) * player->walk_direction * player->move_speed;
	sight.x = player->vec.x + cos(player->rotation_angle) * 20;
	sight.y = player->vec.y + sin(player->rotation_angle) * 20;
	for (double theta = 0; theta < 180; theta += 0.1) {
		for (double y = player->vec.y - player->radius * sin(get_radian(theta)); y < player->vec.y + player->radius * sin(get_radian(theta)); y += 0.1) {
			//printf("%f\n", y);
			//printf("%f\n", (get_radian(theta)));
			my_mlx_pixel_put(data, player->vec.x + player->radius * (1 - cos(get_radian(theta))), y, 0x00BFFF);
		}
	}

	line(player->vec, sight, data);

}

void init_map(t_map *m) {
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
int closed(t_mlx *mlx) {
	mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	free(mlx);
	exit(0);
	return (0);
}

int key_press(int keycode, t_mlx *mlx) {
	printf("%d\n", keycode);
	if (keycode == FRONT) {
		mlx->player.walk_direction = 1;
	}
	else if (keycode == BACK)
		mlx->player.walk_direction = -1;
	else if (keycode == RIGHT)
		mlx->player.turn_direction = 1;
	else if (keycode == LEFT)
		mlx->player.turn_direction = -1;
	else if (keycode == RIGHT_ARROW) 
		mlx->player.rotation_angle += 1;
	else if (keycode == LEFT_ARROW)
		mlx->player.rotation_angle -= 0.1;
	else if (keycode == ESC)
		closed(mlx);

	return (0);
}

int key_released(int keycode, t_mlx *mlx) {
	printf("%d\n", keycode);
	printf("rotation angle: %f\n", mlx->player.rotation_angle);
	if (keycode == FRONT) {
		mlx->player.walk_direction = 0;
	}
	else if (keycode == BACK)
		mlx->player.walk_direction = 0;
	else if (keycode == RIGHT)	
		mlx->player.turn_direction = 0;
	else if (keycode == LEFT)
		mlx->player.turn_direction = 0;
	// else if (keycode == RIGHT_ARROW)
	// else if (keycode == LEFT_ARROW)
	else if (keycode == ESC)
		closed(mlx);

	return (0);
}

void print_tile(t_map *m, int x, int y, int color, t_data *data) {
	for (int i = x - TILE_SIZE; i < x; i++) {
		for (int j = y - TILE_SIZE; j < y; j++) {
			my_mlx_pixel_put(data, i, j, color);
		}
	}
}

void render(t_map *m, t_data *data) {
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

int loop(t_mlx *mlx) {
	render(&mlx->m, &mlx->img);
	render_player(&mlx->player, &mlx->img);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img.img, 0, 0);
	return (0);
}

int main() {
	t_mlx *mlx;
	//t_data img;
	mlx = malloc(sizeof(t_mlx));
	init_map(&mlx->m);
	init_player(&mlx->player);

	mlx->mlx = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx, 500, 500, "test");
	mlx->img.img = mlx_new_image(mlx->mlx, 500, 500);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bits_per_pixel, &mlx->img.line_length, &mlx->img.endian);
	mlx_hook(mlx->mlx_win, 2, 1L<<0, key_press, mlx);	
	mlx_hook(mlx->mlx_win, 3, 1L<<1, key_released, mlx);
	mlx_loop_hook(mlx->mlx, loop, mlx);
	//
	mlx_loop(mlx->mlx);
}