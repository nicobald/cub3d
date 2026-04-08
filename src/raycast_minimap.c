/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:20:00 by nbaldes           #+#    #+#             */
/*   Updated: 2026/04/09 18:20:00 by nbaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	is_wall(t_data_game *game, int x, int y)
{
	int	line_len;

	if (y < 0 || y > game->y_len || !game->map[y])
		return (TRUE);
	line_len = ft_strlen(game->map[y]);
	if (x < 0 || x >= line_len)
		return (TRUE);
	if (game->map[y][x] == '1' || game->map[y][x] == ' ')
		return (TRUE);
	return (FALSE);
}

void	cast_ray(t_data_game *game)
{
	while (game->data_text->ray_x >= 0 && game->data_text->ray_y >= 0
		&& game->data_text->ray_x <= game->x_len + 1
		&& game->data_text->ray_y <= game->y_len + 1)
	{
		game->data_text->pixel_ray_x = ((game->data_text->ray_x
					/ (game->x_len + 1)) * SCREEN_WIDTH) / 4;
		game->data_text->pixel_ray_y = ((game->data_text->ray_y
					/ (game->y_len + 1)) * SCREEN_HEIGHT) / 4;
		img_pix_put(&game->image, game->data_text->pixel_ray_x,
			game->data_text->pixel_ray_y, CUSTOM);
		game->data_text->t += 0.01;
		game->data_text->ray_x = game->player->pos.x + game->data_text->t
			* game->player->player_dir.x;
		game->data_text->ray_y = game->player->pos.y + game->data_text->t
			* game->player->player_dir.y;
		if (is_wall(game, (int)game->data_text->ray_x,
				(int)game->data_text->ray_y))
			break ;
	}
}

void	draw_direction(t_data_game *game)
{
	int	i;
	int	fov_half;

	fov_half = FOV / 2;
	i = -fov_half;
	while (i <= fov_half)
	{
		game->data_text->t = 0.0;
		game->player->player_dir.x = cos((game->player->orientation + i)
				* PI / 180.0);
		game->player->player_dir.y = sin((game->player->orientation + i)
				* PI / 180.0);
		game->data_text->ray_x = game->player->pos.x;
		game->data_text->ray_y = game->player->pos.y;
		cast_ray(game);
		i++;
	}
}

void	init_dda(t_data_game *game)
{
	game->data_text->mapx = (int)game->player->pos.x;
	game->data_text->mapy = (int)game->player->pos.y;
	game->data_text->deltax = fabs(1.0 / game->player->ray_dir.x);
	game->data_text->deltay = fabs(1.0 / game->player->ray_dir.y);
	if (fabs(game->player->ray_dir.x) < 1e-12)
		game->data_text->deltax = 1e30;
	if (fabs(game->player->ray_dir.y) < 1e-12)
		game->data_text->deltay = 1e30;
}

void	dda_step(t_data_game *game)
{
	if (game->player->ray_dir.x < 0)
	{
		game->data_text->stepx = -1;
		game->data_text->sidex = (game->player->pos.x - game->data_text->mapx)
			* game->data_text->deltax;
	}
	else
	{
		game->data_text->stepx = 1;
		game->data_text->sidex = (game->data_text->mapx + 1.0
				- game->player->pos.x) * game->data_text->deltax;
	}
	if (game->player->ray_dir.y < 0)
	{
		game->data_text->stepy = -1;
		game->data_text->sidey = (game->player->pos.y - game->data_text->mapy)
			* game->data_text->deltay;
	}
	else
	{
		game->data_text->stepy = 1;
		game->data_text->sidey = (game->data_text->mapy + 1.0
				- game->player->pos.y) * game->data_text->deltay;
	}
}
