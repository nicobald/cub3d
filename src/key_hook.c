/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 15:45:05 by nbaldes           #+#    #+#             */
/*   Updated: 2026/03/23 17:07:46 by nbaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	rotate_left(t_data_game *game)
{
	if (game->player->orientation < 360)
		game->player->orientation++;
	if (game->player->orientation == 360)
		game->player->orientation = 0;
	draw_direction(game);
	return (0);
}

int	rotate_right(t_data_game *game)
{
	if (game->player->orientation > 0)
		game->player->orientation--;
	if (game->player->orientation == 0)
		game->player->orientation = 360;
	draw_direction(game);
	return (0);
}


int	key_press(int keycode, t_data_game *game)
{
	if (keycode == W_KEY)
		game->key->w_key = 1;
	if (keycode == A_KEY)
		game->key->a_key = 1;
	else if (keycode == D_KEY)
		game->key->d_key = 1;
	else if (keycode == S_KEY)
		game->key->s_key = 1;
	else if (keycode == LEFT_KEY)
		game->key->left_key = 1;
	else if (keycode == RIGHT_KEY)
		game->key->right_key = 1;
	else if (keycode == ESCAPE_KEY)
		game->key->escape_key = 1;
	return (0);
}

int	key_release(int keycode, t_data_game *game)
{
	if (keycode == W_KEY)
		game->key->w_key = 0;
	if (keycode == A_KEY)
		game->key->a_key = 0;
	else if (keycode == D_KEY)
		game->key->d_key = 0;
	else if (keycode == S_KEY)
		game->key->s_key = 0;
	else if (keycode == LEFT_KEY)
		game->key->left_key = 0;
	else if (keycode == RIGHT_KEY)
		game->key->right_key = 0;
	else if (keycode == ESCAPE_KEY)
		game->key->escape_key = 0;
	return (0);
}

int	control_key(t_data_game *game)
{
	// if (keycode == W_KEY)
	// 	move_up(game);
	// else if (keycode == A_KEY)
	// 	move_left(game);
	// else if (keycode == D_KEY)
	// 	move_right(game);
	// else if (keycode == S_KEY)
	// 	move_down(game);
	if (game->key->left_key == 1)
		rotate_left(game);
	if (game->key->right_key == 1)
		rotate_right(game);
    if (game->key->escape_key == 1)
		free_game(game);
	return (0);
}
