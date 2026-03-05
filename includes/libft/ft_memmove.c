/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laudinot <laudinot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 11:59:27 by laudinot          #+#    #+#             */
/*   Updated: 2025/04/12 16:09:24 by laudinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*ptrdest;
	unsigned char	*ptrsrc;
	size_t			i;

	i = 0;
	ptrdest = (unsigned char *)dest;
	ptrsrc = (unsigned char *)src;
	if (ft_strlen((char *)ptrsrc) > ft_strlen((char *)ptrdest))
	{
		while (0 < n)
		{
			ptrdest[n - 1] = ptrsrc[n - 1];
			n--;
		}
	}
	else
	{
		while (i < n)
		{
			ptrdest[i] = ptrsrc[i];
			i++;
		}
	}
	return (dest);
}
/*int main(void)
{

	char *bytes = strdup("123456789");

	ft_memmove(bytes + 3, bytes, 5);
	for (int i = 0; i < 10; i++)
		if (bytes[i])
			printf("%c ", bytes[i]);
		else
			printf("\\0 ");
	free(bytes);
}*/