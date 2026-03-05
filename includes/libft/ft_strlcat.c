/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laudinot <laudinot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:11:23 by louis             #+#    #+#             */
/*   Updated: 2025/04/12 01:06:45 by laudinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if ((size_t)ft_strlen(dst) >= dstsize)
		return (dstsize + ft_strlen((char *)src));
	if (dstsize == 0)
		return (ft_strlen((char *)src));
	while (dst[j] && j < dstsize - 1)
		j++;
	while (src[i] && j < dstsize - 1)
	{
		dst[j] = src[i];
		j++;
		i++;
	}
	dst[j] = '\0';
	return (ft_strlen(src) + (j - i));
}
