/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 15:45:05 by nbaldes           #+#    #+#             */
/*   Updated: 2026/03/23 18:00:45 by nbaldes          ###   ########.fr       */
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

int	move_left(t_data_game *game)
{
	game->player->pos_x = game->player->pos_x + MOVE_SPEED * (cos((game->player->orientation - 90) * PI / 180));
	game->player->pos_y = game->player->pos_y + MOVE_SPEED * (sin((game->player->orientation - 90) * PI / 180));
	print_map(game);
	draw_grille(game);
	draw_player(game);
	draw_direction(game);
	return (0);
}

int	move_right(t_data_game *game)
{
	game->player->pos_x = game->player->pos_x + MOVE_SPEED * (cos((game->player->orientation + 90) * PI / 180));
	game->player->pos_y = game->player->pos_y + MOVE_SPEED * (sin((game->player->orientation + 90) * PI / 180));
	print_map(game);
	draw_grille(game);
	draw_player(game);
	draw_direction(game);
	return (0);
}

int	move_up(t_data_game *game)
{
	game->player->pos_x = game->player->pos_x + MOVE_SPEED * (cos((game->player->orientation) * PI / 180));
	game->player->pos_y = game->player->pos_y + MOVE_SPEED * (sin((game->player->orientation) * PI / 180));
	print_map(game);
	draw_grille(game);
	draw_player(game);
	draw_direction(game);
	return (0);
}

int	move_down(t_data_game *game)
{
	game->player->pos_x = game->player->pos_x + MOVE_SPEED * (cos((game->player->orientation + 180) * PI / 180));
	game->player->pos_y = game->player->pos_y + MOVE_SPEED * (sin((game->player->orientation + 180) * PI / 180));
	print_map(game);
	draw_grille(game);
	draw_player(game);
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
	if (game->key->w_key == 1)
		move_up(game);
	else if (game->key->a_key == 1)
		move_left(game);
	else if (game->key->d_key == 1)
		move_right(game);
	else if (game->key->s_key == 1)
		move_down(game);
	if (game->key->left_key == 1)
		rotate_left(game);
	if (game->key->right_key == 1)
		rotate_right(game);
    if (game->key->escape_key == 1)
		free_game(game);
	return (0);
}
