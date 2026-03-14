#include "cub3D.h"

static int	fill_static(int fd, char *buf, char **static_save)
{
	int		byte;
	char	*line;

	byte = 0;
	while (!ft_strchr(*static_save, '\n'))
	{
		byte = read(fd, buf, BUFFER_SIZE);
		if (byte < 0)
			return (-1);
		if (byte == 0)
			break ;
		buf[byte] = '\0';
		line = ft_strjoin(*static_save, buf);
		free(*static_save);
		*static_save = line;
	}
	return (byte);
}

static char	*get_line(char *static_save)
{
	int		i;
	char	*line;
	int		len;

	i = 0;
	while (static_save[i] && static_save[i] != '\n')
		i++;
	if (static_save[i] == '\n')
		len = i + 2;
	else
		len = i + 1;
	line = malloc(len);
	if (!line)
		return (NULL);
	i = -1;
	while (static_save[++i] && static_save[i] != '\n')
		line[i] = static_save[i];
	if (static_save[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*get_rest(char *static_save)
{
	int		i;
	char	*rest;

	i = 0;
	while (static_save[i] && static_save[i] != '\n')
		i++;
	if (static_save[i] == '\n')
		i++;
	rest = ft_strdup(static_save + i);
	free(static_save);
	return (rest);
}

char	*get_next_line(int fd)
{
	char		*buf;
	char		*line;
	int			byte;
	static char	*static_save = NULL;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	buf[BUFFER_SIZE] = '\0';
	if (!static_save)
		static_save = ft_strdup("");
	byte = fill_static(fd, buf, &static_save);
	if (byte < 0 || (byte == 0 && static_save[0] == '\0'))
	{
		free(buf);
		free(static_save);
		static_save = NULL;
		return (NULL);
	}
	free(buf);
	line = get_line(static_save);
	static_save = get_rest(static_save);
	return (line);
}