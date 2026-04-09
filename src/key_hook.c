/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 15:45:05 by nbaldes           #+#    #+#             */
/*   Updated: 2026/04/09 11:53:31 by nbaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_wall(t_data_game *game, double x, double y)
{
	int		map_x;
	int		map_y;
	int		line_len;
	char	cell;

	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || map_y > game->y_len || !game->map[map_y])
		return (TRUE);
	line_len = ft_strlen(game->map[map_y]);
	if (map_x < 0 || map_x >= line_len)
		return (TRUE);
	cell = game->map[map_y][map_x];
	if (cell == '1' || cell == ' ')
		return (TRUE);
	return (FALSE);
}

void	try_move(t_data_game *game, double angle)
{
	double	next_x;
	double	next_y;
	double	buf;

	buf = 0.001;
	next_x = game->player->pos.x + MOVE_SPEED * cos(angle);
	next_y = game->player->pos.y + MOVE_SPEED * sin(angle);
	if (!is_wall(game, next_x + buf, game->player->pos.y)
		&& !is_wall(game, next_x - buf, game->player->pos.y))
		game->player->pos.x = next_x;
	if (!is_wall(game, game->player->pos.x, next_y + buf)
		&& !is_wall(game, game->player->pos.x, next_y - buf))
		game->player->pos.y = next_y;
}

int	rotate_right(t_data_game *game)
{
	double	rot_speed;

	rot_speed = 180.0;
	if (game->player->orientation < 360)
	{
		game->player->orientation += rot_speed * game->delta_time;
	}
	if (game->player->orientation >= 360)
		game->player->orientation -= 360;
	return (0);
}

int	rotate_left(t_data_game *game)
{
	double	rot_speed;

	rot_speed = 180.0;
	game->player->orientation -= rot_speed * game->delta_time;
	if (game->player->orientation < 0)
		game->player->orientation += 360;
	return (0);
}

int	control_key(t_data_game *game)
{
	gettimeofday(&game->time, NULL);
	game->delta_time = (game->time.tv_sec + game->time.tv_usec
			/ 1000000.0) - game->last_time;
	game->last_time = game->time.tv_sec + game->time.tv_usec / 1000000.0;
	if (game->key->w_key == 1)
		try_move(game, (game->player->orientation) * PI / 180);
	if (game->key->a_key == 1)
		try_move(game, (game->player->orientation - 90) * PI / 180);
	if (game->key->d_key == 1)
		try_move(game, (game->player->orientation + 90) * PI / 180);
	if (game->key->s_key == 1)
		try_move(game, (game->player->orientation + 180) * PI / 180);
	if (game->key->left_key == 1)
		rotate_left(game);
	if (game->key->right_key == 1)
		rotate_right(game);
	if (game->key->escape_key == 1)
		free_game(game);
	draw_image(game);
	return (0);
}
