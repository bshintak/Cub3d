/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 20:12:39 by bshintak          #+#    #+#             */
/*   Updated: 2023/02/25 15:59:01 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	hit_m_wall(t_cub *cub, t_ray *ray)
{
	ray->hit_wall = 0;
	while (!(ray->hit_wall))
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->steps_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->steps_y;
			ray->side = 1;
		}
		if (cub->map[ray->map_y][ray->map_x] == '1' ||
			cub->map[ray->map_y][ray->map_x] == 'D')
			ray->hit_wall = 1;
	}
	if (ray->side == 0)
		ray->perpendicular = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perpendicular = ray->side_dist_y - ray->delta_dist_y;
}

void	hit_t_wall(t_cub *cub, t_ray *ray)
{
	ray->t_walls_parse = 0;
	while (ray->t_walls_parse != ray->t_walls)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->steps_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->steps_y;
			ray->side = 1;
		}
		if (cub->map[ray->map_y][ray->map_x] == 'D' \
			|| cub->map[ray->map_y][ray->map_x] == 'B')
			ray->t_walls_parse++;
	}
	if (ray->side == 0)
		ray->perpendicular = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perpendicular = ray->side_dist_y - ray->delta_dist_y;
}

void	hit_wall2(t_cub *cub, t_ray *ray)
{
	if (cub->map[ray->map_y][ray->map_x] == '1')
		ray->hit_wall = 1;
	if (cub->map[ray->map_y][ray->map_x] == 'D'
		|| cub->map[ray->map_y][ray->map_x] == 'B')
		ray->t_walls++;
}

void	hit_wall(t_cub *cub, t_ray *ray)
{
	(void)cub;
	ray->hit_wall = 0;
	ray->t_walls = 0;
	while (!(ray->hit_wall))
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->steps_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->steps_y;
			ray->side = 1;
		}
		hit_wall2(cub, ray);
	}
	if (ray->side == 0)
		ray->perpendicular = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perpendicular = ray->side_dist_y - ray->delta_dist_y;
}
