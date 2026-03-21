/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laudinot <laudinot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 15:40:32 by laudinot          #+#    #+#             */
/*   Updated: 2026/03/21 18:41:31 by laudinot         ###   ########.fr       */
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
	ray_x = game->player->pos_x + t * game->player->dir_x;
	ray_y = game->player->pos_y + t * game->player->dir_y;
	
	while (ray_x <= game->x_len && ray_x >= 0 && ray_y <= game->y_len && ray_y >= 0)
	{
		pixel_ray_x = (ray_x / game->x_len) * SCREEN_WIDTH;
		pixel_ray_y = (ray_y / game->y_len) * SCREEN_HEIGHT;
		printf("DOIT PRINT SUR X : %d Y : %d\n", pixel_ray_x, pixel_ray_y);
		mlx_pixel_put(game->win->mlx_ptr, game->win->win_ptr, pixel_ray_x, pixel_ray_y, CUSTOM);
		t += 0.1;
		ray_x = game->player->pos_x + t * game->player->dir_x;
		ray_y = game->player->pos_y + t * game->player->dir_y;
	}
}
void	put_direction(t_data_game *game)
{
	if (game->player->orientation == 'N')
		game->player->orientation = 90;
	else if (game->player->orientation == 'S')
		game->player->orientation = 270;
	else if (game->player->orientation == 'W')
		game->player->orientation = 180;
	else if (game->player->orientation == 'E')
		game->player->orientation = 0;
	game->player->dir_x = cos(game->player->orientation * PI / 180);
	game->player->dir_y = sin(game->player->orientation * PI / 180);
	draw_direction(game);
}
