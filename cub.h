/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 18:27:07 by slamhaou          #+#    #+#             */
/*   Updated: 2026/01/16 16:31:23 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
#include <stdbool.h>

# define COLORS 1
# define PATH 2
# define WIDTH 800
# define HEIGHT 600
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
#  define TotalColrsTxtur 6
# endif

typedef struct s_img
{
	mlx_image_t	*img_ptr;
	int			*pixels;
	int			width;
	int			height;
}				t_img;

typedef struct s_map
{
	char		**map;
	int			map_w;
	int			map_h;
}				t_map;

typedef struct s_gun {
    mlx_image_t *frames[5]; 
    int         current_frame;
    bool        is_shooting;
    double      last_time; 
} t_gun;

typedef	struct path
{
	char c;
	int fd;
	char *texter;
	struct path	*next;
} t_path;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	int			r_angle;
	int			r_speed;
	int			t_direction;

}				t_player;

typedef struct data_file_cub
{
	int			**clr;
	t_path		 *path;
	t_path		 *list;
	//char		**info;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	mlx_t		*mlx;
	t_gun	gun;
	mlx_image_t	*img;
	t_map		map_info;
	t_player	player;
	t_img		texture[4];
}				t_data;

typedef struct s_ray
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			side;
}				t_ray;


////////////////////////// PARS //////////////////

int	start_pars(char *str, t_data *data);
char	*ft_strjoin(char *s1, char *s2);
char	*str_dup(char *s);
char	*get_next_line(int fd);
int		ft_strlen(char *str);
int		str_cmp(char *s1, char *s2);
int		serch(char *str, char c);
void	err_msg(char *str, t_data *data);
void	ft_fre(char **str);
char	**ft_split(char *str, char sep);
int		lin_is_sps(char *str);
int		ft_atoi(const char *str);
t_path	*ft_lstnew(void);
void	ft_lstadd_back(t_path **lst, t_path *new);
void	ft_lstclear(t_path **lst);

/////////////////////////////-----check----------//////////////

int	check_color(char *str, t_data *data, char c, int i);
int	color_or_paht(char *str);
int s_w_e_n(char c);
char	*skip_spc(char *str);
int	empt_lin(char *lin);
int check_put(char c, char *str, t_data *data);
int	wall_check(char *str, char c);
int check_path_put(char *str, t_data *data);
int	check_lin(char *str);
void	free_data(t_data *data);
int		check_lin_p_c(char *lin, t_data *data);
void	search_replace(char c, char **arr);
/////////////////////////-----------maps------------///////////

int check_map(char **map);
int	get_map(t_data *data, int fd);
char **get_tst_map(char **map, t_data *data);
int	 how_many_pl(char *p, char *str, int *coun);
void	ft_free_int(int **tab, int size);
char	*take_lin_data(int fd);

//-----------------------------raycasting----------------------------//
void	draw_minimap(t_data *data);
unsigned int	get_minimap_color(t_data *data, int x, int y);
void	rotate_player(t_data *data, double angle);
void	move_player(t_data *data, double dx, double dy);
void	handle_input(void *param);
void mouse_hook(double xpos, double ypos, void* param);
void	raycasting_3d(t_data *data, t_ray ray);
void	render_column(t_data *data, t_ray *ray, int x, int start, int end,
		int lineH);
void	perform_dda(t_data *data, t_ray *ray);
void	set_ray_step(t_data *data, t_ray *ray);
void	init_ray(t_data *data, t_ray *ray, int x);
void	draw_ceiling_floor(t_data *data);
void	draw_square(t_data *data, int x, int y, int size, unsigned int color);
void    load_txt_gun(t_data *data);
void	load_textures(t_data *data);
void handle_shooting(void *param);
void update_gun_animation(t_data *data);
unsigned int	rgb_to_int(int r, int g, int b, int a);
void	set_direction(t_data *data, char c);
void	init_player(t_data *data);
void	render_frame(void *param);
void	update_animation(t_data *data, double current_time);
void    draw_minimap_player(t_data *data, int radius, int tile_size);
void    draw_minimap_tile(t_data *data, int x, int y, int start_x, int start_y);
void free_everything(t_data *d);

#endif