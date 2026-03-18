/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utilisateur <utilisateur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 20:09:20 by nbaldes           #+#    #+#             */
/*   Updated: 2026/03/18 01:56:16 by utilisateur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_parsing(t_env *env, char ***text, char ***map)
{
	free(env->type);
	free_tab(&env->tab);
	free_tab(map);
	free_tab(text);
	return ;
}

int	split_check_color(char *line)
{
	char	**tab;
	char	**colors;
	char	*trimmed_line;

	trimmed_line = ft_strtrim(line, "\n");
	tab = ft_split(trimmed_line, ' ');
	free(trimmed_line);
	colors = ft_split(tab[1], ',');
	free_tab(&tab);
	if (tab_is_digit(colors) == 0)
	{
		free_tab(&colors);
		return (0);
	}
	if (ft_atoi(colors[0]) < 0 || ft_atoi(colors[0]) > 255
		|| ft_atoi(colors[1]) < 0 || ft_atoi(colors[1]) > 255
		|| ft_atoi(colors[2]) < 0 || ft_atoi(colors[2]) > 255)
	{
		free_tab(&colors);
		return (0);
	}
	free_tab(&colors);
	return (1);
}

char	*ft_strrtrim(char const *s1, char const *set)
{
	int		last;
	char	*str;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup((char *)s1));
	last = ft_strlen((char *)s1) - 1;
	while (last >= 0 && ft_strchr(set, s1[last]) != NULL)
		last--;
	if (last < 0)
		return (if_full_trim());
	str = (char *)malloc(sizeof(char) * (last + 2));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, (char *)s1, last + 2);
	return (str);
}

void	print_tab(char **str)
{
	int	x;

	x = 0;

	while (str[x])
	{
		printf("%s\n", str[x]);
		x++;
	}
	printf("\n");
}
