/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 15:40:32 by laudinot          #+#    #+#             */
/*   Updated: 2026/03/23 19:37:00 by nbaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_direction(t_data_game *game)
{
	double	ray_x;
	double	ray_y;
	int		pixel_ray_x;
	int		pixel_ray_y;
	double	t;

	t = 0;
	game->player->dir_x = cos(game->player->orientation * PI / 180);
	game->player->dir_y = sin(game->player->orientation * PI / 180);
	ray_x = game->player->pos_x + t * game->player->dir_x;
	ray_y = game->player->pos_y + t * game->player->dir_y;

	while (ray_x <= game->x_len + 1 && ray_x >= 0 && ray_y <= game->y_len + 1 && ray_y >= 0)
	{
		pixel_ray_x = (ray_x / (game->x_len + 1)) * SCREEN_WIDTH;
		pixel_ray_y = (ray_y / (game->y_len + 1)) * SCREEN_HEIGHT;
		// printf("DOIT PRINT SUR X : %d Y : %d\n", pixel_ray_x, pixel_ray_y);
		mlx_pixel_put(game->win->mlx_ptr, game->win->win_ptr, pixel_ray_x, pixel_ray_y, CUSTOM);
		t += 0.01;
		ray_x = game->player->pos_x + t * game->player->dir_x;
		ray_y = game->player->pos_y + t * game->player->dir_y;
	}
}
void	put_direction(t_data_game *game)
{
	draw_direction(game);
}
