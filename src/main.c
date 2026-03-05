/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utilisateur <utilisateur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:57:33 by nbaldes           #+#    #+#             */
/*   Updated: 2026/03/05 17:32:35 by utilisateur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int check_args(int argc, char **argv)
{
	int i;
	int j;
	if (argc != 2)
	{
		ft_putstr_fd("Cub3D take only one argument", 2);
		return (1);
	}
	if (argv[i][j])
	{
		
	}
	return (0);
}

int	parsing(int argc, char **argv)
{
	(void)argv;
	check_args(argc, argv);
	//
	return (0);
}

int	main(int argc, char **argv)
{
	if (parsing(argc, argv) == 1)
		return (1);
	return (0);
}