/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utilisateur <utilisateur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 00:38:05 by utilisateur       #+#    #+#             */
/*   Updated: 2026/03/16 00:34:14 by utilisateur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
		(*nb_line)++;
	}
	close(fd);
	return (0);
}

int fill_tab_file(char *file, int nb_line, char ***tab)
{
	int fd;
	char *line;
	int i;
	
	i = 0;
	if (alloc_tab(tab, nb_line) == 1)
		return (1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error: Invalid file descriptor.\n", 2);
		return (1);
	}
	while ((line = get_next_line(fd)))
	{
		(*tab)[i] = ft_strdup(line);
		free(line);
		i++;
	}
	close(fd);
	return (0);
}

int parse_file(t_env *env, char ***text, char ***map)
{
	int i;

    i = 0;
    env->type = malloc(sizeof(int) * (env->nb_line + 1));
	if (!env->type)
		 return (1);
	env->type[env->nb_line] = 0;
	while (env->tab[i])
	{
        env->type[i] = parse_type(env->tab[i]);
		printf("la ligne %d est de type %d elle contiens %s", i, env->type[i], env->tab[i]);
		i++;
	}
	error_file(env, text, map);
	free_tab(&env->tab);
	free(env->type);
	return (0);
}
