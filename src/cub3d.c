/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:20:45 by ralves-g          #+#    #+#             */
/*   Updated: 2023/01/30 17:28:11 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
				cub->pos_x = x;
				cub->pos_y = y;
				cub->direction = cub->map[y][x];
			}
			x++;
		}
		y++;
	}
}

void	search_direction(t_cub *cub)
{
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

void	search_plane(t_cub *cub)
{
	// N = plane_x = 0; plane_y = -0.66;
	// S = plane_x = 0; plane_y = 0.66;
	// W = plane_x = -0.66; plane_y = 0;
	// E = plane_x = 0.66; plane_y = 0;
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
		if (cub->map[ray->map_y][ray->map_x] == '1')
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
	int		i;

	ray.i = -1;
	while (++ray.i < CUB_W)
	{
		ray.camera_x = 2 * ray.i / (double)CUB_W - 1;
		ray.rayDir_x = cub->dir_x + cub->plane_x * ray.camera_x;
		ray.rayDir_y = cub->dir_y + cub->plane_y * ray.camera_x;
		calc_deltaDist(&ray);
		calc_sideDist(&ray, cub);
		hit_wall(cub, &ray);
		ray.line_h = (int)(CUB_H / ray.perpendicular);
		ray.start = -ray.line_h / 2 + CUB_H / 2;
		if (ray.start < 0)
			ray.start = 0;
		ray.end = ray.line_h / 2 + CUB_H / 2;
		if (ray.end >= CUB_H)
			ray.end = CUB_H -1;
		i = -1;
		while (++i < ray.start)
			mlx_pixel_put(cub->mlx, cub->mlx_w, CUB_W - ray.i - 1, i, (0x000000FF / 6));
		while (++i < ray.end)
		{
			if (ray.side == 0)
				mlx_pixel_put(cub->mlx, cub->mlx_w, CUB_W - ray.i - 1, i, (0x0000FF00 / 2));
			else
				mlx_pixel_put(cub->mlx, cub->mlx_w, CUB_W - ray.i - 1, i, (0x0000FF00 / 6));
		}
		while (++i < CUB_H)
			mlx_pixel_put(cub->mlx, cub->mlx_w, CUB_W - ray.i - 1, i, (0x000000FF / 20));
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_cub	cub;

	if (parse_file(ac, av, &cub))
		return (1);
	print_vars(cub);
	ray_main(&cub);
}
