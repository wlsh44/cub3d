#include "cub3d.h"

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
		printf("%s\n", line);

	if (line == NULL)
		return (-1);
	while (line[i] == '\t')
	{
		j = 0;
		while (j < 4)
			all->map.tmp[all->map.y][j++] = ' ';
		i++;
	}
	while (line[i] != 0)
	{
		all->map.tmp[all->map.y][i] = line[i];
		i++;
	}
	if (all->map.x < i)
		all->map.x = i;
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

void parse(t_all *all, char *file)
{
	int fd;
	int res;
	char *line;

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
	close(fd);
	map_parse(all);
}