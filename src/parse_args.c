/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 23:53:38 by nbaldes           #+#    #+#             */
/*   Updated: 2026/04/06 20:03:33 by nbaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_args(char **argv)
{
	int		len;
	int		argc;
	char	*extention;

	argc = 0;
	while (argv[argc])
		argc++;
	if (argc != 2 || !argv[1])
	{
		ft_putstr_fd("Error: Cub3D takes exactly one argument.\n", 2);
		return (1);
	}
	len = ft_strlen(argv[1]);
	extention = &argv[1][len - 4];
	if (ft_strnstr(extention, ".cub", len) == NULL || len == 4)
	{
		ft_putstr_fd("Error: Invalid map file. Expected a .cub.\n", 2);
		return (1);
	}
	return (0);
}
