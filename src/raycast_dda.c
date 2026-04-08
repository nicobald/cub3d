/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_dda_core.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:20:00 by nbaldes           #+#    #+#             */
/*   Updated: 2026/04/09 18:20:00 by nbaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_wall_cell(t_data_game *game, int x, int y)
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

static void	run_dda_loop(t_data_game *game)
{
	while (1)
	{
		if (game->data_text->sidex < game->data_text->sidey)
		{
			game->data_text->sidex += game->data_text->deltax;
			game->data_text->mapx += game->data_text->stepx;
			game->data_text->side = 0;
		}
		else
		{
			game->data_text->sidey += game->data_text->deltay;
			game->data_text->mapy += game->data_text->stepy;
			game->data_text->side = 1;
		}
		if (is_wall_cell(game, game->data_text->mapx, game->data_text->mapy))
			break ;
	}
}

double	dda_distance(t_data_game *game)
{
	init_dda(game);
	dda_step(game);
	run_dda_loop(game);
	if (game->data_text->side == 0)
		game->data_text->perpw = game->data_text->sidex - game->data_text->deltax;
	else
		game->data_text->perpw = game->data_text->sidey - game->data_text->deltay;
	if (game->data_text->perpw < 1e-6)
		game->data_text->perpw = 1e-6;
	return (game->data_text->perpw);
}

void	calc_pix_to_draw(t_data_game *game)
{
	game->data_text->lineheight = (int)(SCREEN_HEIGHT / game->data_text->perpw);
	game->data_text->drawstart = SCREEN_HEIGHT / 2 - game->data_text->lineheight / 2;
	game->data_text->drawend = SCREEN_HEIGHT / 2 + game->data_text->lineheight / 2;
	if (game->data_text->drawstart < 0)
		game->data_text->drawstart = 0;
	if (game->data_text->drawend >= SCREEN_HEIGHT)
		game->data_text->drawend = SCREEN_HEIGHT - 1;
	select_texture(game);
	compute_texture_x(game);
	draw_column_pixels(game);
}

void	dda(t_data_game *game)
{
	int		x;
	double	camera_x;

	game->data_text->floor_color = rgb_to_hex(game->colors[0],
			game->colors[1], game->colors[2]);
	game->data_text->sky_color = rgb_to_hex(game->colors[3],
			game->colors[4], game->colors[5]);
	game->player->angle = game->player->orientation * PI / 180.0;
	game->player->player_dir.x = cos(game->player->angle);
	game->player->player_dir.y = sin(game->player->angle);
	game->player->plane.x = -game->player->player_dir.y * 0.66;
	game->player->plane.y = game->player->player_dir.x * 0.66;
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		camera_x = 2.0 * x / (double)SCREEN_WIDTH - 1.0;
		game->player->ray_dir.x = game->player->player_dir.x
			+ game->player->plane.x * camera_x;
		game->player->ray_dir.y = game->player->player_dir.y
			+ game->player->plane.y * camera_x;
		game->data_text->screenx = x;
		game->data_text->perpw = dda_distance(game);
		calc_pix_to_draw(game);
		x++;
	}
}
