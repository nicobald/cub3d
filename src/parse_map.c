/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 18:05:43 by laudinot          #+#    #+#             */
/*   Updated: 2026/04/06 21:12:38 by nbaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_first_space(char *str)
{
	int	i;
	int	ret;

	i = -1;
	ret = 0;

	while (str[++i])
	{
		if (str[i] == ' ' || (str[i] >= 7 && str[i] <= 13))
			ret++;
		else
			return (ret);
	}
	return (ret);
}

int	get_map_x(char **str)
{
	int	i;
	int	len;
	int	first_space;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (ft_strlen(str[i]) > len)
			len = ft_strlen(str[i]);
		i++;
	}
	first_space = get_first_space(str[0]);
	i = 1;
	while (str[i])
	{
		if (first_space > get_first_space(str[i]))
			first_space = get_first_space(str[i]);
		i++;
	}
	remove_first_space(str, first_space);
	return ((len - 1) - first_space);
}

int	tab_colors(int **fcolors, char **text)
{
	int		i;
	char	**colors;
	char	*tmp;

	i = 0;
	(*fcolors) = malloc(sizeof(int) * 6);
	if (!*fcolors)
		return (1);
	tmp = ft_strjoin_coma(text[4], text[5]);
	colors = ft_split(tmp, ',');
	free(tmp);
	while (colors[i])
	{
		(*fcolors)[i] = ft_atoi(colors[i]);
		i++;
	}
	free_tab(&colors);
	return (0);
}

int	is_there_player(char *str, t_data_game *game)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
		{
			game->player->pos.x = i + 0.5;
			game->player_start_dir = str[i];
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

void	parse_map_info(t_data_game *game)
{
	int	i;

	i = 0;
	while (game->map[i])
		i++;
	game->y_len = i - 1;
	i = 0;
	game->x_len = get_map_x(game->map);
	tab_colors(&game->colors, game->text);
	while (is_there_player(game->map[i], game) == FALSE)
		i++;
	game->player->pos.y = i + 0.5;
}
