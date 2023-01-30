/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:17:31 by ralves-g          #+#    #+#             */
/*   Updated: 2023/01/30 18:46:48 by bshintak         ###   ########.fr       */
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

# define ROT 0.2
# define MOVE 0.2

# define CUB_W 1000
# define CUB_H 500

# define MAP_W 1920
# define MAP_H 1080
# define MAP_S_Y 100
# define MAP_S_X 100
# define MAP_RADIUS 200
# define MAP_UNIT 10
# define MAP_X_CENTER 1000
# define MAP_Y_CENTER 200
# define MAP_OUTLINE 5
# define PLAYER_RADIUS 5

# define R_OFFSET 3
# define G_OFFSET R_OFFSET + R_OFFSET
# define B_OFFSET G_OFFSET + R_OFFSET

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_R 65363
# define KEY_L 65361

typedef struct s_ray{
	int				i;
	double			camera_x;
	double			perpendicular;
	double			ray_dir_x;
	double			ray_dir_y;
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
}	t_ray;

typedef struct s_cub {
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
	int					key_w;
	int					key_a;
	int					key_s;
	int					key_d;
	int					key_l;
	int					key_r;
	char				**map;
	void				*mlx;
	void				*mlx_w;
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
void	ray_main(t_cub *cub);
int		raycasting_loop(t_cub *cub);

//ray_key.c
int		raycasting_key(int key, t_cub *cub);

//close.c
int		close_win(void);

//search.c
void	search_player(t_cub *cub);
void	search_direction(t_cub *cub);
void	search_plane(t_cub *cub);

//delta_side_dist.c
void	calc_delta_dist(t_ray *ray);
void	calc_side_dist(t_ray *ray, t_cub *cub);

//hit_wall.c
void	hit_wall(t_cub *cub, t_ray *ray);

//put_color.c
void	put_color(t_ray *ray, t_cub *cub);

#endif 