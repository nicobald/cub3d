/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laudinot <laudinot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 08:26:52 by laudinot          #+#    #+#             */
/*   Updated: 2025/04/12 16:30:41 by laudinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	j;
	char	*substr;

	j = 0;
	if (s == NULL)
		return (NULL);
	if (start >= (unsigned int)ft_strlen((char *)s))
		return (ft_strdup(""));
	if ((size_t)ft_strlen((char *)s + start) < len)
		len = ft_strlen((char *)s + start);
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (substr == NULL)
		return (NULL);
	while (j < len)
	{
		substr[j] = s[start + j];
		j++;
	}
	substr[j] = '\0';
	return (substr);
}
