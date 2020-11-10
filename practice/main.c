#include <stdio.h>
#include <mlx.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>

#define TILE_SIZE 32
#define MAP_NUM_ROWS 11
#define MAP_NUM_COLS 15
#define Y 1080
#define X 720

#define W 13
#define A 0
#define S 1
#define D 2
#define ESC 53
#define UPPER 126
#define DOWN 125
#define LEFT_ARROW 123
#define RIGHT_ARROW 124
#define ROTATE 12
#define SPEED 1.0
#define TURN 5

typedef struct t_map {
	int grid[11][15];
	double x_ratio;
	double y_ratio;
} t_map;

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;
typedef struct s_pos {
	double x;
	double y;
} t_pos;

typedef struct s_player {
	double x;
	double y;
	double rotation_angle;
	double r;
} t_player;


typedef struct s_mlx {
	void *mlx;
	void *mlx_win;
	t_data img;
	t_player player;
	t_map m;
} t_mlx;


void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

double get_radian(int num) {
	return num * (M_PI / 180);
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
	m->x_ratio = X / MAP_NUM_ROWS;
	m->y_ratio = Y / MAP_NUM_COLS;
}

int closed(t_mlx *mlx) {
	mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	free(mlx);
	exit(0);
	return (0);
}

void move(t_player *player, int c) {
	//printf("x dif: %f\n", sin(get_radian(player->rotation_angle) * c) * player->r * SPEED);
	player->x += cos(get_radian(player->rotation_angle)) * c * player->r * SPEED;
	player->y += sin(get_radian(player->rotation_angle)) * c * player->r * SPEED;
}

void side_move(t_player *player, int c) {
	//printf("x dif: %f\n", sin(get_radian(player->rotation_angle) * c) * player->r * SPEED);

	player->x -= sin(get_radian(player->rotation_angle)) * c * player->r * SPEED;
	player->y += cos(get_radian(player->rotation_angle)) * c * player->r * SPEED;

}

void turn(t_mlx *mlx, char c) {
	
}

int key_press(int keycode, t_mlx *mlx) {
	//printf("%d\n", keycode);
	printf("%d\n", mlx->player.rotation_angle);

	if (keycode == W) {
		// mlx->player.walk_direction = 1;
		move(&mlx->player, 1);
	}
	else if (keycode == S)
		// mlx->player->player.walk_direction = -1;
	 	move(&mlx->player, -1);
	else if (keycode == D)
		// mlx->player->player.turn_direction = 1;
		side_move(&mlx->player, -1);
	else if (keycode == A)
		// mlx->player->player.turn_direction = -1;
		side_move(&mlx->player, 1);
	else if (keycode == RIGHT_ARROW) 
		mlx->player.rotation_angle -= TURN;
		//turn(mlx->player, 'r');
	else if (keycode == LEFT_ARROW)
		mlx->player.rotation_angle += TURN;
	// 	turn(mlx->player, 'l');
	else if (keycode == ESC)
		closed(mlx);
	else if (keycode == ROTATE)
		mlx->player.rotation_angle += 90;
	return (0);
}

// int key_released(int keycode, t_mlx *mlx) {
// 	//printf("%d\n", keycode);
// 	//printf("rotation angle: %f\n", mlx->player.rotation_angle);
// 	if (keycode == W) {
// 		//move(mlx, );
// 	}
// 	else if (keycode == S)
// 		move(mlx, 's');
// 	else if (keycode == D)	
// 		move(mlx, 's');
// 	else if (keycode == A)
// 		move(mlx, 's');
// 	// else if (keycode == RIGHT_ARROW)
// 	// else if (keycode == LEFT_ARROW)
// 	else if (keycode == ESC)
// 		closed(mlx);
// 	return (0);
// }

void print_tile(t_map *m, int x, int y, int color, t_data *data) {
	for (int i = x - m->x_ratio; i < x; i++) {
		for (int j = y - m->y_ratio; j < y; j++) {
			my_mlx_pixel_put(data, i, j, color);
		}
	}
}

void render(t_map *m, t_data *data) {
	for (int x = 1; x <= MAP_NUM_ROWS; x++) {
		for (int y = 1; y <= MAP_NUM_COLS; y++) {
			int tile_x = x * m->x_ratio;
			int tile_y = y * m->y_ratio;
			int tile_color = m->grid[x - 1][y - 1] == 1 ? 0x111111 : 0xffffff;

			print_tile(m, tile_y, tile_x, tile_color, data);
			//printf("%d\n", i+j);
		}
	}
}

void init_player(t_player *player) {
	player->x = 360;
	player->y = 540;
	player->rotation_angle = 10;
	player->r = 10;
}

void render_player(t_player *player, t_data *data) {
	for (double theta = 0; theta < 180; theta += 0.1) {
		for (double y = player->y - player->r * sin(get_radian(theta)); y < player->y + player->r * sin(get_radian(theta)); y += 0.1) {
			my_mlx_pixel_put(data, y, player->x + player->r * (1 - cos(get_radian(theta))), 0x00BFFF);
		}
	}
}

int loop(t_mlx *mlx) {
	//render(&mlx->m, &mlx->img);
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
	mlx->mlx_win = mlx_new_window(mlx->mlx, Y, X, "test");
	mlx->img.img = mlx_new_image(mlx->mlx, Y, X);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bits_per_pixel, &mlx->img.line_length, &mlx->img.endian);
	mlx_hook(mlx->mlx_win, 2, 1L<<0, key_press, mlx);	
	//mlx_hook(mlx->mlx_win, 3, 1L<<1, key_released, mlx);
	mlx_loop_hook(mlx->mlx, loop, mlx);
	//
	mlx_loop(mlx->mlx);
}