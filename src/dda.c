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
		game->data_text->perpw = game->data_text->sidex - game->data_text->deltax;
	else
		game->data_text->perpw = game->data_text->sidey - game->data_text->deltay;
	if (game->data_text->perpw < 1e-6)
		game->data_text->perpw = 1e-6;
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

static void	draw_sky(t_data_game *game, int x, int end_y)
{
	int	y;

	y = 0;
	while (y < end_y)
		img_pix_put(&game->image, x, y++, game->data_text->sky_color);
}

static void	draw_floor(t_data_game *game, int x, int start_y)
{
	int	y;

	y = start_y;
	while (y < SCREEN_HEIGHT)
		img_pix_put(&game->image, x, y++, game->data_text->floor_color);
}

static void	draw_wall(t_data_game *game, int x, int start_y, int end_y)
{
	int		y;
	int		tex_id;
	int		tex_y;
	int		color;
	double	tex_step;
	double	tex_pos;

	tex_id = game->data_text->tex_id;
	tex_step = (double)game->tex_h[tex_id] / (double)game->data_text->lineheight;
	tex_pos = (start_y - SCREEN_HEIGHT / 2
			+ game->data_text->lineheight / 2) * tex_step;
	y = start_y;
	while (y <= end_y)
	{
		tex_y = (int)tex_pos % game->tex_h[tex_id];
		if (tex_y < 0)
			tex_y = 0;
		color = get_tex_pixel(game, tex_id, game->data_text->tex_x, tex_y);
		img_pix_put(&game->image, x, y, color);
		tex_pos += tex_step;
		y++;
	}
}

void	draw_column_pixels(t_data_game *game)
{
	int	x;
	int	start;
	int	end;

	x = game->data_text->screenx;
	start = game->data_text->drawstart;
	end = game->data_text->drawend;
	draw_sky(game, x, start);
	draw_wall(game, x, start, end);
	draw_floor(game, x, end + 1);
}

static int	rgb_to_hex(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

static void	select_texture(t_data_game *game)
{
	if (game->data_text->side == 0)
	{
		if (game->data_text->stepx > 0)
			game->data_text->tex_id = WE;
		else
			game->data_text->tex_id = EA;
	}
	else
	{
		if (game->data_text->stepy > 0)
			game->data_text->tex_id = NO;
		else
			game->data_text->tex_id = SO;
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
	if (game->data_text->side == 0 && game->player->ray_dir.x > 0)
		game->data_text->tex_x = game->tex_w[tex_id]
			- game->data_text->tex_x - 1;
	if (game->data_text->side == 1 && game->player->ray_dir.y < 0)
		game->data_text->tex_x = game->tex_w[tex_id]
			- game->data_text->tex_x - 1;
}

void	calc_pix_to_draw(t_data_game *game)
{
	int	x;

	x = game->data_text->screenx;
	game->data_text->floor_color = rgb_to_hex(game->colors[0],
			game->colors[1], game->colors[2]);
	game->data_text->sky_color = rgb_to_hex(game->colors[3],
			game->colors[4], game->colors[5]);
	if (game->data_text->perpw <= 0)
	{
		draw_sky(game, x, SCREEN_HEIGHT / 2);
		draw_floor(game, x, SCREEN_HEIGHT / 2);
		return ;
	}
	game->data_text->lineheight = (int)(SCREEN_HEIGHT / game->data_text->perpw);
	game->data_text->drawstart = SCREEN_HEIGHT / 2
		- game->data_text->lineheight / 2;
	game->data_text->drawend = SCREEN_HEIGHT / 2
		+ game->data_text->lineheight / 2;
	if (game->data_text->drawstart < 0)
		game->data_text->drawstart = 0;
	if (game->data_text->drawstart >= SCREEN_HEIGHT)
		game->data_text->drawstart = SCREEN_HEIGHT - 1;
	if (game->data_text->drawend < 0)
		game->data_text->drawend = 0;
	if (game->data_text->drawend >= SCREEN_HEIGHT)
		game->data_text->drawend = SCREEN_HEIGHT - 1;
	select_texture(game);
	calc_tex_x(game);
	draw_column_pixels(game);
}
