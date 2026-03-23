/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laudinot <laudinot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 15:45:05 by nbaldes           #+#    #+#             */
/*   Updated: 2026/03/21 19:07:02 by laudinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	move_left(t_data_game *game)
{
	if (game->player->orientation < 360)
		game->player->orientation++;
	if (game->player->orientation == 360)
		game->player->orientation = 0;
	draw_direction(game);
	return (0);
}

int	move_right(t_data_game *game)
{
	if (game->player->orientation > 0)
		game->player->orientation--;
	if (game->player->orientation == 0)
		game->player->orientation = 360;
	draw_direction(game);
	return (0);
}

// int	move_up(t_data_game *game)
// {
// 	draw_direction();
// 	return (0);
// }

// int	move_down(t_data_game *game)
// {
// 	draw_direction();
// 	return (0);
// }

int	control_key(int keycode, t_data_game *game)
{
	// if (keycode == 119)
	// 	move_up(env);
	if (keycode == 97)
		move_left(game);
	else if (keycode == 100)
		move_right(game);
	// else if (keycode == 115)
	// 	move_down(env);
    if (keycode == 65307)
	{
		free_game(game);
	}
	return (0);
}
