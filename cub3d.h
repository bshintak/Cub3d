/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:17:31 by ralves-g          #+#    #+#             */
/*   Updated: 2023/02/15 16:09:54 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <sys/time.h>
# include "get_next_line.h"
# include "mlx-linux/mlx.h"

# define CEILING 1
# define FLOOR 0

# define C_NO 0
# define C_EA 1
# define C_SO 2
# define C_WE 3

# define ROT 0.01
# define MOVE 0.05

# define CUB_W 1000
# define CUB_H 500


//MINIMAP
# define MAP_RADIUS 100
# define MAP_UNIT 10
// # define MAP_X_CENTER 800
// # define MAP_Y_CENTER 200
# define MAP_OUTLINE 5
// # define MAP_OUTL_CLR 0xFFC500FF
# define MAP_OUTL_CLR 0x00000099
# define PLAYER_RADIUS 5
# define OFFSET 2

//KEYS
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_R 65363
# define KEY_L 65361
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
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		x_size;
	int		y_size;
}	t_data;

typedef struct	s_wall
{
	int		color;
	int		offset;
	double	angle;
}	t_wall;

typedef struct s_coords {
	double	x;
	double	y;
}	t_coords;

typedef struct s_keys
{
	int	r;
	int	l;
	int	up;
	int	down;
	int	w;
	int	a;
	int	s;
	int	d;
}	t_keys;

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
	int				hitWall;
	int				line_h;
	int				start;
	int				end;
	int				side;

	double			wall_x;
	// double			wall_x2;
	double			wall_hit;
	double			wall_hit_x;
	double			wall_hit_y;
	// double			wall_y2;
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


	// int					mp_outline;
	int					mp_x;
	int					mp_y;
	int					mp_u;
	double				mp_a;
	int					mp_color;
	
	int					w;
	int					a;
	int					s;
	int					d;
	int					r;
	int					l;
	int					up;
	int					dw;
	int					tab;
	int					alt;
	int					sft;
	double				mouse;
	int					h;
	

	t_keys				key;
}	t_cub;

//testing_prints.c
void		print_matrix(char **matrix);
void		print_vars(t_cub cub);

//cub3d.c

//map_parser.c
int			get_color(char **rgb, t_cub *cub, int *var, int type);
int			add_fc(char *line, t_cub *cub, int *var, int type);
int			check_for_var(char *line, t_cub *cub, int *var);
int			parse_vars(t_cub *cub, int var, int fd);
int			parse_file(int ac, char **av, t_cub *cub);

//map_parser2.c
int			check_name(char *name);
int			add_texture(char *line, t_cub *cub, int *var, int type);
int			add_matrix(t_cub *cub, char *line);
int			check_line(char *line, int *player);
int			parse_map(t_cub *cub, int fd);

//mapp_parser3.c
int			check_map(t_cub *cub);

//map_parser_utils.c
int			has_char(char *str, char c);
char		*get_map(int fd);
void		init_cub(t_cub *cub);
char		*ft_strdup(char *str);
int			check_equal(char *line, char *test);

//map_parser_utils2.c
char		*ft_substr(char const *str, int start, int end);
char		**ft_split(char const *str, char c);
long int	ft_atoi(const char *str);
void		free_matrix(char **matrix);

//map_parser_utils3.c
int			parse_error(char *line, t_cub *cub, char *msg);
void		free_textures(t_cub cub);

//raycasting.c
void		move_mouse(t_cub *cub);
void		ray_main(t_cub *cub);
int			raycasting_key(int key, t_cub *cub);
int			raycasting_loop(t_cub *cub);

int			close_win(void);
void		search_player(t_cub *cub);
void		search_direction(t_cub *cub);
void		search_plane(t_cub *cub);

//image_printing
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			my_mlx_pixel_put_add(t_data *data, int x, int y, int color);
void			my_mlx_pixel_put_sub(t_data *data, int x, int y, int color);
void			my_mlx_pixel_put_add2(t_data *data, int x, int y, int color);
void			my_mlx_pixel_put_inv(t_data *data, int x, int y);
void			my_mlx_pixel_put_drk(t_data *data, int x, int y);
unsigned int	get_image_color(t_data *data, int x, int y);
void			create_image(t_cub *cub, t_data *data, int size_x, int size_y);
void			draw_ray(t_cub *cub, t_ray ray, int color);
void			draw_vector(t_cub *cub, double dir_x, double dir_y, double max_size);
int				rgb_spectrum(void);

//ray_key.c
int		key_up(int key, t_cub *cub);
void	rotate(t_cub *cub, int rl, int ud);
void	move(t_cub *cub, int ws, int ad);
int		mouse_hook(int code);

//minimap.c
void	print_minimap_wall_fill(t_cub *cub, t_coords c, t_wall w, int offset);
void	minimap_wall_pixel(t_cub *cub, t_coords c, t_wall w, int mode);
void	draw_player(t_cub *cub, int height);
int		check_borders(int x, int y);

//minimap2.c
void	print_minimap_wall(t_cub *cub, int m_x, int m_y);
void	print_outline(t_cub *cub);
void	print_minimap(t_cub *cub);

//init_textures.c
int		init_textures(t_cub *cub);

//print_textures.c
void	print_textures(t_cub *cub, t_ray ray);

void	calc_side_dist(t_ray *ray, t_cub *cub);
void	calc_delta_dist(t_ray *ray);
void	hit_wall(t_cub *cub, t_ray *ray);
int		get_side(t_ray ray);

int *mp_unit(void);

#endif 