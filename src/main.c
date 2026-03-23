/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:57:33 by nbaldes           #+#    #+#             */
/*   Updated: 2026/03/23 15:07:30 by nbaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_env(t_env *env, t_data_game *game)
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
	return ;
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
	game->win = malloc(sizeof(t_window));
	if (!game->win)
		printf("Malloc error\n");
	game->win->win_ptr = NULL;
	game->win->mlx_ptr = NULL;
	return (0);
}

int	main(int argc, char **argv)
{
	t_env		env;
	t_data_game	game;

	(void)argc;
	init_env(&env, &game);
	if (parsing(argv, &env, &game) == 1)
	{
		free_parsing(&env, &game.text, &game.map, game.player);
		return (1);
	}
	// print_tab(game.text);
	// print_tab(game.map);
	if (init_game(&game))
		return (1);
	create_window(&game);
	// free_tab(&game.text);
	// free_tab(&game.map);
	// free(game.colors);
	// free(game.player);
	return (0);
}
