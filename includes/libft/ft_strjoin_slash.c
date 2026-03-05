/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_slash.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:28:22 by nbaldes           #+#    #+#             */
/*   Updated: 2025/12/04 16:28:47 by nbaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strjoin_copy(char *result, const char *s1, const char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = '/';
	i++;
	while (s2[j])
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
}

char	*ft_strjoin_slash(const char *s1, const char *s2)
{
	char	*result;
	int		lentot;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	lentot = ft_strlen(s1) + ft_strlen(s2);
	result = malloc(lentot + 2);
	if (!result)
		return (NULL);
	ft_strjoin_copy(result, s1, s2);
	return (result);
}
