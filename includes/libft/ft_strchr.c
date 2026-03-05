/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laudinot <laudinot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:20:19 by laudinot          #+#    #+#             */
/*   Updated: 2025/04/12 16:17:33 by laudinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	uc;

	i = 0;
	uc = (unsigned char)c;
	while (i <= ft_strlen((char *)s))
	{
		if ((unsigned char)s[i] == uc)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}
/*
int main()
{

	int c;
	char *s = "tripouille";

	c = 't' + 256;
	printf("%d\n", c);
	printf("%s\n",ft_strchr(s , c));
	printf("%s\n",strchr(s , c));
	return (0);
}*/