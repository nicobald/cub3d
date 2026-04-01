/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 15:40:32 by laudinot          #+#    #+#             */
/*   Updated: 2026/04/01 11:21:24 by nbaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int check_if_hit_wall(t_data_game *game, double x_pos, double y_pos)
{
	int x;
	int y;

	x = (int)x_pos;
	y = (int)y_pos;
	if (game->map[y][x] == '1')
		return (TRUE);
	else
		return (FALSE);
}

void	draw_direction(t_data_game *game)
{
	double	ray_x;
	double	ray_y;
	int		pixel_ray_x;
	int		pixel_ray_y;
	int		fov;
	int		i;
	double	t;

	fov = FOV / 2;
	i = 0;
	while (i < fov)
	{
		t = 0;
		game->player->dir_x = cos((game->player->orientation + i) * PI / 180);
		game->player->dir_y = sin((game->player->orientation + i) * PI / 180);
		ray_x = (game->player->pos_x + t * game->player->dir_x) / 4;
		ray_y = (game->player->pos_y + t * game->player->dir_y) / 4;
		while (ray_x <= game->x_len + 1 && ray_x >= 0 && ray_y <= game->y_len + 1 && ray_y >= 0)
		{
			pixel_ray_x = ((ray_x / (game->x_len + 1)) * SCREEN_WIDTH) / 4;
			pixel_ray_y = ((ray_y / (game->y_len + 1)) * SCREEN_HEIGHT) / 4;
			// mlx_pixel_put(game->win->mlx_ptr, game->win->win_ptr, pixel_ray_x, pixel_ray_y, CUSTOM);
			img_pix_put(&game->image, pixel_ray_x, pixel_ray_y, CUSTOM);
			t += 0.01;
			ray_x = (game->player->pos_x + t * game->player->dir_x);
			ray_y = (game->player->pos_y + t * game->player->dir_y);
			if (check_if_hit_wall(game, ray_x , ray_y) == TRUE)
				break ;
		}
		i++;
	}
	i = 0;
	while (i > -fov)
	{
		t = 0;
		game->player->dir_x = cos((game->player->orientation + i) * PI / 180);
		game->player->dir_y = sin((game->player->orientation + i) * PI / 180);
		ray_x = (game->player->pos_x + t * game->player->dir_x) / 4;
		ray_y = (game->player->pos_y + t * game->player->dir_y) / 4;
		while (ray_x <= game->x_len + 1 && ray_x >= 0 && ray_y <= game->y_len + 1 && ray_y >= 0)
		{
			pixel_ray_x = ((ray_x / (game->x_len + 1)) * SCREEN_WIDTH) / 4;
			pixel_ray_y = ((ray_y / (game->y_len + 1)) * SCREEN_HEIGHT) / 4;
			// mlx_pixel_put(game->win->mlx_ptr, game->win->win_ptr, pixel_ray_x, pixel_ray_y, CUSTOM);
			img_pix_put(&game->image, pixel_ray_x, pixel_ray_y, CUSTOM);
			t += 0.01;
			ray_x = (game->player->pos_x + t * game->player->dir_x);
			ray_y = (game->player->pos_y + t * game->player->dir_y);
			if (check_if_hit_wall(game, ray_x , ray_y) == TRUE)
				break ;
		}
		i--;
	}
}
