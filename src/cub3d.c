/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:20:45 by ralves-g          #+#    #+#             */
/*   Updated: 2023/01/25 16:52:27 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// ( x − a )^2 + ( y − b )^2 = r^2

// pow(x - cub->pos_x + CUB_W / 2 - pos_x, 2) + pow(y - cub->pos_y + CUB_W / 2 - pos_y, 2) <= 90

void	print_minimap_wall(t_cub *cub, int m_x, int m_y)
{
	int	y;
	int	x;

	y = m_y;
	while (y < m_y + MAP_UNIT)
	{
		x = m_x;
		while (x < m_x + MAP_UNIT)
		{
		// 	if ((pow(x - cub->pos_x + CUB_W / 2 - pos_y_CENTER, 2.0) + pow(y - cub->pos_y + CUB_H / 2 - MAP_Y_CENTER, 2.0)) <= pow(MAP_RADIUS, 2.0))
		// 		mlx_pixel_put(cub->mlx, cub->mlx_w, x - cub->pos_x + CUB_W / 2 + R_OFFSET, y - cub->pos_y + CUB_H / 2 + R_OFFSET, 0x55550000);
		// 	if ((pow(x - cub->pos_x + CUB_W / 2 - MAP_X_CENTER, 2.0) + pow(y - cub->pos_y + CUB_H / 2 - MAP_Y_CENTER, 2.0)) <= pow(MAP_RADIUS, 2.0))
		// 		mlx_pixel_put(cub->mlx, cub->mlx_w, x - cub->pos_x + CUB_W / 2 + G_OFFSET, y - cub->pos_y + CUB_H / 2 + G_OFFSET, 0x55005500);
		// 	if ((pow(x - cub->pos_x + CUB_W / 2 - MAP_X_CENTER, 2.0) + pow(y - cub->pos_y + CUB_H / 2 - MAP_Y_CENTER, 2.0)) <= pow(MAP_RADIUS, 2.0))
		// 		mlx_pixel_put(cub->mlx, cub->mlx_w, x - cub->pos_x + CUB_W / 2 + B_OFFSET, y - cub->pos_y + CUB_H / 2 + B_OFFSET, 0x55000055);
			if ((pow(x - cub->pos_x + CUB_W / 2 - MAP_X_CENTER, 2.0) + pow(y - cub->pos_y + CUB_H / 2 - MAP_Y_CENTER, 2.0)) <= pow(MAP_RADIUS, 2.0))
				mlx_pixel_put(cub->mlx, cub->mlx_w, x - cub->pos_x + CUB_W / 2, y - cub->pos_y + CUB_H / 2, 0x55FFFFFF);
			x++;
		}
		y++;
	}
}

void	print_minimap(t_cub *cub)
{
	int	y;
	int	x;

	y = 0;
	while (cub->map[y])
	{
		x = 0;
		while (cub->map[y][x])
		{
			// if ((pow(x - cub->pos_x + CUB_W / 2 - MAP_X_CENTER, 2.0) + pow(y - cub->pos_y + CUB_H / 2 - MAP_Y_CENTER, 2.0)) >= pow(MAP_RADIUS, 2.0) && 
			// (pow(x * MAP_UNIT - cub->pos_x + CUB_W / 2 - MAP_X_CENTER, 2.0) + pow(y * MAP_UNIT - cub->pos_y + CUB_H / 2 - MAP_Y_CENTER, 2.0)) <= pow(MAP_RADIUS + 200, 2.0))
			// 	mlx_pixel_put(cub->mlx, cub->mlx_w, x * MAP_UNIT - cub->pos_x + CUB_W / 2, y * MAP_UNIT - cub->pos_y + CUB_H / 2, 0xFFFFFFFF);
			if (cub->map[y][x] == '1')
				print_minimap_wall(cub, x, y);
			x++;
		}
		y++;
	}
	// y = MAP_Y_CENTER - MAP_RADIUS - MAP_OUTLINE;
	// while (y < MAP_Y_CENTER + MAP_RADIUS + MAP_OUTLINE)
	// {
	// 	x = MAP_X_CENTER - MAP_RADIUS - MAP_OUTLINE;
	// 	while (x < MAP_X_CENTER + MAP_RADIUS + MAP_OUTLINE)
	// 	{
	// 		printf("x[%d] y[%d]\n",  x - cub->pos_x + CUB_W / 2, y - cub->pos_y + CUB_H / 2);
	// 		if ((pow(x - MAP_X_CENTER, 2.0) + pow(y - MAP_Y_CENTER, 2.0)) >= pow(MAP_RADIUS, 2.0) && 
	// 		(pow(x - MAP_X_CENTER, 2.0) + pow(y - MAP_Y_CENTER, 2.0)) <= pow(MAP_RADIUS + MAP_OUTLINE, 2.0))
	// 			mlx_pixel_put(cub->mlx, cub->mlx_w, x, y, 0xFFC500FF);
	// 		x++;
	// 	}
	// 	y++;
	// }
}

void	search_player(t_cub *cub)
{
	int	y;
	int	x;

	y = 0;
	while (cub->map[y])
	{
		x = 0;
		while (cub->map[y][x])
		{
			if (cub->map[y][x] == 'N' || cub->map[y][x] == 'S' || 
			cub->map[y][x] == 'W' || cub->map[y][x] == 'E')
			{
				cub->pos_x = x - 1;
				cub->pos_y = y - 1;
				cub->direction = cub->map[y][x];
			}
			x++;
		}
		y++;
	}
	// printf("PLAYER X[%d] Y[%d]\n", cub->pos_x, cub->pos_y);
}

void	move_player(t_cub *cub, int x, int y)
{
	cub->pos_x += x * 10;
	cub->pos_y += y * 10;
}

int	scuffed_move_down(int key, t_cub *cub)
{
	cub->key_w = 0;
	cub->key_a = 0;
	cub->key_s = 0;
	cub->key_d = 0;
	// printf("key = %d\n", key);
	if (key == KEY_ESC)
		exit(0);
	if (key == KEY_W)
		cub->key_w = 1;
	if (key == KEY_A)
		cub->key_a = 1;
	if (key == KEY_S)
		cub->key_s = 1;
	if (key == KEY_D)
		cub->key_d = 1;
	move_player(cub, cub->key_d - cub->key_a, cub->key_s - cub->key_w);
	mlx_clear_window(cub->mlx, cub->mlx_w);
	print_minimap(cub);
	return (0);
}

int	scuffed_move_up(int key, t_cub *cub)
{
	if (key == KEY_W)
		cub->key_w = 0;
	if (key == KEY_A)
		cub->key_a = 0;
	if (key == KEY_S)
		cub->key_s = 0;
	if (key == KEY_D)
		cub->key_d = 0;
	return (0);
}

void	init_mlx(t_cub *cub)
{
	cub->key_w = 0;
	cub->key_a = 0;
	cub->key_s = 0;
	cub->key_d = 0;
	cub->mlx = mlx_init();
	cub->mlx_w = mlx_new_window(cub->mlx, CUB_W, CUB_H, "Cub3d");
	search_player(cub);
	print_minimap(cub);
	// mlx_key_hook(cub->mlx_w, scuffed_move, cub);
	mlx_hook(cub->mlx_w, 2, 1, scuffed_move_down, cub);
	mlx_hook(cub->mlx_w, 3, 1, scuffed_move_up, cub);
	mlx_loop(cub->mlx);
}

void	search_direction(t_cub **tmp)
{
	t_cub *cub;

	cub = *tmp;
	if (cub->direction == 'N' || cub->direction == 'S')
	{
		cub->dir_x = 0;
		if (cub->direction == 'N')
			cub->dir_y = -1;
		else if (cub->direction == 'S')
			cub->dir_y = 1;
	}
	else if (cub->direction == 'W' || cub->direction == 'E')
	{
		cub->dir_y = 0;
		if (cub->direction == 'W')
			cub->dir_x = -1;
		else if (cub->direction == 'E')
			cub->dir_x = 1;
	}
}

void	search_plane(t_cub **tmp)
{
	// N = plane_x = 0; plane_y = -0.66;
	// S = plane_x = 0; plane_y = 0.66;
	// W = plane_x = -0.66; plane_y = 0;
	// E = plane_x = 0.66; plane_y = 0;
	t_cub *cub;

	cub = *tmp;
	if (cub->direction == 'N' || cub->direction == 'S')
	{
		cub->plane_x = (0.66 * cub->dir_y) * 1;
		cub->plane_y = (0.66 * cub->dir_x) * 1;
	}
	else if (cub->direction == 'W' || cub->direction == 'E')
	{
		cub->plane_x = (0.66 * cub->dir_y) * -1;
		cub->plane_y = (0.66 * cub->dir_x) * -1;
	}
}

void	calc_sideDist(t_ray *ray, t_cub *cub)
{
	ray->map_x = (int)cub->pos_x;
	ray->map_y = (int)cub->pos_y;
	if (ray->rayDir_x < 0)
	{
		ray->steps_x = -1;
		ray->sideDist_x = (cub->pos_x - ray->map_x) * ray->deltaDist_x;
	}
	else
	{
		ray->steps_x = 1;
		ray->sideDist_x = (ray->map_x + 1.0 - cub->pos_x) * ray->deltaDist_x;
	}
	if (ray->rayDir_y < 0)
	{
		ray->steps_y = -1;
		ray->sideDist_y = (cub->pos_y - ray->map_y) * ray->deltaDist_y;
	}
	else
	{
		ray->steps_y = 1;
		ray->sideDist_y = (ray->map_y + 1.0 - cub->pos_y) * ray->deltaDist_y;
	}
	printf("sideDist x = %f\n", ray->sideDist_x);
	printf("sideDist y = %f\n", ray->sideDist_y);
}

void	calc_deltaDist(t_ray *ray)
{
	if (ray->rayDir_x == 0)
		ray->deltaDist_x = 1e30;
	else
		ray->deltaDist_x = fabs(1 / ray->rayDir_x);
	if (ray->rayDir_y == 0)
		ray->deltaDist_y = 1e30;
	else
		ray->deltaDist_y = fabs(1 / ray->rayDir_y);
	printf("deltaDist x = %f\n", ray->deltaDist_x);
	printf("deltaDist y = %f\n", ray->deltaDist_y);
}

void	hit_wall(t_cub *cub, t_ray *ray)
{
	ray->hitWall = 0;
	while (!(ray->hitWall))
	{
		if (ray->sideDist_x < ray->sideDist_y)
		{
			ray->sideDist_x += ray->deltaDist_x;
			ray->map_x += ray->steps_x;
			ray->side = 0;
		}
		else
		{
			ray->sideDist_y += ray->deltaDist_y;
			ray->map_y += ray->steps_y;
			ray->side = 1;
		}
		if (cub->map[ray->map_y][ray->map_x] != '0')
			ray->hitWall = 1;
	}
	if (ray->side == 0)
		ray->perpendicular = ray->sideDist_x - ray->deltaDist_x;
	else
		ray->perpendicular = ray->sideDist_y - ray->deltaDist_y;
}

int	raycasting_loop(t_cub *cub)
{
	t_ray	ray;
	// t_cub	*cub;
	int		i;

	// cub = *tmp;
	ray.i = -1;
	i = -1;
	while (++ray.i < CUB_W)
	{
		ray.camera_x = 2 * ray.i / (double)CUB_W - 1;
		ray.rayDir_x = cub->dir_x + cub->plane_x * ray.camera_x;
		ray.rayDir_y = cub->dir_y + cub->plane_y * ray.camera_x;
		calc_deltaDist(&ray);
		calc_sideDist(&ray, cub);
		hit_wall(cub, &ray);
		ray.line_h = (int)CUB_H / ray.perpendicular;
		ray.start = -ray.line_h / 2 + CUB_H / 2;
		if (ray.start < 0)
			ray.start = 0;
		ray.end = ray.line_h / 2 + CUB_H / 2;
		if (ray.end > CUB_H)
			ray.end = CUB_H;
		while (++i < ray.start)
			mlx_pixel_put(cub->mlx, cub->mlx_w, CUB_W - ray.i - 1, i, 0x000000FF);
		while (++i < CUB_H)
			mlx_pixel_put(cub->mlx, cub->mlx_w, CUB_W - ray.i - 1, i, 0x00FF0000);
	}
	return(0);
}

// int	init_game(int key, t_cub *cub)
// {
// 	(void)key;
// 	raycasting_loop(&cub);
// 	// key_game();
// 	return (0);
// }

void	ray_main(t_cub *cub)
{
	cub->mlx = mlx_init();
	cub->mlx_w = mlx_new_window(cub->mlx, CUB_W, CUB_H, "Cub3d");
	search_player(cub);
	search_direction(&cub);
	search_plane(&cub);
	// print_minimap(cub);
	printf("x = %f\n", cub->pos_x);
	printf("y = %f\n", cub->pos_y);
	printf("dir = %c\n", cub->direction);
	printf("dir x = %d\n", cub->dir_x);
	printf("dir y = %d\n", cub->dir_y);
	printf("plane x = %f\n", cub->plane_x);
	printf("plane y = %f\n", cub->plane_y);
	mlx_loop_hook(cub->mlx, raycasting_loop, cub);
	mlx_loop(cub->mlx);
}

int	main(int ac, char **av)
{
	t_cub	cub;

	if (parse_file(ac, av, &cub))
		return (1);
	print_vars(cub);
	ray_main(&cub);
	// init_mlx(&cub);
}
