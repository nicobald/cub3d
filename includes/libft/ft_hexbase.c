/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexbase.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 08:21:53 by laudinot          #+#    #+#             */
/*   Updated: 2026/04/03 17:22:02 by nbaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

char	*ft_fillhex(char *hexa, unsigned int n)
{
	int				i;
	unsigned int	nb;
	char			*hexnb;

	if (n == 0)
	{
		hexnb = malloc(2);
		if (!hexnb)
			return (NULL);
		hexnb[0] = '0';
		hexnb[1] = '\0';
		return (hexnb);
	}
	i = 0;
	nb = n;
	while (nb != 0)
	{
		nb /= 16;
		i++;
	}
	hexnb = malloc(sizeof(char) * (i + 1));
	if (!hexnb)
		return (NULL);
	hexnb[i] = '\0';
	while (n != 0)
	{
		i--;
		hexnb[i] = hexa[n % 16];
		n /= 16;
	}
	return (hexnb);
}

char	*ft_hexbase_upp(unsigned int n)
{
	char	hexa[17];

	ft_strlcpy(hexa, "0123456789ABCDEF", 17);
	return (ft_fillhex(hexa, n));
}

int	ft_hexbase_low(unsigned int n)
{
	char	hexa[17];
	char	*hexnb;
	int		compteur;

	if (n == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	ft_strlcpy(hexa, "0123456789abcdef", 17);
	hexnb = ft_fillhex(hexa, n);
	compteur = ft_putstr(hexnb);
	free(hexnb);
	return (compteur);
}
