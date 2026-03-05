/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laudinot <laudinot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:31:29 by laudinot          #+#    #+#             */
/*   Updated: 2025/04/13 15:17:11 by laudinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	if (little[0] == '\0')
		return ((char *)&big[0]);
	while (big[i] && i < len)
	{
		j = 0;
		k = i;
		while (big[k] == little[j] && k < len)
		{
			if (j == (size_t)ft_strlen(little) - 1)
				return ((char *)&big[i]);
			j++;
			k++;
		}
		i++;
	}
	return (NULL);
}
