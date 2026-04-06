/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 15:40:32 by laudinot          #+#    #+#             */
/*   Updated: 2026/04/06 21:46:46 by nbaldes          ###   ########.fr       */
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

void	dda_loop(t_data_game *game)
{
	game->data_text->side = 0;
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
		if (game->data_text->mapy < 0 || game->data_text->mapy > game->y_len
			|| game->data_text->mapx < 0
			|| game->data_text->mapx
			>= (int)ft_strlen(game->map[game->data_text->mapy])
			|| game->map[game->data_text->mapy][game->data_text->mapx] == '1'
			|| game->map[game->data_text->mapy][game->data_text->mapx] == ' ')
			break ;
	}
}

double	dda_distance(t_data_game *game)
{
	game->data_text->mapx = (int)game->player->pos.x;
	game->data_text->mapy = (int)game->player->pos.y;
	if (game->player->ray_dir.x == 0)
		game->data_text->deltax = 1e30;
	else
		game->data_text->deltax = fabs(1 / game->player->ray_dir.x);
	if (game->player->ray_dir.y == 0)
		game->data_text->deltay = 1e30;
	else
		game->data_text->deltay = fabs(1 / game->player->ray_dir.y);
	init_dda_side_dist(game);
	dda_loop(game);
	if (game->data_text->side == 0)
		game->data_text->perpw = (game->data_text->mapx - game->player->pos.x
				+ (1 - game->data_text->stepx) / 2.0) / game->player->ray_dir.x;
	else
		game->data_text->perpw = (game->data_text->mapy - game->player->pos.y
				+ (1 - game->data_text->stepy) / 2.0) / game->player->ray_dir.y;
	return (game->data_text->perpw);
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
		game->data_text->perpw = dda_distance(game);
		game->data_text->screenx = x;
		calc_pix_to_draw(game);
		x++;
	}
}

static int	get_tex_pixel(t_data_game *game, int id, int x, int y)
{
	char	*src;

	src = game->tex[id].addr
		+ (y * game->tex[id].line_len + x * (game->tex[id].bpp / 8));
	return (*(int *)src);
}

void	draw_column_pixels(t_data_game *game)
{
	int		i;
	int		tex_id;
	int		tex_y;
	int		color;
	double	tex_step;

	tex_id = game->data_text->tex_id;
	if (game->data_text->lineheight > 0)
		tex_step = (double)game->tex_h[tex_id]
			/ (double)game->data_text->lineheight;
	else
		tex_step = 0;
	game->tex_pos = (game->data_text->drawstart - SCREEN_HEIGHT / 2
			+ game->data_text->lineheight / 2) * tex_step;
	i = 0;
	while (i < game->data_text->drawstart)
	{
		img_pix_put(&game->image, game->data_text->screenx, i,
			game->data_text->sky_color);
		i++;
	}
	while (i <= game->data_text->drawend && game->data_text->lineheight > 0)
	{
		tex_y = (int)game->tex_pos % game->tex_h[tex_id];
		if (tex_y < 0)
			tex_y = 0;
		game->tex_pos += tex_step;
		color = get_tex_pixel(game, tex_id, game->data_text->tex_x, tex_y);
		if (game->data_text->side == 1)
			color = (color >> 1) & 0x7F7F7F;
		img_pix_put(&game->image, game->data_text->screenx, i, color);
		i++;
	}
	while (i < SCREEN_HEIGHT)
	{
		img_pix_put(&game->image, game->data_text->screenx, i,
			game->data_text->floor_color);
		i++;
	}
}

static int	rgb_to_hex(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

static void	select_texture(t_data_game *game)
{
	if (game->data_text->side == 0)
	{
		if (game->player->ray_dir.x > 0)
			game->data_text->tex_id = EA;
		else
			game->data_text->tex_id = WE;
	}
	else
	{
		if (game->player->ray_dir.y > 0)
			game->data_text->tex_id = SO;
		else
			game->data_text->tex_id = NO;
	}
}


static void	calc_tex_x(t_data_game *game)
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
	if (game->data_text->tex_x >= game->tex_w[tex_id])
		game->data_text->tex_x = game->tex_w[tex_id] - 1;
	if (game->data_text->side == 0 && game->player->ray_dir.x < 0)
		game->data_text->tex_x = game->tex_w[tex_id]
			- game->data_text->tex_x - 1;
	if (game->data_text->side == 1 && game->player->ray_dir.y > 0)
		game->data_text->tex_x = game->tex_w[tex_id]
			- game->data_text->tex_x - 1;
}

void	calc_pix_to_draw(t_data_game *game)
{
	game->data_text->lineheight = (int)(SCREEN_HEIGHT / game->data_text->perpw);
	game->data_text->drawstart = -game->data_text->lineheight
		/ 2 + SCREEN_HEIGHT / 2;
	game->data_text->drawend = game->data_text->lineheight
		/ 2 + SCREEN_HEIGHT / 2;
	if (game->data_text->drawstart < 0)
		game->data_text->drawstart = 0;
	if (game->data_text->drawend >= SCREEN_HEIGHT)
		game->data_text->drawend = SCREEN_HEIGHT - 1;
	game->data_text->floor_color = rgb_to_hex(game->colors[0],
			game->colors[1], game->colors[2]);
	game->data_text->sky_color = rgb_to_hex(game->colors[3],
			game->colors[4], game->colors[5]);
	select_texture(game);
	calc_tex_x(game);
	draw_column_pixels(game);
}
