/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laudinot <laudinot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:40:29 by louis             #+#    #+#             */
/*   Updated: 2026/01/29 15:24:53 by laudinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	size_t	length;
	char	*copy;

	if (!src)
		return (NULL);
	length = ft_strlen(src);
	copy = (char *)malloc(sizeof(char) * (length + 1));
	if (copy == NULL)
		return (NULL);
	ft_strlcpy(copy, src, length + 1);
	return (copy);
}
/*int	main(int argc, char **argv)
{
	if (argc != 2)
		return (0);
	printf("Copie : %s\n", ft_strdup(argv[1]));
	printf("Copie : %s\n", strdup(argv[1]));
	return (0);
}*/
