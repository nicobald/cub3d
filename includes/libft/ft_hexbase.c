/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexbase.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laudinot <laudinot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 08:21:53 by laudinot          #+#    #+#             */
/*   Updated: 2025/04/27 19:42:37 by laudinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_fillhex(char *hexa, unsigned int n)
{
	int		i;
	int		nb;
	char	*hexnb;

	i = 0;
	nb = n;
	while (nb != 0)
	{
		nb = nb / 16;
		i++;
	}
	hexnb = malloc(sizeof(char) * (i + 1));
	if (!hexnb)
		return (0);
	i = 0;
	while (n != 0)
	{
		hexnb[i] = hexa[n % 16];
		n = n / 16;
		i++;
	}
	hexnb[i] = '\0';
	ft_revstr(hexnb);
	return (hexnb);
}

int	ft_hexbase_upp(unsigned int n)
{
	char	hexa[17];
	char	*hexnb;
	int		compteur;

	if (n == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	ft_strlcpy(hexa, "0123456789ABCDEF", 17);
	hexnb = ft_fillhex(hexa, n);
	compteur = ft_putstr(hexnb);
	free(hexnb);
	return (compteur);
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
