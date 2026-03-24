/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laudinot <laudinot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:10:14 by laudinot          #+#    #+#             */
/*   Updated: 2026/03/24 10:09:35 by laudinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	choose_color(char c)
{
	// printf("test dans choose color\n");
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

	x = game->x_pixel_per_unit;
	while (x < SCREEN_WIDTH)
	{
		y = 0;
		while (++y < SCREEN_HEIGHT)
			mlx_pixel_put(game->win->mlx_ptr, game->win->win_ptr, x, y, BLACK);
		x += game->x_pixel_per_unit;
	}
	y = game->y_pixel_per_unit;
	while (y < SCREEN_WIDTH)
	{
		x = 0;
		while (++x < SCREEN_HEIGHT)
			mlx_pixel_put(game->win->mlx_ptr, game->win->win_ptr, x, y, BLACK);
		y += game->x_pixel_per_unit;
	}
}

void	draw_texture(t_data_game *game, int x, int y)
{
	int	i;
	int	j;
	int	x_len_to_start_draw;
	int	y_len_to_start_draw;

	// printf("drawing x = %d y = %d\n", x, y);

	i = 0;
	x_len_to_start_draw = (x * game->x_pixel_per_unit);
	y_len_to_start_draw = (y * game->y_pixel_per_unit);
	while (i < game->y_pixel_per_unit)
	{
		// printf("%d\n", i);
		j = 0;
		// printf(" game->x_pixel_per_unit = %d\n", game->x_pixel_per_unit);
		while (j < game->x_pixel_per_unit)
		{
			// printf("j = %d, pixel to draw X = %d Y = %d\n", j, x_len_to_start_draw + j, y_len_to_start_draw + i);
			mlx_pixel_put(game->win->mlx_ptr, game->win->win_ptr,
				x_len_to_start_draw + j, y_len_to_start_draw + i,
				choose_color(game->map[y][x]));
			// usleep(100);
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
	
	printf("pos player X : %f Y : %f\n", game->player->pos_x, game->player->pos_y);

	x_pixel = ((game->player->pos_x / (game->x_len + 1)) *  SCREEN_WIDTH);
	y_pixel = ((game->player->pos_y / (game->y_len + 1)) *  SCREEN_HEIGHT);

	i = 6;
	
	while (i >= -6)
	{
		mlx_pixel_put(game->win->mlx_ptr, game->win->win_ptr, x_pixel + i, y_pixel + i, RED);
		mlx_pixel_put(game->win->mlx_ptr, game->win->win_ptr, x_pixel - i, y_pixel + i, RED);
		i--;
	}

}

void	calculate_map(t_data_game *game)
{
	game->x_pixel_per_unit = SCREEN_WIDTH / (game->x_len + 1);
	game->y_pixel_per_unit = SCREEN_HEIGHT / (game->y_len + 1);
	printf("pixel = %d x %d \n", game->x_pixel_per_unit, game->y_pixel_per_unit);
}

void	print_map(t_data_game *game)
{
	int	i;
	int	j;

	i = 0;
	// print_tab(game->map);
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == '1')
				draw_texture(game, j , i);
			else if (game->map[i][j] == '0')
				draw_texture(game, j , i);
			else if (game->map[i][j] == 'N' || game->map[i][j] == 'S' || game->map[i][j] == 'W' || game->map[i][j] == 'E')
				draw_texture(game, j , i);
			else if(game->map[i][j] == ' ')
			{
				// printf("x = %d y = %d quand rentre dans vide\n", j , i);
				draw_texture(game, j , i);
			}
			j++;
		}
		i++;
	}
	// printf("print_map terminee j = %d i = %d\n", j, i);
}

int	free_game(t_data_game *game)
{
	if (game->win->win_ptr && game->win->mlx_ptr)
		mlx_destroy_window(game->win->mlx_ptr, game->win->win_ptr);
	if (game->win->mlx_ptr)
		mlx_destroy_display(game->win->mlx_ptr);
	free(game->win->mlx_ptr);
	free_tab(&game->text);
	free_tab(&game->map);
	free(game->colors);
	free(game->player);
	exit(0);
	return (0);
}

int	create_window(t_data_game *game)
{
	game->win->mlx_ptr = mlx_init();
	if (game->win->mlx_ptr == 0)
		return (printf("Mlx init failed \n"));
	printf("adresse window->mlx_ptr = %p\n", game->win->mlx_ptr);
	game->win->win_ptr = mlx_new_window(game->win->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "Dofus3D");
	calculate_map(game);
	print_map(game);
	draw_grille(game);
	draw_player(game);
	set_direction(game);
	// env->win->img_ptr = mlx_new_image(env->win->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	// mlx_put_image_to_window(env->win->mlx_ptr, env->win->win_ptr, env->win->img_ptr, 0, 0);
	// window->mlx_adress = mlx_get_data_addr(window->img_ptr, NULL, NULL, NULL);
	mlx_hook(game->win->win_ptr, 2, 1L << 0, key_press, game);
	mlx_hook(game->win->win_ptr, 3, 1L << 1, key_release, game);
	gettimeofday(&game->time, NULL);
	game->last_time = game->time.tv_sec + game->time.tv_usec / 1000000.0;
	// printf("inital time = %f\n", game->last_time);
	mlx_loop_hook(game->win->mlx_ptr, control_key, game);
	mlx_hook(game->win->win_ptr, 17, 0, free_game, game);
	mlx_loop(game->win->mlx_ptr);
	printf("apres loop\n");	
	return (0);
}
