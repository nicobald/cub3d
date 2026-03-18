/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 18:05:43 by laudinot          #+#    #+#             */
/*   Updated: 2026/03/18 18:26:00 by nbaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_map_y(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	get_map_x(char **str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str[0]);
	while (str[i])
	{
		if (ft_strlen(str[i]) > len)
			len = ft_strlen(str[i]);
		i++;
	}
	return (len);
}

int	tab_colors(int **fcolors, char **text)
{
	int		i;
	char	**colors;

	i = 0;
	colors = malloc(sizeof(char *) * 7);
	if (!colors)
		return (1);
	(*fcolors) = malloc(sizeof(int) * 6);
	if (!fcolors)
		return (1);
	colors[6] = NULL;
	colors = ft_split(ft_strjoin_coma(text[4], text[5]), ',');
	while (colors[i])
	{
		(*fcolors)[i] = ft_atoi(colors[i]);
		i++;
	}
	free_tab(&colors);
	return (0);
}

void	parse_map_info(t_data_game *game)
{
	game->y_len = get_map_y(game->map);
	game->x_len = get_map_x(game->map);
	tab_colors(&game->colors, game->text);
	printf ("Map X : %d\nMap Y : %d\n", game->x_len, game->y_len);
}
