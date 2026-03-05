/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laudinot <laudinot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:53:35 by laudinot          #+#    #+#             */
/*   Updated: 2025/04/27 09:58:28 by laudinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(int n)
{
	char	c;
	int		compteur;

	compteur = 0;
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		compteur += ft_putchar('-');
		n = -n;
	}
	if (n > 9)
	{
		compteur += ft_putnbr(n / 10);
	}
	c = n % 10 + '0';
	compteur += ft_putchar(c);
	return (compteur);
}
