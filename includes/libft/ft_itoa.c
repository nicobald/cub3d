/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laudinot <laudinot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 11:39:25 by laudinot          #+#    #+#             */
/*   Updated: 2025/04/12 16:08:29 by laudinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*fill_str(char *str, int result, int negatif, int len)
{
	size_t	i;
	size_t	is_negative;

	i = (len + negatif) - 1;
	is_negative = 0;
	if (negatif == 2)
	{
		str[0] = '-';
		is_negative = 1;
	}
	str[i] = '\0';
	i--;
	while (i >= is_negative)
	{
		str[i] = (result % 10) + '0';
		result = result / 10;
		if (i == 0)
			break ;
		i--;
	}
	return (str);
}

char	*int_min(void)
{
	char	*str;

	str = ft_strdup("-2147483648");
	return (str);
}

size_t	lenght_calc(int n)
{
	int	i;

	i = 1;
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;
	size_t	negative;

	negative = 1;
	if (n == -2147483648)
		return (int_min());
	if (n < 0)
	{
		n = -n;
		negative++;
	}
	len = lenght_calc(n);
	str = (char *)malloc(sizeof(char) * (len + negative));
	if (str == NULL)
		return (NULL);
	fill_str(str, n, negative, len);
	return (str);
}
