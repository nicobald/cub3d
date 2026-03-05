/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laudinot <laudinot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 23:11:57 by louis             #+#    #+#             */
/*   Updated: 2025/04/12 16:21:32 by laudinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ifnull(const char *s1, const char *s2)
{
	char	*str;

	if (s1 == NULL && s2 != NULL)
	{
		str = malloc((ft_strlen((char *)s2) + 1) * sizeof(char));
		if (str == NULL)
			return (NULL);
		ft_strlcpy(str, (char *)s2, ft_strlen((char *)s2) + 1);
		return (str);
	}
	if (s2 == NULL && s1 != NULL)
	{
		str = malloc((ft_strlen((char *)s1) + 1) * sizeof(char));
		if (str == NULL)
			return (NULL);
		ft_strlcpy(str, (char *)s1, ft_strlen((char *)s1) + 1);
		return (str);
	}
	str = malloc(1 * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[0] = '\0';
	return (str);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	total_length;
	char	*str;

	if (s1 == NULL || s2 == NULL )
	{
		str = ft_ifnull(s1, s2);
		return (str);
	}
	total_length = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	str = malloc((total_length + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, (char *)s1, ft_strlen((char *)s1) + 1);
	ft_strlcat(str, (char *)s2, total_length + 1);
	return (str);
}
/*
int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		printf("./a.out + 2 string ");
		return (1);
	}
	printf("%s\n", ft_strjoin(argv[1], argv[2]));
	//printf("%s\n", strjoin(argv[1], argv[2]));
	return (0);
}*/