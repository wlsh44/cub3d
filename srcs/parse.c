#include "../includes/cub3d.h"

int		get_next_line(int fd, char **line)
{
	int			read_size;
	char		buf[4096];
	static char	*save = NULL;

	if (line == NULL || fd < 0)
		return (-3);
	*line = NULL;
	read_size = 1;
	while (!(newline_check(save, read_size)))
	{
		if ((read_size = read(fd, buf, 4095)) == -1)
			return (-3);
		buf[read_size] = '\0';
		if ((save = buf_join(save, buf)) == NULL)
			return (-3);
	}
	if ((*line = get_line(save)) == NULL)
		return (-3);
	if (read_size == 0)
		free(save);
	if (read_size == 0)
		return (0);
	if ((save = save_trim(save)) == NULL)
		return (-3);
	return (1);
}

void print_error(int errno)
{
	printf("error\n");
	exit(0);
}

int load_image(t_all *all, int *texture, char *path, t_img *img) {
    int x;
    int y;

    y = 0;
    img->img = mlx_xpm_file_to_image(all->mlx, path, &img->x, &img->y);
	if (img->img == NULL)
		return (-1);
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
	return (0);
}

int get_texture(t_all *all, char *line, int i)
{
	t_img img;

	return (load_image(all, all->texture[i], line, &img));
}

int skip_blank_line(char *line)
{
	if (line[0] == 0)
		return (1);
	return (0);
}

int get_map(t_all *all, char *line)
{
	int i;
	int j;

	i = 0;
		//printf("%s\n", line);
	j = 0;
	if (line == NULL)
		return (-1);
	while (line[i] == '\t')
	{
		all->map.tmp[all->map.y][j++] = ' ';
		while (j % 4 != 0)
			all->map.tmp[all->map.y][j++] = ' ';
		i++;
	}
	while (line[i] != 0)
	{
		all->map.tmp[all->map.y][j] = line[i];
		i++;
		j++;
	}
	//while (j < all->map.x)
	all->map.tmp[all->map.y][j] = 0;
	if (all->map.x < j)
		all->map.x = j;
	all->map.y++;
	return (0);
}

int get_win(t_all *all, char *line)
{
return (0);
}

int get_color(t_all *all, char *line, int i)
{
return (0);
}

int parse_line(t_all *all, char *line)
{
	int i;
	int errno;

	i = 0;
	errno = 0;
	if (skip_blank_line(line))
		return (0);
	if (line[0] == 'R' && line[1] == ' ')
		errno = get_win(all, line + 2);
	else if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		errno = get_texture(all, line + 3, 0);
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		errno = get_texture(all, line + 3, 1);
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		errno = get_texture(all, line + 3, 2);
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		errno = get_texture(all, line + 3, 3);
	else if (line[0] == 'F' && line[1] == ' ' && line[2] == '.')
		errno = get_texture(all, line + 2, 4);
	else if (line[0] == 'F' && line[1] == ' ')
		errno = get_color(all, line + 2, 4);
	else if (line[0] == 'C' && line[1] == ' ' && line[2] == '.')
		errno = get_texture(all, line + 2, 5);
	else if (line[0] == 'C' && line[1] == ' ')
		errno = get_color(all, line + 2, 5);
	else if (line[0] == 'S' && line[1] == ' ')
		errno = get_texture(all, line + 2, 6);
	else
		return(get_map(all, line));
	if (errno != 0)
		print_error(errno);
	return (errno);
}

void map_alloc(t_all *all)
{
	int y;
	int x;
	y = 0;
	all->map.map = malloc(sizeof(int *) * all->map.y);
	while (y < all->map.y)
	{
		x = 0;
		all->map.map[y] = malloc(sizeof(int) * all->map.x);
		while (x < all->map.x)
		{
			if (all->map.tmp[y][x] == ' ' || all->map.tmp[y][x] == '1')
				all->map.map[y][x] = 1;
			else
				all->map.map[y][x] = 0;
			x++;
		}
		y++;
	}
}

int check_srround(t_all *all, int y, int x)
{
	if (y == 0 && all->map.tmp[y + 1][x] == '0')
			return (0);
	else if (y == all->map.y - 1 && all->map.tmp[y - 1][x] == '0')
			return (0);
	else if (all->map.tmp[y + 1][x] == '0' ||
			all->map.tmp[y - 1][x] == '0')
			return (0);
	//printf("in\n");
	if (x == 0 && all->map.tmp[y][x + 1] == '0')
			return (0);
	else if (x == all->map.x - 1 && all->map.tmp[y][x - 1] == '0')
			return (0);
	else if (all->map.tmp[y][x + 1] == '0' ||
			all->map.tmp[y][x - 1] == '0')
			return (0);
	return (1);
}

int check_map(t_all *all)
{
	int flag;
	int i;
	int j;

	i = 0;
	flag = 0;
	//printf("%d %d\n", all->map.y, all->map.x);
	while (i < all->map.y)
	{
		j = 0;
		//printf("%d", i);
		while (j < all->map.x)
		{
	//		printf(" %d\n", j);
			if (all->map.tmp[i][j] == 'W' || all->map.tmp[i][j] == 'N'
				|| all->map.tmp[i][j] == 'S' || all->map.tmp[i][j] == 'E')
				{
					all->pos.y = i;
					all->pos.x = j;
					flag = 1;
				}
			else if (all->map.tmp[i][j] == ' ' && !check_srround(all, i, j))
					return (-1);
			else if (all->map.tmp[i][j] == '2')
			{
				all->s_pos[all->sprite_num].y = i;
				all->s_pos[all->sprite_num++].x = j;
			}
			j++;
		}
		i++;
	}
	if (flag == 0)
		return (-1);
	return (0);
}

int map_parse(t_all *all)
{
	if (check_map(all))
		return (-1);
	map_alloc(all);
	// for (int i = 0; i < all->map.y; i++) 
	// {
	// 	for (int j = 0; j < all->map.x; j++)
	// 		printf("%d", all->map.map[i][j]);
	// 	printf("\n");
	// }
	return (0);
}

void parse(t_all *all, char *file)
{
	int fd;
	int res;
	char *line;
	double tmp;

	res = 1;
	if ((fd = open(file, O_RDONLY)) == -1)
		print_error(1);
	while (res == 1)
	{
		res = get_next_line(fd, &line);
		//printf("%s\n", line);
		if (parse_line(all, line) == -1)
			res = -1;
		free(line);
	}
	//printf("asdf\n");
	close(fd);
	// 	for (int i = 0; i < all->map.y; i++) 
	// {
	// 	for (int j = 0; j < all->map.x; j++)
	// 		printf("%c", all->map.tmp[i][j]);
	// 	printf("\n");
	// }
	map_parse(all);
	tmp = all->pos.x;
	all->pos.x = all->pos.y;
	all->pos.y = tmp;
}