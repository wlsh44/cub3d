#include "cub3d.h"

char	*error(char *save)
{
	free(save);
	return (NULL);
}

int		newline_check(char *save, int read_size)
{
	int	i;

	i = 0;
	if (save == NULL)
		return (0);
	if (read_size == 0)
		return (1);
	while (save[i] != '\0')
	{
		if (save[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*buf_join(char *save, char *buf)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	while (save != NULL && save[i] != '\0')
		i++;
	while (buf[j] != '\0')
		j++;
	if (!(new = malloc(sizeof(char) * (i + j + 1))))
		return (error(save));
	i = 0;
	j = 0;
	while (save != NULL && save[i] != '\0')
		new[i++] = save[j++];
	j = 0;
	while (buf[j] != '\0')
		new[i++] = buf[j++];
	new[i] = '\0';
	if (save != NULL)
		free(save);
	return (new);
}

char	*save_trim(char *save)
{
	int		i;
	int		j;
	char	*trimmed;

	i = 0;
	j = 0;
	while (save[i] != '\n' && save[i] != '\0')
		i++;
	while (save[i++] != '\0')
		j++;
	if (!(trimmed = malloc(sizeof(char) * j + 1)))
		return (error(save));
	i = 0;
	j = 0;
	while (save[i] != '\n' && save[i] != '\0')
		i++;
	if (save[i] == '\0')
		i--;
	i++;
	while (save[i] != '\0')
		trimmed[j++] = save[i++];
	trimmed[j] = '\0';
	free(save);
	return (trimmed);
}

char	*get_line(char *save)
{
	int		i;
	char	*line;

	i = 0;
	while (save[i] != '\n' && save[i] != '\0')
		i++;
	if (!(line = malloc(sizeof(char) * i + 1)))
		return (error(save));
	i = 0;
	while (save[i] != '\n' && save[i] != '\0')
	{
		line[i] = save[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}
