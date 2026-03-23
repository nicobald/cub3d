/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laudinot <laudinot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 15:45:05 by nbaldes           #+#    #+#             */
/*   Updated: 2026/03/23 18:37:16 by laudinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	direction_right(t_data_game *game)
{
	if (game->player->orientation < 360)
		game->player->orientation++;
	if (game->player->orientation == 360)
		game->player->orientation = 0;
	print_map(game);
	draw_grille(game);
	draw_player(game);
	draw_direction(game);
	return (0);
}

int	direction_left(t_data_game *game)
{
	if (game->player->orientation > 0)
		game->player->orientation--;
	if (game->player->orientation == 0)
		game->player->orientation = 360;
	print_map(game);
	draw_grille(game);
	draw_player(game);
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

int	control_key(int keycode, t_data_game *game)
{
	if (keycode == 119)
		move_up(game);
	if (keycode == 97)
		move_left(game);
	else if (keycode == 100)
		move_right(game);
	else if (keycode == 115)
		move_down(game);
	if (keycode == 65361)
		direction_left(game);
	else if (keycode == 65363)
		direction_right(game);
    if (keycode == 65307)
	{
		free_game(game);
	}
	return (0);
}
