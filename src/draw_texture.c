/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:20:00 by nbaldes           #+#    #+#             */
/*   Updated: 2026/04/09 18:20:00 by nbaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	select_texture(t_data_game *game)
{
	if (game->data_text->side == 0)
	{
		if (game->player->ray_dir.x > 0)
			game->data_text->tex_id = WE;
		else
			game->data_text->tex_id = EA;
	}
	else
	{
		if (game->player->ray_dir.y > 0)
			game->data_text->tex_id = NO;
		else
			game->data_text->tex_id = SO;
	}
}

void	compute_texture_x(t_data_game *game)
{
	int	tex_id;

	if (game->data_text->side == 0)
		game->data_text->wall_x = game->player->pos.y
			+ game->data_text->perpw * game->player->ray_dir.y;
	else
		game->data_text->wall_x = game->player->pos.x
			+ game->data_text->perpw * game->player->ray_dir.x;
	game->data_text->wall_x -= floor(game->data_text->wall_x);
	tex_id = game->data_text->tex_id;
	game->data_text->tex_x = (int)(game->data_text->wall_x
			* (double)game->tex_w[tex_id]);
	if (game->data_text->tex_x < 0)
		game->data_text->tex_x = 0;
	if (game->data_text->tex_x >= game->tex_w[tex_id])
		game->data_text->tex_x = game->tex_w[tex_id] - 1;
	if (game->data_text->side == 0 && game->player->ray_dir.x > 0)
		game->data_text->tex_x = game->tex_w[tex_id] - game->data_text->tex_x - 1;
	if (game->data_text->side == 1 && game->player->ray_dir.y < 0)
		game->data_text->tex_x = game->tex_w[tex_id] - game->data_text->tex_x - 1;
}

void	draw_textured_wall(t_data_game *game, int *y, double step, double *tex_pos)
{
	int	tex_y;

	while (*y <= game->data_text->drawend)
	{
		tex_y = (int)(*tex_pos);
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= game->tex_h[game->data_text->tex_id])
			tex_y = game->tex_h[game->data_text->tex_id] - 1;
		img_pix_put(&game->image, game->data_text->screenx, *y,
			*(int *)(game->tex[game->data_text->tex_id].addr
				+ (tex_y * game->tex[game->data_text->tex_id].line_len
					+ game->data_text->tex_x
					* (game->tex[game->data_text->tex_id].bpp / 8))));
		*tex_pos += step;
		(*y)++;
	}
}

void	draw_column_pixels(t_data_game *game)
{
	int		y;
	double	step;
	double	tex_pos;

	y = 0;
	step = (double)game->tex_h[game->data_text->tex_id]
		/ (double)game->data_text->lineheight;
	tex_pos = (game->data_text->drawstart - SCREEN_HEIGHT / 2
			+ game->data_text->lineheight / 2) * step;
	while (y < game->data_text->drawstart)
		img_pix_put(&game->image, game->data_text->screenx, y++,
			game->data_text->sky_color);
	draw_textured_wall(game, &y, step, &tex_pos);
	while (y < SCREEN_HEIGHT)
		img_pix_put(&game->image, game->data_text->screenx, y++,
			game->data_text->floor_color);
}
