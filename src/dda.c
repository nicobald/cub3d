/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laudinot <laudinot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 15:40:32 by laudinot          #+#    #+#             */
/*   Updated: 2026/04/01 14:42:10 by laudinot         ###   ########.fr       */
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
	int		fov;
	int		i;
	double	t;

	fov = FOV / 2;
	i = 0;
	while (i < fov)
	{
		t = 0;
		game->player->player_dir.x = cos((game->player->orientation) * PI / 180);
		game->player->player_dir.y = sin((game->player->orientation) * PI / 180);
		ray_x = (game->player->pos.x + t * game->player->player_dir.x) / 4;
		ray_y = (game->player->pos.y + t * game->player->player_dir.y) / 4;
		while (ray_x <= game->x_len + 1 && ray_x >= 0 && ray_y <= game->y_len + 1 && ray_y >= 0)
		{
			pixel_ray_x = ((ray_x / (game->x_len + 1)) * SCREEN_WIDTH) / 4;
			pixel_ray_y = ((ray_y / (game->y_len + 1)) * SCREEN_HEIGHT) / 4;
			img_pix_put(&game->image, pixel_ray_x, pixel_ray_y, CUSTOM);
			t += 0.01;
			ray_x = game->player->pos.x + t * game->player->player_dir.x;
			ray_y = game->player->pos.y + t * game->player->player_dir.y;
			if (check_if_hit_wall(game, ray_x , ray_y) == TRUE)
				break ;
		}
		i++;
	}
	i = 0;
	while (i > -fov)
	{
		t = 0;
		game->player->player_dir.x = cos((game->player->orientation + i) * PI / 180);
		game->player->player_dir.y = sin((game->player->orientation + i) * PI / 180);
		ray_x = (game->player->pos.x + t * game->player->player_dir.x) / 4;
		ray_y = (game->player->pos.y + t * game->player->player_dir.y) / 4;
		while (ray_x <= game->x_len + 1 && ray_x >= 0 && ray_y <= game->y_len + 1 && ray_y >= 0)
		{
			pixel_ray_x = ((ray_x / (game->x_len + 1)) * SCREEN_WIDTH) / 4;
			pixel_ray_y = ((ray_y / (game->y_len + 1)) * SCREEN_HEIGHT) / 4;
			img_pix_put(&game->image, pixel_ray_x, pixel_ray_y, CUSTOM);
			t += 0.01;
			ray_x = game->player->pos.x + t * game->player->player_dir.x;
			ray_y = game->player->pos.y + t * game->player->player_dir.y;
			if (check_if_hit_wall(game, ray_x , ray_y) == TRUE)
				break ;
		}
		i--;
	}
}


double dda_distance(t_data_game *game)
{
    game->data_text->mapX = (int)(game->player->pos.x);
    game->data_text->mapY = (int)(game->player->pos.y);

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

    if (game->player->ray_dir.x < 0)
    {
        game->data_text->stepX = -1;
        sideDistX = (game->player->pos.x - game->data_text->mapX) * deltaDistX;
    }
    else
    {
        game->data_text->stepX = 1;
        sideDistX = (game->data_text->mapX + 1.0 - game->player->pos.x) * deltaDistX;
    }

    // 🔹 STEP Y
    if (game->player->ray_dir.y < 0)
    {
        game->data_text->stepY = -1;
        sideDistY = (game->player->pos.y - game->data_text->mapY) * deltaDistY;
    }
    else
    {
        game->data_text->stepY = 1;
        sideDistY = (game->data_text->mapY + 1.0 - game->player->pos.y) * deltaDistY;
    }

    int hit = 0;
    int side;

    // 🔁 DDA LOOP
    while (hit == 0)
    {
        if (sideDistX < sideDistY)
        {
            sideDistX += deltaDistX;
            game->data_text->mapX += game->data_text->stepX;
            side = 0;
        }
        else
        {
            sideDistY += deltaDistY;
            game->data_text->mapY += game->data_text->stepY;
            side = 1;
        }
        if (game->map[game->data_text->mapY][game->data_text->mapX] == '1')
            hit = 1;
    }

    // 🎯 DISTANCE FINALE
    double perpWallDist;
    if (side == 0)
        perpWallDist = (game->data_text->mapX - game->player->pos.x + (1 - game->data_text->stepX) / 2.0) / game->player->ray_dir.x;
    else
		perpWallDist = (game->data_text->mapY - game->player->pos.y + (1 - game->data_text->stepY) / 2.0) / game->player->ray_dir.y;
    return perpWallDist;
}

void	choose_wall(t_data_game *game)
{
	// worldMap = map avec un int different pour chaque face en fonction de la position du personnage
	// int worldMap[mapWidth][mapHeight]=
// {
//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
//   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// };
// changer le switch en if else avec NO/SO/WE/EA Apres avoir refait la map.
    int color;

	switch(worldMap[game->data_text->mapX][game->data_text->mapY])
    {
    	case 1:  color = RED; 
			break; //red
    	case 2:  color = GREEN;
			break; //green
    	case 3:  color = BLUE;
			break; //blue
    	case 4:  color = WHITE;
			break; //white
    	default: color = YELLOW;
			break; //yellow
    }
	// integrer x et side dans struct pour recuperer la data
    if (side == 1)
		color = color / 2;
    verLine(x, drawStart, drawEnd, color);
}

void	dda(t_data_game *game)
{
	int	x;
	double cameraX;
	// printf("Debut de dda\n");
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
		// printf("angle = %f\n", game->player->angle);
		game->player->player_dir.x = cos(game->player->angle);
		game->player->player_dir.y = sin(game->player->angle);

		// FOV ≈ 66°
		game->player->plane.x = -game->player->player_dir.y * 0.66;
		game->player->plane.y =  game->player->player_dir.x * 0.66;
		game->data_text->perpWallDist = dda_distance(game);
		calc_pix_to_draw(game);
		choose_wall(game);
		x++;
	}
}

void calc_pix_to_draw(t_data_game *game)
{
	int h;
	int lineHeight;
	int drawStart;
	int drawEnd;
	
	printf("map.y = %d\n", game->data_text->mapY);
	printf("stepY = %d\n", game->data_text->stepY);
	h = game->data_text->mapY + (1 - game->data_text->stepY) / 2;
	printf("h = %d\n", h);
	printf("perpWallDist = %f\n", game->data_text->perpWallDist);
	lineHeight = (int)(h / game->data_text->perpWallDist);
	printf("lineHeight = %d\n", lineHeight);
    drawStart = -lineHeight / 2 + h / 2;
    drawEnd = lineHeight / 2 + h / 2;
    if(drawStart < 0)
		drawStart = 0;
    if(drawEnd >= h)
		drawEnd = h - 1;
	printf("drawStart = %d, drawEnd = %d\n", drawStart, drawEnd);
}

// void texturing(t_data_game *game)
// {
	
// }

// stepX/stepY
// perpWallDist
