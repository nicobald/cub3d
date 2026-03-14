/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utilisateur <utilisateur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:57:33 by nbaldes           #+#    #+#             */
/*   Updated: 2026/03/05 17:32:35 by utilisateur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void init_env(t_env *env)
{
	env->nb_line = 0;
	return ;
}

int check_args(int argc, char *file)
{
	int		len;
	char 	*extention;

	if (argc != 2 || !file)
	{
		ft_putstr_fd("Error: Cub3D takes exactly one argument (a .cub map file).\n", 2);
		return (1);
	}
	len = ft_strlen(file);
	extention = &file[len - 4];
	if (ft_strnstr(extention, ".cub", len) == NULL || len == 4)
	{
		ft_putstr_fd("Error: Invalid map file. Expected a .cub file (example: map.cub).\n", 2);
		return (1);
	}
	return (0);
}

int check_access(char *file)
{
	struct stat file_data;

	if (access(file, F_OK) == -1)
	{
		ft_putstr_fd("Error: map file not found.\n", 2);
		return (1);
	}
	if (stat(file, &file_data) == -1)
	{
		ft_putstr_fd("Error: Failed to retrieve file information.\n", 2);
		return (1);
	}
	if (S_ISREG(file_data.st_mode) == 0)
	{
		ft_putstr_fd("Error: Expected a regular file.\n", 2);
		return (1);
	}
	if (access(file, R_OK) == -1)
	{
		ft_putstr_fd("Error: cannot read the map file.\n", 2);
		return (1);
	}
	return (0);
}

int count_line_file(char *file, int *nb_line)
{
	int fd;
	char *line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error: Invalid file descriptor.\n", 2);
		return (1);
	}
	while ((line = get_next_line(fd)))
	{
		free(line);
		nb_line++;
	}
	close(fd);
	return (0);
}

int fill_tab_file(char *file, int *nb_line)
{
	int fd;
	char *line;

	(void)nb_line;
	printf("nb line = %d\n", *nb_line);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error: Invalid file descriptor.\n", 2);
		return (1);
	}
	while ((line = get_next_line(fd)))
	{
		free(line);
	}
	close(fd);
	return (0);
}

int	parsing(int argc, char *file, t_env *env)
{
	if (check_args(argc, file) == 1 || check_access(file) == 1)
		return (1);
	if (count_line_file(file, &env->nb_line) == 1 || fill_tab_file(file, &env->nb_line) == 1)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_env env;

	init_env(&env);
	if (parsing(argc, argv[1], &env) == 1)
		return (1);
	return (0);
}