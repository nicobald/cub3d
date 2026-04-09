/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 19:09:18 by nbaldes           #+#    #+#             */
/*   Updated: 2026/04/09 13:02:09 by nbaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	img_pix_put(t_image *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

void	calculate_map(t_data_game *game)

{
	game->x_pixel_per_unit = (SCREEN_WIDTH / (game->x_len + 1)) / 4;
	game->y_pixel_per_unit = (SCREEN_HEIGHT / (game->y_len + 1)) / 4;
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
				draw_texture(game, j, i);
			else if (game->map[i][j] == '0')
				draw_texture(game, j, i);
			else if (game->map[i][j] == 'N' || game->map[i][j] == 'S'
				|| game->map[i][j] == 'W' || game->map[i][j] == 'E')
				draw_texture(game, j, i);
			else if (game->map[i][j] == ' ')
			{
				draw_texture(game, j, i);
			}
			j++;
		}
		i++;
	}
}

static void	load_textures(t_data_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->tex[i].mlx_img = mlx_xpm_file_to_image(game->win->mlx_ptr,
				game->text[i], &game->tex_w[i], &game->tex_h[i]);
		if (!game->tex[i].mlx_img)
		{
			ft_putstr_fd("Error: cannot load texture\n", 2);
			exit(1);
		}
		game->tex[i].addr = mlx_get_data_addr(game->tex[i].mlx_img,
				&game->tex[i].bpp, &game->tex[i].line_len,
				&game->tex[i].endian);
		i++;
	}
}

int	create_window(t_data_game *game)
{
	game->win->mlx_ptr = mlx_init();
	if (game->win->mlx_ptr == 0)
		return (printf("Mlx init failed \n"));
	game->win->win_ptr = mlx_new_window(game->win->mlx_ptr,
			SCREEN_WIDTH, SCREEN_HEIGHT, "Dofus3D");
	calculate_map(game);
	game->image.mlx_img = mlx_new_image(game->win->mlx_ptr,
			SCREEN_WIDTH, SCREEN_HEIGHT);
	game->image.addr = mlx_get_data_addr(game->image.mlx_img,
			&game->image.bpp, &game->image.line_len, &game->image.endian);
	load_textures(game);
	draw_image(game);
	mlx_hook(game->win->win_ptr, 2, 1L << 0, key_press, game);
	mlx_hook(game->win->win_ptr, 3, 1L << 1, key_release, game);
	gettimeofday(&game->time, NULL);
	game->last_time = game->time.tv_sec + game->time.tv_usec / 1000000.0;
	mlx_loop_hook(game->win->mlx_ptr, control_key, game);
	mlx_hook(game->win->win_ptr, 17, 0, free_game, game);
	mlx_loop(game->win->mlx_ptr);
	return (0);
}
