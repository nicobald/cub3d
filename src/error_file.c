/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utilisateur <utilisateur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 19:52:37 by utilisateur       #+#    #+#             */
/*   Updated: 2026/03/16 01:14:17 by utilisateur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	parse_text(int *type, t_count *count, int nb_line)
{
	int i;

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
		i++;
	}
	return ;
}

int error_parse_file(t_count count, int *type)
{
	int i;

	i = 0;
	if (count.no_count != 1 || count.so_count != 1 || count.we_count != 1 || count.ea_count != 1)
	{
		ft_putstr_fd("Error: Missing or duplicate texture definition (NO, SO, WE, EA must appear exactly once).\n", 2);
		return (1);
	}
	if (count.f_count != 1 || count.c_count != 1)
	{
		ft_putstr_fd("Error: Missing or duplicate color definition (F, C must appear exactly once).\n", 2);
		return (1);
	}
	while (type[i])
	{
		if (type[i] == MAP && type[i + 1] && type[i + 1] != MAP)
		{
		ft_putstr_fd("Error: Error: The map must be contiguous and placed at the end of the file.\n", 2);
		return (1);
		}
		i++;
	}
	return (0);
}

void	fill_text(int *type, int key, char ***new_tab, char **old_tab)
{
	int i;

	i = 0;
	while (type[i] != key)
		i++;
	(*new_tab)[key] = second_word_dup(old_tab[i]);
	return ;
}

int	fill_map(int *type, char ***map, char **tab)
{
	int i;
	int j;
	int begin_map;

	i = 0;
	j = 0;
	while (type[i] != MAP)
		i++;
	begin_map = i;
	while(type[i++] == MAP)
		j++;
	(*map) = malloc(sizeof(char *) * (j + 1));
	if (!(*map))
		return (1);
	(*map)[j] = NULL;
	j = 0;
	i = begin_map;
	while(type[i] == MAP)
	{
		(*map)[j] = ft_strdup(tab[i]);
		j++;
		i++;
	}
	return (0);
}

int dup_text_map(char **tab, int *type, char ***text, char ***map)
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

// int check_access_text()
// {
// 	if (access(file, F_OK) == -1)
// 	{
// 		ft_putstr_fd("Error: map file not found.\n", 2);
// 		return (1);
// 	}
// }

int error_file(t_env *env, char ***text, char ***map)
{
	parse_text(env->type, &env->count, env->nb_line);
	if (error_parse_file(env->count, env->type) == 1)
		return (1);
	if (dup_text_map(env->tab, env->type, text, map) == 1)
		return (1);
	// check_access_text();
	// flood_fill
	//fill_pos_player
	return (0);
}
