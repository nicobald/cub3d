/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbaldes <nbaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 20:09:20 by nbaldes           #+#    #+#             */
/*   Updated: 2026/03/16 20:11:06 by nbaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_parsing(t_env *env, char ***text, char ***map)
{
	free(env->type);
	free_tab(&env->tab);
	free_tab(map);
	free_tab(text);
	return ;
}
