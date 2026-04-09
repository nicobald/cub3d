/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laudinot <laudinot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 19:52:37 by nbaldes           #+#    #+#             */
/*   Updated: 2026/04/09 13:16:02 by laudinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	error_parse_file(t_count count, int *type, int nb_line)
{
	int	i;

	i = -1;
	if (count.no_count != 1 || count.so_count != 1
		|| count.we_count != 1 || count.ea_count != 1)
	{
		ft_putstr_fd("Error: Missing or duplicate texture definition.\n", 2);
		return (1);
	}
	if (count.f_count != 1 || count.c_count != 1)
	{
		ft_putstr_fd("Error: Missing or duplicate color definition.\n", 2);
		return (1);
	}
	while (++i < nb_line)
	{
		if (type[i] == MAP && type[i + 1] && type[i + 1] != MAP)
		{
			ft_putstr_fd("Error: Error: wrong map format.\n", 2);
			return (1);
		}
	}
	return (0);
}

int	dup_text_map(char **tab, int *type, char ***text, char ***map)
{
	int	nb_text;

	nb_text = 6;
	(*text) = malloc(sizeof(char *) * (nb_text + 1));
	if (!(*text))
		return (1);
	fill_text(type, NO, text, tab);
	fill_text(type, SO, text, tab);
	fill_text(type, WE, text, tab);
	fill_text(type, EA, text, tab);
	fill_text(type, F, text, tab);
	fill_text(type, C, text, tab);
	(*text)[nb_text] = NULL;
	if (fill_map(type, map, tab) == 1)
		return (1);
	return (0);
}

int	check_nb_player(char ***map)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	count = 0;
	while ((*map)[++i])
	{
		j = -1;
		while ((*map)[i][++j])
		{
			if ((*map)[i][j] == 'N' || (*map)[i][j] == 'S'
			|| (*map)[i][j] == 'E' || (*map)[i][j] == 'W')
				count++;
		}
	}
	if (count != 1)
	{
		ft_putstr_fd("Error : invalid number of player\n", 2);
		return (1);
	}
	return (0);
}

int	check_map_closed(char **map)
{
	int	nb_line;
	int	i;
	int	j;

	nb_line = 0;
	i = 0;
	while (map[nb_line])
		nb_line++;
	while (map[i])
	{
		j = 0;
		if (check_line_map(i, j, map, nb_line) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	error_file(t_env *env, char ***text, char ***map)
{
	parse_text(env->type, &env->count, env->nb_line);
	if (env->count.str_count != 0)
	{
		ft_putstr_fd("Error: line not allowed detected\n", 2);
		return (1);
	}
	if (error_parse_file(env->count, env->type, env->nb_line) == 1)
		return (1);
	if (dup_text_map(env->tab, env->type, text, map) == 1)
		return (1);
	if (check_nb_player(map) || check_map_closed(*map))
		return (1);
	return (0);
}
