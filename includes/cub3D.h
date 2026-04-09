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

# define NO			0
# define SO			1
# define WE			2
# define EA			3
# define F			4
# define C			5
# define MAP		6
# define EMP		7
# define STR		8
# define W_KEY		119
# define A_KEY		97
# define D_KEY		100
# define S_KEY		115
# define LEFT_KEY	65361
# define RIGHT_KEY 	65363
# define ESCAPE_KEY 65307
# define GREEN 		0x00FF7F
# define BLACK 		0x000000
# define WHITE 		0xFFFFFF
# define RED   		0xFF0033
# define BLUE		0x000080
# define YELLOW		0xFFFF00
# define CUSTOM   	0xFFEE33
// # ifndef COL_SIZE
// #  define COL_SIZE 32
// # endif
# define FALSE 0
# define TRUE 1

# define PI	3.141592653589793
# define BUFFER_SIZE 10
# define SCREEN_WIDTH 1000
# define SCREEN_HEIGHT 1000
# define MOVE_SPEED 0.1
# define FOV 50
// # ifndef ROW_SIZE
// #  define ROW_SIZE 32
// # endif

# include "libft.h"
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include <fcntl.h>

# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/time.h>

typedef struct s_coord
{
	double	x;
	double	y;
}			t_coord;

typedef struct s_texturing
{
	int			mapx;
	int			mapy;
	int			stepx;
	int			stepy;
	int			side;
	int			screenx;
	int			lineheight;
	int			drawstart;
	int			drawend;
	int			wall_color;
	int			floor_color;
	int			sky_color;
	int			fov;
	int			i;
	int			pixel_ray_x;
	int			pixel_ray_y;
	int			tex_id;
	int			tex_x;
	double		wall_x;
	double		t;
	double		ray_x;
	double		ray_y;
	double		deltax;
	double		deltay;
	double		sidex;
	double		sidey;
	double		perpw;
}				t_texturing;

typedef struct s_player
{
	t_coord		wall_d;
	t_coord		pos;
	t_coord		player_dir;
	t_coord		ray_dir;
	t_coord		plane;
	double		orientation;
	double		angle;
}				t_player;

typedef struct s_image
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_image;

typedef struct s_key
{
	int	w_key;
	int	a_key;
	int	d_key;
	int	s_key;
	int	left_key;
	int	right_key;
	int	escape_key;
}				t_key;

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
	char			**text;
	char			**map;
	char			player_start_dir;
	int				x_pixel_per_unit;
	int				y_pixel_per_unit;
	int				x_len;
	int				y_len;
	int				*colors;
	int				tex_w[4];
	int				tex_h[4];
	double			last_time;
	double			delta_time;
	double			tex_pos;
	t_player		*player;
	t_window		*win;
	t_key			*key;
	t_image			image;
	t_image			tex[4];
	t_texturing		*data_text;
	struct timeval	time;
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

//key_hook
int				control_key(t_data_game *game);
int				key_press(int keycode, t_data_game *game);
int				key_release(int keycode, t_data_game *game);
int				rotate_left(t_data_game *game);
int				rotate_right(t_data_game *game);

//utils
char			*get_next_line(int fd);
int				alloc_tab(char ***tab, int nb_line);
void			free_tab(char ***tab);
int				tab_is_digit(char **tab);
int				count_words(const char *s);
char			*second_word_dup(char *s);
void			free_parsing(t_env *env, char ***text, char ***map,
					t_player *player);
int				split_check_color(char *line);
char			*ft_strrtrim(char const *s1, char const *set);
void			remove_first_space(char **str, int nb);
int				rgb_to_hex(int r, int g, int b);

//mlx
int				free_game(t_data_game *game);
int				create_window(t_data_game *game);
void			dda(t_data_game *game);
void			set_direction(t_data_game *game);
void			draw_direction(t_data_game *game);
void			print_map(t_data_game *game);
void			draw_grille(t_data_game *game);
void			draw_player(t_data_game *game);
void			img_pix_put(t_image *img, int x, int y, int color);
int				draw_image(t_data_game *game);

	//dda
void			texturing(t_data_game *game);
void			cast_ray(t_data_game *game);
double			dda_distance(t_data_game *game);
void			select_texture(t_data_game *game);
void			compute_texture_x(t_data_game *game);
void			draw_textured_wall(t_data_game *game, int *y, double step,
					double *tex_pos);
void			draw_column_pixels(t_data_game *game);
void			calc_pix_to_draw(t_data_game *game);

//mini_map
void			draw_texture(t_data_game *game, int x, int y);
void			init_dda(t_data_game *game);
void			dda_step(t_data_game *game);

#endif
