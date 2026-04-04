/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 15:40:32 by laudinot          #+#    #+#             */
/*   Updated: 2026/04/02 16:36:03 by nbaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_if_hit_wall(t_data_game *game, double x_pos, double y_pos)
{
	int	x;
	int	y;

	x = (int)x_pos;
	y = (int)y_pos;
	if (game->map[y][x] == '1')
		return (TRUE);
	return (FALSE);
}

void	init_ray(t_data_game *game, double angle)
{
	game->data_text->t = 0;
	game->player->player_dir.x = cos(angle * PI / 180.0);
	game->player->player_dir.y = sin(angle * PI / 180.0);
	game->data_text->ray_x = (game->player->pos.x
			+ game->data_text->t * game->player->player_dir.x) / 4;
	game->data_text->ray_y = (game->player->pos.y
			+ game->data_text->t * game->player->player_dir.y) / 4;
}

void	cast_ray(t_data_game *game)
{
	while (game->data_text->ray_x <= game->x_len + 1
		&& game->data_text->ray_x >= 0
		&& game->data_text->ray_y <= game->y_len + 1
		&& game->data_text->ray_y >= 0)
	{
		game->data_text->pixel_ray_x = ((game->data_text->ray_x
					/ (game->x_len + 1)) * SCREEN_WIDTH) / 4;
		game->data_text->pixel_ray_y = ((game->data_text->ray_y
					/ (game->y_len + 1)) * SCREEN_HEIGHT) / 4;
		img_pix_put(&game->image, game->data_text->pixel_ray_x,
			game->data_text->pixel_ray_y, CUSTOM);
		game->data_text->t += 0.01;
		game->data_text->ray_x = game->player->pos.x
			+ game->data_text->t * game->player->player_dir.x;
		game->data_text->ray_y = game->player->pos.y
			+ game->data_text->t * game->player->player_dir.y;
		if (check_if_hit_wall(game, game->data_text->ray_x,
				game->data_text->ray_y) == TRUE)
			break ;
	}
}

void	draw_direction(t_data_game *game)
{
	game->data_text->fov = FOV / 2;
	game->data_text->i = 0;
	while (game->data_text->i < game->data_text->fov)
	{
		init_ray(game, game->player->orientation);
		cast_ray(game);
		game->data_text->i++;
	}
	game->data_text->i = 0;
	while (game->data_text->i > -game->data_text->fov)
	{
		init_ray(game, game->player->orientation + game->data_text->i);
		cast_ray(game);
		game->data_text->i--;
	}
}

void	init_dda_side_dist(t_data_game *game)
{
	if (game->player->ray_dir.x < 0)
	{
		game->data_text->stepX = -1;
		game->data_text->sideDistX = (game->player->pos.x - game->data_text->mapX)
			* game->data_text->deltaDistX;
	}
	else
	{
		game->data_text->stepX = 1;
		game->data_text->sideDistX = (game->data_text->mapX + 1.0
				- game->player->pos.x) * game->data_text->deltaDistX;
	}
	if (game->player->ray_dir.y < 0)
	{
		game->data_text->stepY = -1;
		game->data_text->sideDistY = (game->player->pos.y - game->data_text->mapY)
			* game->data_text->deltaDistY;
	}
	else
	{
		game->data_text->stepY = 1;
		game->data_text->sideDistY = (game->data_text->mapY + 1.0
				- game->player->pos.y) * game->data_text->deltaDistY;
	}
}

void	dda_loop(t_data_game *game)
{
	game->data_text->side = 0;
	while (1)
	{
		if (game->data_text->sideDistX < game->data_text->sideDistY)
		{
			game->data_text->sideDistX += game->data_text->deltaDistX;
			game->data_text->mapX += game->data_text->stepX;
			game->data_text->side = 0;
		}
		else
		{
			game->data_text->sideDistY += game->data_text->deltaDistY;
			game->data_text->mapY += game->data_text->stepY;
			game->data_text->side = 1;
		}
		if (game->data_text->mapY < 0 || game->data_text->mapY > game->y_len
		|| game->data_text->mapX < 0
		|| game->data_text->mapX >= (int)ft_strlen(game->map[game->data_text->mapY])
		|| game->map[game->data_text->mapY][game->data_text->mapX] == '1'
		|| game->map[game->data_text->mapY][game->data_text->mapX] == ' ')
			break ;
	}
}

double	dda_distance(t_data_game *game)
{
	game->data_text->mapX = (int)game->player->pos.x;
	game->data_text->mapY = (int)game->player->pos.y;
	if (game->player->ray_dir.x == 0)
		game->data_text->deltaDistX = 1e30;
	else
		game->data_text->deltaDistX = fabs(1 / game->player->ray_dir.x);
	if (game->player->ray_dir.y == 0)
		game->data_text->deltaDistY = 1e30;
	else
		game->data_text->deltaDistY = fabs(1 / game->player->ray_dir.y);
	init_dda_side_dist(game);
	dda_loop(game);
	if (game->data_text->side == 0)
		game->data_text->perpWallDist = (game->data_text->mapX - game->player->pos.x
				+ (1 - game->data_text->stepX) / 2.0) / game->player->ray_dir.x;
	else
		game->data_text->perpWallDist = (game->data_text->mapY - game->player->pos.y
				+ (1 - game->data_text->stepY) / 2.0) / game->player->ray_dir.y;
	return (game->data_text->perpWallDist);
}

void	dda(t_data_game *game)
{
	int		x;
	double	camera_x;

	game->player->angle = game->player->orientation * PI / 180.0;
	game->player->player_dir.x = cos(game->player->angle);
	game->player->player_dir.y = sin(game->player->angle);
	game->player->plane.x = -game->player->player_dir.y * 0.66;
	game->player->plane.y = game->player->player_dir.x * 0.66;
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
		game->player->ray_dir.x = game->player->player_dir.x
			+ game->player->plane.x * camera_x;
		game->player->ray_dir.y = game->player->player_dir.y
			+ game->player->plane.y * camera_x;
		if (fabs(game->player->ray_dir.x) < 1e-6)
			game->player->ray_dir.x = 1e-6;
		if (fabs(game->player->ray_dir.y) < 1e-6)
			game->player->ray_dir.y = 1e-6;
		game->data_text->perpWallDist = dda_distance(game);
		game->data_text->screenX = x;
		calc_pix_to_draw(game);
		x++;
	}
}

void	draw_column_pixels(t_data_game *game)
{
	int	y;

	y = 0;
	while (y < game->data_text->drawStart)
	{
		img_pix_put(&game->image, game->data_text->screenX, y,
			game->data_text->sky_color);
		y++;
	}
	while (y <= game->data_text->drawEnd)
	{
		img_pix_put(&game->image, game->data_text->screenX, y,
			game->data_text->wall_color);
		y++;
	}
	while (y < SCREEN_HEIGHT)
	{
		img_pix_put(&game->image, game->data_text->screenX, y,
			game->data_text->floor_color);
		y++;
	}
}

static int	rgb_to_hex(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	calc_pix_to_draw(t_data_game *game)
{
	game->data_text->lineHeight = (int)(SCREEN_HEIGHT / game->data_text->perpWallDist);
	game->data_text->drawStart = -game->data_text->lineHeight / 2 + SCREEN_HEIGHT / 2;
	game->data_text->drawEnd = game->data_text->lineHeight / 2 + SCREEN_HEIGHT / 2;
	if (game->data_text->drawStart < 0)
		game->data_text->drawStart = 0;
	if (game->data_text->drawEnd >= SCREEN_HEIGHT)
		game->data_text->drawEnd = SCREEN_HEIGHT - 1;
	game->data_text->wall_color = WHITE;
	game->data_text->floor_color = rgb_to_hex(game->colors[0],
			game->colors[1], game->colors[2]);
	game->data_text->sky_color = rgb_to_hex(game->colors[3],
			game->colors[4], game->colors[5]);
	draw_column_pixels(game);
}
