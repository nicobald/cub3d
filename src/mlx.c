/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laudinot <laudinot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:10:14 by laudinot          #+#    #+#             */
/*   Updated: 2026/03/17 16:25:29 by laudinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	create_window(t_env *env)
{
	env->win->mlx_ptr = mlx_init();	
	if (env->win->mlx_ptr == 0)
		return (printf("Mlx init failed \n"));
	printf("adresse window->mlx_ptr = %p\n", env->win->mlx_ptr);
	env->win->win_ptr = mlx_new_window(env->win->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "Dofus3D");
	// window->img_ptr = mlx_new_image(window->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	// window->mlx_adress = mlx_get_data_addr(window->img_ptr, NULL, NULL, NULL);
	printf("test\n");
	mlx_loop(env->win->mlx_ptr);
	return (0);
}