/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   cub3D.h											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: utilisateur <utilisateur@student.42.fr>	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2026/03/03 18:39:41 by nbaldes		   #+#	#+#			 */
/*   Updated: 2026/03/15 20:52:20 by utilisateur	  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H


# define	NO		0
# define	SO		1
# define	WE		2
# define	EA		3
# define	F		4
# define	C		5
# define	MAP		6
# define	EMP		7
# define	STR		8

// # ifndef COL_SIZE
// #  define COL_SIZE 32
// # endif

# define BUFFER_SIZE 10
# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 800

// # ifndef ROW_SIZE
// #  define ROW_SIZE 32
// # endif


# include "libft.h"
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>

// typedef struct s_point
// {
//delta pour horientation
// 	int		x;
// 	int		y;
// }			t_point;

typedef	struct player
{
	int		x;
	int		y;
	char 	orientation;
}				t_player;


typedef struct s_count
{
	int			no_count;
	int			so_count;
	int			we_count;
	int			ea_count;
	int			f_count;
	int			c_count;
	int			str_count;
}				t_count;

typedef struct s_window 
{
	char 	*mlx_adress;
	void	*mlx_ptr;
	void	*win_ptr;
	void 	*img_ptr;
}	t_window;

typedef struct s_env
{
	int			nb_line;
	char		**tab;
	int			*type;
	t_count		count;
	t_window	*win;

}				t_env;

typedef struct s_data_game
{
	char		**text;
	char		**map;
	int			x_len;
	int			y_len;
	t_player	player;
}				t_data_game;


//error_file
int				error_file(t_env *env, char ***text, char ***map);

//parse_args
int				check_args(char **argv);
int				check_access(char *file);

//parse_file
int				count_line_file(char *file, int *nb_line);
int				fill_tab_file(char *file, int nb_line, char ***tab);
int				parse_file(t_env *env, char ***text, char ***map);

//parse_map_info
void	parse_map_info(t_data_game *game);

//parse_type
int				parse_type(char *line);

//utils
char			*get_next_line(int fd);
int				alloc_tab(char ***tab, int nb_line);
void			free_tab(char ***tab);
int				tab_is_digit(char **tab);
int				count_words(const char *s);
char			*second_word_dup(char *s);
void			free_parsing(t_env *env, char ***text, char ***map);
void			print_tab(char **str);

//mlx
int				create_window(t_env *env);
#endif