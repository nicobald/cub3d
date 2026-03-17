/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 19:52:37 by utilisateur       #+#    #+#             */
/*   Updated: 2026/03/17 19:22:13 by nbaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	parse_text(int *type, t_count *count, int nb_line)
{
	int	i;

	i = 0;
	while (i < (nb_line - 1))
	{
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

int	error_parse_file(t_count count, int *type)
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
	while (type[++i])
	{
		if (type[i] == MAP && type[i + 1] && type[i + 1] != MAP)
		{
			ft_putstr_fd("Error: Error: wrong map format.\n", 2);
			return (1);
		}
	}
	return (0);
}

void	fill_text(int *type, int key, char ***new_tab, char **old_tab)
{
	int	i;

	i = 0;
	while (type[i] != key)
		i++;
	(*new_tab)[key] = second_word_dup(old_tab[i]);
	return ;
}

int	fill_map(int *type, char ***map, char **tab)
{
	int	i;
	int	j;
	int	begin_map;

	i = 0;
	j = 0;
	while (type[i] != MAP)
		i++;
	begin_map = i;
	while (type[i++] == MAP)
		j++;
	(*map) = malloc(sizeof(char *) * (j + 1));
	if (!(*map))
		return (1);
	(*map)[j] = NULL;
	j = 0;
	i = begin_map;
	while (type[i] == MAP)
	{
		(*map)[j] = ft_strrtrim(tab[i], "\n ");
		j++;
		i++;
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
		while (map[i][j])
		{
			if (i == 0 || i == (nb_line - 1))
			{
				if (map[i][j] != ' ' && map[i][j] != '1'
					&& map[i][j] != '\n' && map[i][j] != '\0')
				{
					ft_putstr_fd("Error : Map not closed", 2);
					return (1);
				}
			}
			else
			{
				if (j == 0 || j > ft_strlen(map[i]))
				{
					j++;
					continue ;
				}
				else
				{
					if (map[i][j] == ' ' &&
					((map[i][j - 1] != '1' && map[i][j - 1] != ' ')
					|| (map[i][j + 1] != '1' && map[i][j + 1] != ' ')
					|| (map[i - 1][j] != '1' && map[i - 1][j] != ' ')
					|| (map[i + 1][j] != '1' && map[i + 1][j] != ' ')))
					{
						ft_putstr_fd("Error : Map not closed", 2);
						return (1);
					}
					else if (map[i][j] == '0' && (j >= ft_strlen(map[i - 1])))
					{
						ft_putstr_fd("Error : Map not closed", 2);
						return (1);
					}
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	error_file(t_env *env, char ***text, char ***map)
{
	int	i;

	i = 0;
	parse_text(env->type, &env->count, env->nb_line);
	if (env->count.str_count != 0)
	{
		ft_putstr_fd("Error: line not allowed detected\n", 2);
		return (1);
	}
	if (error_parse_file(env->count, env->type) == 1)
		return (1);
	if (dup_text_map(env->tab, env->type, text, map) == 1)
		return (1);
	if (check_nb_player(map) || check_map_closed(*map))
		return (1);
	while (i < 4)
	{
		printf("%s\n", (*text)[i]);
		check_access((*text)[i]);
		i++;
	}
	// flood_fill
	//fill_pos_player
	return (0);
}
