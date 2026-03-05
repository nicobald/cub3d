/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadress.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laudinot <laudinot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 10:04:17 by laudinot          #+#    #+#             */
/*   Updated: 2025/04/27 17:16:39 by laudinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	fillstr(char *hex_adress, char *hexa, unsigned long adress, int i)
{
	i++;
	while (adress != 0)
	{
		hex_adress[i] = hexa[adress % 16];
		adress = adress / 16;
		i--;
	}
	hex_adress[i] = 'x';
	hex_adress[i - 1] = '0';
}

char	*ft_putnbr_base(void *ptr)
{
	char			hexa[17];
	char			*hex_adress;
	unsigned long	adress;
	int				i;

	i = 1;
	ft_strlcpy(hexa, "0123456789abcdef", 17);
	adress = (unsigned long)ptr;
	if (adress == 0)
		return (ft_strdup("0x0"));
	while (adress / 16 != 0)
	{
		adress = adress / 16;
		i++;
	}
	adress = (unsigned long)ptr;
	hex_adress = malloc(sizeof(char) * (i + 3));
	if (!hex_adress)
		return (NULL);
	hex_adress[i + 2] = '\0';
	fillstr(hex_adress, hexa, adress, i);
	return (hex_adress);
}

int	ft_putadress(void *ptr)
{
	char	*adress;
	int		compteur;

	if (ptr == NULL)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	adress = ft_putnbr_base(ptr);
	compteur = ft_putstr(adress);
	free(adress);
	return (compteur);
}
