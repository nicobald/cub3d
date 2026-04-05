/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laudinot <laudinot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 15:54:24 by nbaldes           #+#    #+#             */
/*   Updated: 2026/03/18 16:37:14 by laudinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

int	check_flline_map(int i, int j, char **map, int nb_line)
{
	if (i == 0 || i == (nb_line - 1))
	{
		if (map[i][j] != ' ' && map[i][j] != '1'
			&& map[i][j] != '\n' && map[i][j] != '\0'
			&& !(map[i][j] >= 7 && map[i][j] <= 13))
		{
			ft_putstr_fd("Error : Map not closed", 2);
			return (1);
		}
	}
	return (0);
}

int	check_oth_line_map(int i, int j, char **map)
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
	return (0);
}

int	check_line_map(int i, int j, char **map, int nb_line)
{
	while (map[i][j])
	{
		if (check_flline_map(i, j, map, nb_line) == 1)
			return (1);
		else if (i != 0 && i != (nb_line - 1))
		{
			if (j == 0 || j > ft_strlen(map[i]))
			{
				j++;
				continue ;
			}
			else
			{
				if (check_oth_line_map(i, j, map) == 1)
					return (1);
			}
		}
		j++;
	}
	return (0);
}
