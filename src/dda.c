/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laudinot <laudinot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 15:40:32 by laudinot          #+#    #+#             */
/*   Updated: 2026/04/01 12:50:02 by laudinot         ###   ########.fr       */
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
	else
		return (FALSE);
}

void	draw_direction(t_data_game *game)
{
	double	ray_x;
	double	ray_y;
	int		pixel_ray_x;
	int		pixel_ray_y;
	// int		fov;
	// int		i;
	double	t;

	// fov = FOV / 2;
	// i = 0;
	// while (i < fov)
	// {
		t = 0;
		game->player->player_dir.x = cos((game->player->orientation) * PI / 180);
		game->player->player_dir.y = sin((game->player->orientation) * PI / 180);
		ray_x = game->player->pos.x + t * game->player->player_dir.x;
		ray_y = game->player->pos.y + t * game->player->player_dir.y;
		while (ray_x <= game->x_len + 1 && ray_x >= 0 && ray_y <= game->y_len + 1 && ray_y >= 0)
		{
			pixel_ray_x = (ray_x / (game->x_len + 1)) * SCREEN_WIDTH;
			pixel_ray_y = (ray_y / (game->y_len + 1)) * SCREEN_HEIGHT;
			mlx_pixel_put(game->win->mlx_ptr, game->win->win_ptr, pixel_ray_x, pixel_ray_y, CUSTOM);
			t += 0.01;
			ray_x = game->player->pos.x + t * game->player->player_dir.x;
			ray_y = game->player->pos.y + t * game->player->player_dir.y;
			// if (check_if_hit_wall(game, ray_x , ray_y) == TRUE)
			// 	break ;
		}
		// i++;
	// // }
	// i = 0;
	// while (i > -fov)
	// {
	// 	t = 0;
	// 	game->player->dir.x = cos((game->player->orientation + i) * PI / 180);
	// 	game->player->dir.y = sin((game->player->orientation + i) * PI / 180);
	// 	ray_x = game->player->pos.x + t * game->player->dir.x;
	// 	ray_y = game->player->pos.y + t * game->player->dir.y;
	// 	while (ray_x <= game->x_len + 1 && ray_x >= 0 && ray_y <= game->y_len + 1 && ray_y >= 0)
	// 	{
	// 		pixel_ray_x = (ray_x / (game->x_len + 1)) * SCREEN_WIDTH;
	// 		pixel_ray_y = (ray_y / (game->y_len + 1)) * SCREEN_HEIGHT;
	// 		mlx_pixel_put(game->win->mlx_ptr, game->win->win_ptr, pixel_ray_x, pixel_ray_y, CUSTOM);
	// 		t += 0.01;
	// 		ray_x = game->player->pos.x + t * game->player->dir.x;
	// 		ray_y = game->player->pos.y + t * game->player->dir.y;
	// 		if (check_if_hit_wall(game, ray_x , ray_y) == TRUE)
	// 			break ;
	// 	}
	// 	i--;
	// }
}


double dda_distance(t_data_game *game)
{
    int mapX = (int)(game->player->pos.x);
    int mapY = (int)(game->player->pos.y);

    double deltaDistX;
    double deltaDistY;

    if (game->player->ray_dir.x == 0)
        deltaDistX = 1e30;
    else
        deltaDistX = fabs(1 / game->player->ray_dir.x);

    if (game->player->ray_dir.y == 0)
        deltaDistY = 1e30;
    else
        deltaDistY = fabs(1 / game->player->ray_dir.y);

    double sideDistX;
    double sideDistY;

    int stepX;
    int stepY;

    // 🔹 STEP X
    if (game->player->ray_dir.x < 0)
    {
        stepX = -1;
        sideDistX = (game->player->pos.x - mapX) * deltaDistX;
    }
    else
    {
        stepX = 1;
        sideDistX = (mapX + 1.0 - game->player->pos.x) * deltaDistX;
    }

    // 🔹 STEP Y
    if (game->player->ray_dir.y < 0)
    {
        stepY = -1;
        sideDistY = (game->player->pos.y - mapY) * deltaDistY;
    }
    else
    {
        stepY = 1;
        sideDistY = (mapY + 1.0 - game->player->pos.y) * deltaDistY;
    }

    int hit = 0;
    int side;

    // 🔁 DDA LOOP
    while (hit == 0)
    {
        if (sideDistX < sideDistY)
        {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        }
        else
        {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }
        if (game->map[mapY][mapX] == '1')
            hit = 1;
    }

    // 🎯 DISTANCE FINALE
    double perpWallDist;

    if (side == 0)
        perpWallDist = (mapX - game->player->pos.x + (1 - stepX) / 2.0) / game->player->ray_dir.x;
    else
		perpWallDist = (mapY - game->player->pos.y + (1 - stepY) / 2.0) / game->player->ray_dir.y;
    return perpWallDist;
}

void	dda(t_data_game *game)
{
	int	x;
	double cameraX;
	printf("Debut de dda\n");
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
		game->player->ray_dir.x = game->player->player_dir.x + game->player->plane.x * cameraX;
		game->player->ray_dir.y = game->player->player_dir.y + game->player->plane.y * cameraX;
		if (fabs(game->player->ray_dir.x) < 1e-6)
			game->player->ray_dir.x = 1e-6;
		if (fabs(game->player->ray_dir.y) < 1e-6)
			game->player->ray_dir.y = 1e-6;
		game->player->angle = game->player->orientation * PI / 180.0;
		printf("angle = %f\n", game->player->angle);
		game->player->player_dir.x = cos(game->player->angle);
		game->player->player_dir.y = sin(game->player->angle);

		// FOV ≈ 66°
		game->player->plane.x = -game->player->player_dir.y * 0.66;
		game->player->plane.y =  game->player->player_dir.x * 0.66;
		game->tab_distance[x] = dda_distance(game);
		printf("%d distance = %f\n",x, game->tab_distance[x]);
		x++;
	}
}
