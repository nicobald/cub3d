/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 00:38:05 by utilisateur       #+#    #+#             */
/*   Updated: 2026/03/18 17:49:17 by nbaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	count_line_file(char *file, int *nb_line)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error: Invalid file descriptor.\n", 2);
		return (1);
	}
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		(*nb_line)++;
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

int	fill_tab_file(char *file, int nb_line, char ***tab)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	if (alloc_tab(tab, nb_line) == 1)
		return (1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error: Invalid file descriptor.\n", 2);
		return (1);
	}
	line = get_next_line(fd);
	while (line)
	{
		(*tab)[i] = ft_strdup(line);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

void	parse_text(int *type, t_count *count, int nb_line)
{
	int	i;

	i = 0;
	while (i < (nb_line))
	{
		// printf("type[%d] = %d\n", i, type[i]);
		if (type[i] == NO)
			count->no_count++;
		if (type[i] == SO)
			count->so_count++;
		if (type[i] == WE)
			count->we_count++;
		if (type[i] == EA)
			count->ea_count++;
		if (type[i] == F)
			count->f_count++;
		if (type[i] == C)
			count->c_count++;
		if (type[i] == STR)
			count->str_count++;
		i++;
	}
	return ;
}

int	parse_file(t_env *env, char ***text, char ***map)
{
	int	i;

	i = 0;
	env->type = malloc(sizeof(int) * (env->nb_line + 1));
	if (!env->type)
		return (1);
	env->type[env->nb_line] = 0;
	while (env->tab[i])
	{
		env->type[i] = parse_type(env->tab[i]);
		// printf("la ligne %d est de type %d elle contiens %s", i, env->type[i], env->tab[i]);
		i++;
	}
	if (error_file(env, text, map) == 1)
		return (1);
	free_tab(&env->tab);
	free(env->type);
	return (0);
}
