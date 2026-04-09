/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 19:09:18 by nbaldes           #+#    #+#             */
/*   Updated: 2026/04/09 11:51:51 by nbaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	draw_image(t_data_game *game)
{
	dda(game);
	print_map(game);
	draw_grille(game);
	draw_player(game);
	draw_direction(game);
	mlx_put_image_to_window(game->win->mlx_ptr, game->win->win_ptr,
		game->image.mlx_img, 0, 0);
	return (0);
}

int	choose_color(char c)
{
	if (c == '1')
		return (GREEN);
	else if (c == '0')
		return (WHITE);
	else if (c == ' ' || (c >= 9 && c <= 13))
		return (RED);
	else if (c == 'N' || c == 'S' || c == 'W' || c == 'E' )
		return (WHITE);
	return (0);
}

void	draw_grille(t_data_game *game)
{
	int	x;
	int	y;
	int	mini_w;
	int	mini_h;

	mini_w = SCREEN_WIDTH / 4;
	mini_h = SCREEN_HEIGHT / 4;
	x = game->x_pixel_per_unit;
	while (x < mini_w)
	{
		y = 0;
		while (++y < mini_h)
			img_pix_put(&game->image, x, y, BLACK);
		x += game->x_pixel_per_unit;
	}
	y = game->y_pixel_per_unit;
	while (y < mini_h)
	{
		x = 0;
		while (++x < mini_w)
			img_pix_put(&game->image, x, y, BLACK);
		y += game->y_pixel_per_unit;
	}
}

void	draw_texture(t_data_game *game, int x, int y)
{
	int	i;
	int	j;
	int	x_start;
	int	y_start;

	i = 0;
	x_start = (x * game->x_pixel_per_unit);
	y_start = (y * game->y_pixel_per_unit);
	while (i < game->y_pixel_per_unit)
	{
		j = 0;
		while (j < game->x_pixel_per_unit)
		{
			img_pix_put(&game->image,
				x_start + j,
				y_start + i,
				choose_color(game->map[y][x]));
			j++;
		}
		i++;
	}
}

void	draw_player(t_data_game *game)
{
	int	x_pixel;
	int	y_pixel;
	int	i;

	x_pixel = ((game->player->pos.x / (game->x_len + 1))
			* SCREEN_WIDTH) / 4;
	y_pixel = ((game->player->pos.y / (game->y_len + 1))
			* SCREEN_HEIGHT) / 4;
	i = 6;
	while (i >= -6)
	{
		img_pix_put(&game->image, x_pixel + i, y_pixel + i, RED);
		img_pix_put(&game->image, x_pixel - i, y_pixel + i, RED);
		i--;
	}
}
