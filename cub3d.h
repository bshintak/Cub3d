/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:17:31 by ralves-g          #+#    #+#             */
/*   Updated: 2023/02/08 17:44:53 by bshintak         ###   ########.fr       */
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

# define WALL_1 0
# define WALL_2 1
# define WALL_3 2
# define WALL_4 3

# define NO 0
# define EA 1
# define SO 2
# define WE 3

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
	int		img_width;
	int		img_height;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
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
	int				i;
	double			camera_x;
	double			perpendicular;
	double			rayDir_x;
	double			rayDir_y;
	double			deltaDist_x;
	double			deltaDist_y;
	double			sideDist_x;
	double			sideDist_y;
	double			steps_x;
	double			steps_y;
	int				map_x;
	int				map_y;
	int				hitWall;
	int				line_h;
	int				start;
	int				end;
	int				side;
	int				tex_x;
	int				tex_y;
	double			tex_pos;
	double			step;
	double			wall_x;
	unsigned int	color;
}	t_ray;

typedef struct s_cub {
	t_data				tex[15];
	char				*walls[4];
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
	double				moveSpeed;
	double				rotSpeed;
	char				**map;
	void				*mlx;
	void				*mlx_w;
	t_data				frame;


	// int					mp_outline;
	int					mp_x;
	int					mp_y;
	int					mp_u;
	
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
void	move_mouse(t_cub *cub);
void	ray_main(t_cub *cub);
int		raycasting_key(int key, t_cub *cub);
int		raycasting_loop(t_cub *cub);

int		close_win(void);
void	search_player(t_cub *cub);
void	search_direction(t_cub *cub);
void	search_plane(t_cub *cub);

//image_printing
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	my_mlx_pixel_put_add(t_data *data, int x, int y, int color);
void	my_mlx_pixel_put_inv(t_data *data, int x, int y);
void	my_mlx_pixel_put_drk(t_data *data, int x, int y);
void	create_image(t_cub *cub, t_data *data, int size_x, int size_y);
void	draw_ray(t_cub *cub, t_ray *ray);

//ray_key.c
int		key_up(int key, t_cub *cub);
void	rotate(t_cub *cub, int rl, int ud);
void	move(t_cub *cub, int ws, int ad);
int		mouse_hook(int code);

//minimap.c
void	print_minimap(t_cub *cub);

void	init_images(t_cub *cub);
unsigned int	*get_img_pixel(t_data *data, int x, int y);
int *mp_unit(void);

#endif 