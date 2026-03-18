/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laudinot <laudinot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:10:14 by laudinot          #+#    #+#             */
/*   Updated: 2026/03/18 16:00:51 by laudinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	calculate_map(t_data_game *game)
{
	game->x_pixel_per_unit = SCREEN_WIDTH / game->x_len;
	game->y_pixel_per_unit = SCREEN_HEIGHT / game->y_len;
}

// void	print_map(t_data_game *game)
// {
	
// }

int	create_window(t_env *env, t_data_game *game)
{
	env->win->mlx_ptr = mlx_init();	
	if (env->win->mlx_ptr == 0)
		return (printf("Mlx init failed \n"));
	printf("adresse window->mlx_ptr = %p\n", env->win->mlx_ptr);
	env->win->win_ptr = mlx_new_window(env->win->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "Dofus3D");
	calculate_map(game);
	// print_map(game);
	// window->img_ptr = mlx_new_image(window->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	// window->mlx_adress = mlx_get_data_addr(window->img_ptr, NULL, NULL, NULL);
	printf("test\n");
	mlx_loop(env->win->mlx_ptr);
	return (0);
}