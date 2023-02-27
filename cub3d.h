/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:17:31 by ralves-g          #+#    #+#             */
/*   Updated: 2023/02/25 16:46:27 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// (cub->m && (x <= cub->mp_x - MAP_RADIUS || x >= cub->mp_x + MAP_RADIUS
// 			|| y <= cub->mp_y - MAP_RADIUS || y >= cub->mp_y + MAP_RADIUS))
#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <sys/time.h>
# include "get_next_line.h"
# include "mlx-linux/mlx.h"

# define HAS_MOUSE 1
# define BATTERY_RATE 500
# define ROT 0.01
# define MOVE 0.05

# define CUB_W 1000
# define CUB_H 750

# define START "textures/start.xpm"
# define START_SELEC "textures/start_transp.xpm"
# define BACKGROUND "textures/init.xpm"
# define DOOR_TEXTURE "textures/gate_3.xpm"
# define BATTERY_TEX_F "textures/bateria_front.xpm"
# define BATTERY_TEX_R "textures/bateria_right.xpm"
# define BATTERY_TEX_B "textures/bateria_back.xpm"
# define BATTERY_TEX_L "textures/bateria_left.xpm"

# define CEILING 1
# define FLOOR 0

# define C_NO 0
# define C_EA 1
# define C_SO 2
# define C_WE 3

//MINIMAP
# define MAP_RADIUS 100
# define MAP_OUTLINE 5
# define OFFSET 2

//KEYS
# define KEY_W 119
# define KEY_A 97
# define KEY_C 99
# define KEY_S 115
# define KEY_D 100
# define KEY_E 101
# define KEY_F 102
# define KEY_L 108
# define KEY_R 114
# define KEY_M 109
# define KEY_ESC 65307
# define ARROW_R 65363
# define ARROW_L 65361
# define KEY_UP 65362
# define KEY_DW 65364
# define KEY_TAB 65289
# define KEY_ALT 65513
# define KEY_SFT 65505
# define WHEEL_UP 4
# define WHEEL_DW 5
# define MOUSE_SENSITIVITY_X 0.07
# define MOUSE_SENSITIVITY_Y 0.7

typedef struct s_data {
	void	*img;
	void	*img2;
	char	*addr;
	char	*addr2;
	int		bits_per_pixel;
	int		bits_per_pixel2;
	int		line_length;
	int		line_length2;
	int		endian;
	int		endian2;
	int		x_size;
	int		x_size2;
	int		y_size;
	int		y_size2;
}	t_data;

typedef struct s_wall
{
	int		color;
	int		offset;
	double	angle;
}	t_wall;

typedef struct s_coords {
	double	x;
	double	y;
	double	n_x;
	double	n_y;
	int		ix;
	int		iy;
}	t_coords;

typedef struct s_anim
{
	void			*img;
	struct s_anim	*next;
}				t_anim;

typedef struct s_ray{
	double			size;
	int				i;
	double			camera_x;
	double			perpendicular;
	double			ray_dir_x;
	double			ray_dir_y;
	double			map_dir_x;
	double			map_dir_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			side_dist_x;
	double			side_dist_y;
	double			steps_x;
	double			steps_y;
	int				map_x;
	int				map_y;
	int				hit_wall;
	int				line_h;
	int				start;
	int				end;
	int				side;
	int				t_walls;
	int				t_walls_parse;
	double			wall_x;
	double			wall_hit;
	double			wall_hit_x;
	double			wall_hit_y;
}	t_ray;

typedef struct s_cub {
	char				*walls[4];
	t_data				wall_t[4];
	unsigned int		color[2];
	int					color_check[2];
	int					check_f;
	double				pos_x;
	double				pos_y;
	char				direction;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;
	char				**map;
	void				*mlx;
	void				*mlx_w;
	t_data				frame;
	int					mp_x;
	int					mp_y;
	int					mp_u;
	double				mp_a;
	int					mp_color;
	int					parsing_doors;
	t_data				doors;
	void				*background;
	void				*start;
	void				*start_selected;
	int					w;
	int					a;
	int					s;
	int					d;
	int					r;
	int					m;
	int					f;
	int					l;
	double				f_euclidean;
	int					battery;
	int					a_r;
	int					a_l;
	int					up;
	int					dw;
	int					tab;
	int					alt;
	int					sft;
	double				mouse;
	int					h;
	unsigned long		t_start;
	unsigned long		t_now;
	t_data				collec;
	t_data				collec_l[4];
	int					parsing_collectible;
	int					parsing_collectible2;
	int					num_collectible;
}	t_cub;

//cub3d.c
int				game(t_cub *cub);
void			free_starting(t_cub *cub);

//testing_prints.c
void			print_matrix(char **matrix);
void			print_vars(t_cub cub);

//raycasting.c
int				get_side(t_ray ray);
int				raycasting_loop(t_cub *cub);
void			raycasting(t_cub *cub, t_ray *ray, int opt);
void			minimap_raycasting(t_cub *cub, t_ray *ray);

//map_parser.c
int				get_color(char **rgb, t_cub *cub, int *var, int type);
int				add_fc(char *line, t_cub *cub, int *var, int type);
int				check_for_var(char *line, t_cub *cub, int *var);
int				parse_vars(t_cub *cub, int var, int fd);
int				parse_file(int ac, char **av, t_cub *cub);

//map_parser2.c
int				check_name(char *name);
int				add_texture(char *line, t_cub *cub, int *var, int type);
int				add_matrix(t_cub *cub, char *line);
int				check_line(char *line, int *player);
int				parse_map(t_cub *cub, int fd);

//map_parser3.c
int				check_map(t_cub *cub);

//map_parser_utils.c
int				has_char(char *str, char c);
char			*get_map(int fd);
void			init_cub(t_cub *cub);
char			*ft_strdup(char *str);
int				check_equal(char *line, char *test);

//map_parser_utils2.c
char			*ft_substr(char const *str, int start, int end);
char			**ft_split(char const *str, char c);
long int		ft_atoi(const char *str);
void			free_matrix(char **matrix);

//map_parser_utils3.c
int				parse_error(char *line, t_cub *cub, char *msg);
void			free_textures_char(t_cub cub);

//hooks_and_inits.c
void			fun_ray(t_cub *cub);
void			ray_main(t_cub *cub);

//move_mouse.c
void			move_mouse(t_cub *cub);

//close.c
int				close_win(t_cub *cub);

//search.c
void			search_plane(t_cub *cub);
void			search_player(t_cub *cub);
void			search_direction(t_cub *cub);

//image_printing.c
void			draw_vector(t_cub *cub, double dir_x, double dir_y, \
		double max_size);
void			create_image(t_cub *cub, t_data *data, int size_x, int size_y);
void			draw_ray(t_cub *cub, t_ray ray, int color);

//rgb_spectrum.c
int				rgb_spectrum(void);
void			rgb_spectrum2(int *red, int *green, int *blue, int angle);
void			rgb_spectrum3(int *red, int *green, int *blue, int angle);

//my_mlx_pixel.c
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			my_mlx_pixel_put_add(t_data *data, int x, int y, int color);
void			my_mlx_pixel_put_sub(t_data *data, int x, int y, int color);
void			my_mlx_pixel_put_inv(t_data *data, int x, int y);

//my_mlx_pixel2.c
unsigned int	get_image_color(t_data *data, int x, int y);
void			my_mlx_pixel_put_drk(t_data *data, int x, int y);
void			my_mlx_pixel_put_door(t_data *data, int x, int y);

//ray_key.c
int				key_up(int key, t_cub *cub);
void			verif_key(int key, t_cub *cub);
void			show_hide_mouse(int key, t_cub *cub);
int				raycasting_key(int key, t_cub *cub);

//rotate.c
void			rotate(t_cub *cub, int rl, int ud);

//move_player.c
void			move(t_cub *cub, int ws, int ad);
int				mouse_hook(int code);

//minimap.c
int				check_borders(int x, int y);
void			draw_player(t_cub *cub, int height);
void			print_minimap_wall_fill(t_cub *cub, t_coords c, t_wall w, \
		int offset);
void			minimap_wall_pixel(t_cub *cub, t_coords c, t_wall w, int mode);
void			print_outline2(t_cub *cub, int x, int y, int test);

//minimap2.c
void			print_minimap_wall(t_cub *cub, int m_x, int m_y);
void			print_outline(t_cub *cub);
void			print_minimap(t_cub *cub);
void			print_map_door(t_cub *cub);
void			print_map_door2(t_cub *cub, int m_x, int m_y, char chr);

//init_textures.c
void			free_textures(t_cub *cub);
int				init_textures(t_cub *cub);

//init_textures2.c
void			init_textures_null(t_cub *cub);

//print_textures.c
void			ceiling_color(t_cub *cub, t_ray *ray, double *start);
void			floor_color(t_cub *cub, t_ray *ray);
void			print_textures(t_cub *cub, t_ray ray);
void			reflections(t_cub *cub, t_ray *ray, double *start, int *side);

//calc.c
void			calc_side_dist(t_ray *ray, t_cub *cub);
void			calc_delta_dist(t_ray *ray);

//hit_wall.c
void			hit_wall(t_cub *cub, t_ray *ray);
void			hit_t_wall(t_cub *cub, t_ray *ray);
void			hit_m_wall(t_cub *cub, t_ray *ray);
void			hit_c_wall(t_cub *cub, t_ray *ray);

//pseudo_global.c
int				*mp_unit(void);
int				*starting_screen(void);
t_cub			*mouse_cub(void);

//doors.c
void			open_close_door(t_cub *cub);
void			pick_collectible(t_cub *cub);

//minimap_static.c
void			minimap_wall_pixel_s(t_cub *cub, t_coords c, t_wall w, \
				int mode);
void			print_minimap_wall_s(t_cub *cub, int m_x, int m_y);
void			print_minimap_s(t_cub *cub);
void			print_map_door_s(t_cub *cub);
void			print_map_door2_s(t_cub *cub, int m_x, int m_y, char chr);

//minimap_static2.c
void			draw_player_s(t_cub *cub, int height);

//minimap_static3.c
void			minimap_loop_s(t_cub *cub, t_ray *ray);
void			minimap_raycasting_s(t_cub *cub, t_ray *ray);

//flashlight.c
double			flashlight_euclidean(t_cub *cub, t_ray *ray);
void			print_battery(t_cub *cub);
unsigned long	time_ms(void);
void			count_battery(t_cub *cub);

//print_transparent
void			print_textures_t(t_cub *cub, t_ray ray);
void			textures_t(t_cub *cub, t_ray *ray, double *start);
void			reflections_t(t_cub *cub, t_ray *ray, double *start);
void			transparency_loop(t_cub *cub, t_ray *ray);
void			print_textures_c(t_cub *cub, t_ray ray);
void			textures_c(t_cub *cub, t_ray *ray, double *start);
void			reflections_c(t_cub *cub, t_ray *ray, double *start);

//collectible.c
void			print_map_collectible(t_cub *cub);
int				init_collectible(t_cub *cub);
void			print_map_collectible2_s(t_cub *cub, int m_x, int m_y, \
	char chr);
void			print_map_collectible_s(t_cub *cub);

//collectible2.c
int				init_collectible2(t_cub *cub);
int				check_collectible(t_cub *cub);
void			free_collect(t_cub *cub);
void			animate_collec(t_cub *cub);

#endif
