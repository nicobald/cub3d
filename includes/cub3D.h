/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utilisateur <utilisateur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 18:39:41 by nbaldes           #+#    #+#             */
/*   Updated: 2026/03/05 17:08:17 by utilisateur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// # ifndef COL_SIZE
// #  define COL_SIZE 32
// # endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

// # ifndef ROW_SIZE
// #  define ROW_SIZE 32
// # endif

// # include "./minilibx-linux/mlx.h"
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>

// typedef struct s_point
// {
// 	int		x;
// 	int		y;
// }			t_point;

typedef struct s_env
{
    int     nb_line;
}			t_env;

char	*get_next_line(int fd);



#endif
