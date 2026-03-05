/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laudinot <laudinot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:37:26 by louis             #+#    #+#             */
/*   Updated: 2025/04/05 12:15:30 by laudinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	ptr = (unsigned char *)b;
	while (i < n)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

/*int main(void)
{
	char	bytes[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 0};

	ft_memset(bytes, 0, 3 * sizeof(char));
	for (int i = 0; i < 10; i++)
		printf("%d ", bytes[i]);
}*/
/*int main()
{
	char * str;

	str = "salut";
	printf("%s", (char *)ft_memset(str, 0, sizeof str));
	return (0);
}*/