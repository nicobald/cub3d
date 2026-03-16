/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utilisateur <utilisateur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 23:58:08 by utilisateur       #+#    #+#             */
/*   Updated: 2026/03/15 23:58:36 by utilisateur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *src, size_t n)
{
	size_t	length;
	char	*copy;

	if (!src)
		return (NULL);
	length = ft_strlen(src);
	if (length > n)
		length = n;
	copy = (char *)malloc(sizeof(char) * (length + 1));
	if (copy == NULL)
		return (NULL);
	ft_strlcpy(copy, src, length + 1);
	return (copy);
}
