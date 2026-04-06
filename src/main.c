/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:57:33 by nbaldes           #+#    #+#             */
/*   Updated: 2026/04/06 21:16:59 by nbaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	init_env(t_env *env, t_data_game *game)
{
	game->player = malloc(sizeof(t_player));
	if (!game->player)
		printf("Malloc error\n");
	env->nb_line = 0;
	env->count.no_count = 0;
	env->count.so_count = 0;
	env->count.we_count = 0;
	env->count.ea_count = 0;
	env->count.f_count = 0;
	env->count.c_count = 0;
	env->count.str_count = 0;
	env->tab = NULL;
	env->type = NULL;
	game->text = NULL;
	game->map = NULL;
	game->win = malloc(sizeof(t_window));
	if (!game->win)
		printf("Malloc error\n");
	return (0);
}

int	parsing(char **argv, t_env *env, t_data_game *game)
{
	if (check_args(argv) == 1)
		return (1);
	if (count_line_file(argv[1], &env->nb_line) == 1
		|| fill_tab_file(argv[1], env->nb_line, &env->tab) == 1)
		return (1);
	if (parse_file(env, &game->text, &game->map) == 1)
		return (1);
	parse_map_info(game);
	return (0);
}

int	init_game(t_data_game *game)
{
	game->key = malloc(sizeof(t_key));
	if (!game->key)
		printf("Malloc error\n");
	game->data_text = malloc(sizeof(t_texturing));
	if (!game->data_text)
		printf("Malloc error\n");
	game->win->mlx_ptr = NULL;
	game->win->win_ptr = NULL;
	if (game->player_start_dir == 'N')
		game->player->orientation = 270;
	else if (game->player_start_dir == 'S')
		game->player->orientation = 90;
	else if (game->player_start_dir == 'W')
		game->player->orientation = 180;
	else if (game->player_start_dir == 'E')
		game->player->orientation = 0;
	game->key->w_key = 0;
	game->key->a_key = 0;
	game->key->d_key = 0;
	game->key->s_key = 0;
	game->key->left_key = 0;
	game->key->right_key = 0;
	game->key->escape_key = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_env		env;
	t_data_game	game;

	(void)argc;
	if (init_env(&env, &game))
		return (1);
	if (parsing(argv, &env, &game) == 1)
	{
		free_parsing(&env, &game.text, &game.map, game.player);
		return (1);
	}
	if (init_game(&game))
		return (1);
	create_window(&game);
	return (0);
}
