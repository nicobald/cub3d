/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laudinot <laudinot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 09:07:16 by laudinot          #+#    #+#             */
/*   Updated: 2025/04/06 18:33:41 by laudinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*if_full_trim(void)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * 1);
	if (str == NULL)
		return (NULL);
	str[0] = '\0';
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		first;
	int		last;
	char	*str;

	first = 0;
	if (!set && s1)
		return (ft_strdup((char *)s1));
	if (!s1)
		return (NULL);
	while (ft_strchr(set, s1[first]) != NULL)
		first++;
	last = ft_strlen((char *)s1) - 1;
	if (first > last)
		return (if_full_trim());
	while (ft_strchr(set, s1[last]) != NULL)
		last--;
	str = (char *)malloc(sizeof(char) * ((last - first) + 2));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, (char *)s1 + first, (last - first) + 2);
	return (str);
}
