/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laudinot <laudinot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 08:32:53 by laudinot          #+#    #+#             */
/*   Updated: 2025/04/27 19:45:21 by laudinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_format(char c, va_list liste)
{
	int	compteur;

	compteur = 0;
	if (c == '%')
		compteur = ft_putchar(c);
	else if (c == 'd' || c == 'i')
		compteur = ft_putnbr(va_arg(liste, int));
	else if (c == 'c')
		compteur = ft_putchar(va_arg(liste, int));
	else if (c == 's')
		compteur = ft_putstr(va_arg(liste, char *));
	else if (c == 'p')
		compteur = ft_putadress(va_arg(liste, void *));
	else if (c == 'u')
		compteur = ft_unsigned_putnbr(va_arg(liste, unsigned int));
	else if (c == 'x')
		compteur = ft_hexbase_low(va_arg(liste, unsigned int));
	else if (c == 'X')
		compteur = ft_hexbase_upp(va_arg(liste, unsigned int));
	return (compteur);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		compteur;
	va_list	liste;

	if (!format)
		return (0);
	compteur = 0;
	i = 0;
	va_start(liste, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			compteur += ft_format(format[i], liste);
		}
		else
			compteur += ft_putchar(format[i]);
		i++;
	}
	va_end(liste);
	return (compteur);
}
