/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 23:31:40 by utilisateur       #+#    #+#             */
/*   Updated: 2026/03/17 16:13:55 by nbaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	alloc_tab(char ***tab, int nb_line)
{
	if (nb_line == 0)
	{
		ft_putstr_fd("Error: Empty file.\n", 2);
		return (1);
	}
	*tab = malloc(sizeof(char *) * (nb_line + 1));
	if (!*tab)
		return (1);
	(*tab)[nb_line] = NULL;
	return (0);
}

void	free_tab(char ***tab)
{
	int	i;

	i = 0;
	if (tab == NULL || *tab == NULL)
		return ;
	while ((*tab)[i])
	{
		free((*tab)[i]);
		(*tab)[i] = NULL;
		i++;
	}
	free(*tab);
	(*tab) = NULL;
	return ;
}

int	count_words(const char *s)
{
	int	i;
	int	count;

	if (!s)
		return (0);
	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
			i++;
		if (!s[i])
			break ;
		count++;
		while (s[i] && s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
			i++;
	}
	return (count);
}

int	tab_is_digit(char **tab)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (ft_isdigit(tab[i][j]) == 0)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

char	*second_word_dup(char *s)
{
	int	start;
	int	len;

	start = 0;
	while (s[start] == ' ' || s[start] == '\t')
		start++;
	while (s[start] && s[start] != ' ' && s[start] != '\t' && s[start] != '\n')
		start++;
	while (s[start] == ' ' || s[start] == '\t')
		start++;
	len = 0;
	while (s[start + len] && s[start + len] != ' '
		&& s[start + len] != '\t' && s[start + len] != '\n')
		len++;
	return (ft_strndup(s + start, len));
}
