/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 23:53:38 by nbaldes           #+#    #+#             */
/*   Updated: 2026/04/09 13:53:45 by nbaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_args(char **argv)
{
	int		len;
	int		argc;
	char	*extention;

	argc = 0;
	while (argv[argc])
		argc++;
	if (argc != 2 || !argv[1])
	{
		ft_putstr_fd("Error: Cub3D takes exactly one argument.\n", 2);
		return (1);
	}
	len = ft_strlen(argv[1]);
	extention = &argv[1][len - 4];
	if (ft_strnstr(extention, ".cub", len) == NULL || len == 4)
	{
		ft_putstr_fd("Error: Invalid map file. Expected a .cub.\n", 2);
		return (1);
	}
	return (0);
}

int	key_press(int keycode, t_data_game *game)
{
	if (keycode == W_KEY)
		game->key->w_key = 1;
	if (keycode == A_KEY)
		game->key->a_key = 1;
	if (keycode == D_KEY)
		game->key->d_key = 1;
	if (keycode == S_KEY)
		game->key->s_key = 1;
	if (keycode == LEFT_KEY)
		game->key->left_key = 1;
	if (keycode == RIGHT_KEY)
		game->key->right_key = 1;
	if (keycode == ESCAPE_KEY)
		game->key->escape_key = 1;
	return (0);
}

int	key_release(int keycode, t_data_game *game)
{
	if (keycode == W_KEY)
		game->key->w_key = 0;
	if (keycode == A_KEY)
		game->key->a_key = 0;
	if (keycode == D_KEY)
		game->key->d_key = 0;
	if (keycode == S_KEY)
		game->key->s_key = 0;
	if (keycode == LEFT_KEY)
		game->key->left_key = 0;
	if (keycode == RIGHT_KEY)
		game->key->right_key = 0;
	if (keycode == ESCAPE_KEY)
		game->key->escape_key = 0;
	return (0);
}

int	free_game(t_data_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->tex[i].mlx_img)
			mlx_destroy_image(game->win->mlx_ptr, game->tex[i].mlx_img);
		i++;
	}
	if (game->image.mlx_img)
		mlx_destroy_image(game->win->mlx_ptr, game->image.mlx_img);
	if (game->win->win_ptr && game->win->mlx_ptr)
		mlx_destroy_window(game->win->mlx_ptr, game->win->win_ptr);
	if (game->win->mlx_ptr)
		mlx_destroy_display(game->win->mlx_ptr);
	free(game->win->mlx_ptr);
	free_tab(&game->text);
	free_tab(&game->map);
	free(game->colors);
	free(game->player);
	free(game->key);
	free(game->data_text);
	free(game->win);
	exit(0);
	return (0);
}
