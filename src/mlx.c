/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laudinot <laudinot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:10:14 by laudinot          #+#    #+#             */
/*   Updated: 2026/04/01 14:40:53 by laudinot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	img_pix_put(t_image *img, int x, int y, int color)
{
    char    *pixel;
    int		i;

    i = img->bpp - 8;
    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
    while (i >= 0)
    {
        /* big endian, MSB is the leftmost bit */
        if (img->endian != 0)
            *pixel++ = (color >> i) & 0xFF;
        /* little endian, LSB is the leftmost bit */
        else
            *pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
        i -= 8;
    }
}

int draw_image(t_data_game *game)
{
	print_map(game);
	draw_grille(game);
	draw_player(game);
	draw_direction(game);
	mlx_put_image_to_window(game->win->mlx_ptr, game->win->win_ptr, game->image.mlx_img, 0, 0);
	dda(game);
	// texturing(game);
	return (0);
}

int	choose_color(char c)
{
	// printf("test dans choose color case de map = %c\n", c);
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
			img_pix_put(&game->image, x, y, BLACK);
		x += game->x_pixel_per_unit;
	}
	y = game->y_pixel_per_unit;
	while (y < SCREEN_WIDTH)
	{
		x = 0;
		while (++x < SCREEN_HEIGHT)
			img_pix_put(&game->image, x, y, BLACK);
		y += game->x_pixel_per_unit;
	}
}

void	draw_texture(t_data_game *game, int x, int y)
{
	int	i;
	int	j;
	int	x_start;
	int	y_start;

	x_start = (x * game->x_pixel_per_unit);
	y_start = (y * game->y_pixel_per_unit);

	i = 0;
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
	
	// printf("pos player X : %f Y : %f\n", game->player->pos_x, game->player->pos_y);

	x_pixel = ((game->player->pos.x / (game->x_len + 1)) *  SCREEN_WIDTH) / 4;
	y_pixel = ((game->player->pos.y / (game->y_len + 1)) *  SCREEN_HEIGHT) / 4;

	i = 6;
	
	while (i >= -6)
	{
		// mlx_pixel_put(game->win->mlx_ptr, game->win->win_ptr, x_pixel + i, y_pixel + i, RED);
		// mlx_pixel_put(game->win->mlx_ptr, game->win->win_ptr, x_pixel - i, y_pixel + i, RED);
		img_pix_put(&game->image, x_pixel + i, y_pixel + i, RED);
		img_pix_put(&game->image, x_pixel - i, y_pixel + i, RED);
		i--;
	}

}

void	calculate_map(t_data_game *game)

{
	printf("debut calculate map\n");
	game->x_pixel_per_unit = (SCREEN_WIDTH / (game->x_len + 1)) / 4;
	game->y_pixel_per_unit = (SCREEN_HEIGHT / (game->y_len + 1)) / 4;
	printf("pixel = %d x %d game->x_len %d, game-> y_len = %d\n", game->x_pixel_per_unit, game->y_pixel_per_unit, game->x_len, game->y_len);
}

void	print_map(t_data_game *game)
{
	int	i;
	int	j;

	i = 0;
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
	game->image.mlx_img = mlx_new_image(game->win->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->image.addr = mlx_get_data_addr(game->image.mlx_img, &game->image.bpp, &game->image.line_len, &game->image.endian);
	mlx_hook(game->win->win_ptr, 2, 1L << 0, key_press, game);
	mlx_hook(game->win->win_ptr, 3, 1L << 1, key_release, game);
	gettimeofday(&game->time, NULL);
	game->last_time = game->time.tv_sec + game->time.tv_usec / 1000000.0;
	mlx_loop_hook(game->win->mlx_ptr, control_key, game);
	mlx_hook(game->win->win_ptr, 17, 0, free_game, game);
	mlx_loop(game->win->mlx_ptr);
	printf("apres loop\n");	
	return (0);
}
