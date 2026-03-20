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

# define NO		0
# define SO		1
# define WE		2
# define EA		3
# define F		4
# define C		5
# define MAP	6
# define EMP	7
# define STR	8
# define GREEN 0x00FF7F
# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define RED   0xFF0033
# define CUSTOM   0xFFEE33
// # ifndef COL_SIZE
// #  define COL_SIZE 32
// # endif

# define FALSE 0
# define TRUE 1
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

typedef struct player
{
	int		pos_x;
	int		pos_y;
    double 		dir_x; // dirrection du regard
    double 		dir_y;
    double 		plane_x; // champ de vision FOV
    double 		plane_y;
	int		x_pixel_position;
	int		y_pixel_position;
	char	orientation;
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
	char	*mlx_adress;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
}	t_window;

typedef struct s_env
{
	int			nb_line;
	char		**tab;
	int			*type;
	t_count		count;

}				t_env;

typedef struct s_data_game
{
	char		**text;
	char		**map;
	int			x_pixel_per_unit;	// deviendra float?
	int			y_pixel_per_unit;   //SCREEN_WIDTH / game->x_len
	int			x_len;				// longueur x du tableau 
	int			y_len;
	int			*colors;
	t_player	*player;
	t_window	*win;
}				t_data_game;

//check_map
void			fill_text(int *type, int key, char ***new_tab, char **old_tab);
int				fill_map(int *type, char ***map, char **tab);
int				check_flline_map(int i, int j, char **map, int nb_line);
int				check_oth_line_map(int i, int j, char **map);
int				check_line_map(int i, int j, char **map, int nb_line);

//error_file
int				error_file(t_env *env, char ***text, char ***map);

//parse_args
int				check_args(char **argv);
int				check_access(char *file);

//parse_file
int				count_line_file(char *file, int *nb_line);
int				fill_tab_file(char *file, int nb_line, char ***tab);
int				parse_file(t_env *env, char ***text, char ***map);
void			parse_text(int *type, t_count *count, int nb_line);

//parse_map_info
void			parse_map_info(t_data_game *game);

//parse_type
int				parse_type(char *line);

//utils
char			*get_next_line(int fd);
int				alloc_tab(char ***tab, int nb_line);
void			free_tab(char ***tab);
int				tab_is_digit(char **tab);
int				count_words(const char *s);
char			*second_word_dup(char *s);
void			free_parsing(t_env *env, char ***text, char ***map, t_player *player);
int				split_check_color(char *line);
char			*ft_strrtrim(char const *s1, char const *set);
void			print_tab(char **str);

//mlx
int				create_window(t_data_game *game);
#endif