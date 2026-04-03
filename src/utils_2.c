/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 20:09:20 by nbaldes           #+#    #+#             */
/*   Updated: 2026/04/03 16:07:15 by nbaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_parsing(t_env *env, char ***text, char ***map, t_player *player)
{
	free(env->type);
	free_tab(&env->tab);
	free_tab(map);
	free_tab(text);
	free(player);
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

// void	ft_revstr(char *str)
// {
// 	char	temp;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = ft_strlen(str) - 1;
// 	while (i < j)
// 	{
// 		temp = str[i];
// 		str[i] = str[j];
// 		str[j] = temp;
// 		i++;
// 		j--;
// 	}
// }

// char	*ft_fillhex(char *hexa, unsigned int n)
// {
// 	int		i;
// 	int		nb;
// 	char	*hexnb;

// 	i = 0;
// 	nb = n;
// 	while (nb != 0)
// 	{
// 		nb = nb / 16;
// 		i++;
// 	}
// 	hexnb = malloc(sizeof(char) * (i + 1));
// 	if (!hexnb)
// 		return (0);
// 	i = 0;
// 	while (n != 0)
// 	{
// 		hexnb[i] = hexa[n % 16];
// 		n = n / 16;
// 		i++;
// 	}
// 	hexnb[i] = '\0';
// 	ft_revstr(hexnb);
// 	return (hexnb);
// }

// int	ft_hexbase_upp(unsigned int n)
// {
// 	char	hexa[17];
// 	char	*hexnb;
// 	int		compteur;

// 	if (n == 0)
// 	{
// 		write(1, "0", 1);
// 		return (1);
// 	}
// 	ft_strlcpy(hexa, "0123456789ABCDEF", 17);
// 	hexnb = ft_fillhex(hexa, n);
// 	compteur = ft_putstr(hexnb);
// 	free(hexnb);
// 	return (compteur);
// }