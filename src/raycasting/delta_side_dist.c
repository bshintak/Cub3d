/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delta_side_dist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:51:10 by bshintak          #+#    #+#             */
/*   Updated: 2023/01/31 16:03:55 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	calc_delta_dist(t_ray *ray)
{
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

void	calc_side_dist(t_ray *ray, t_cub *cub)
{
	ray->map_x = (int)cub->pos_x;
	ray->map_y = (int)cub->pos_y;
	if (ray->ray_dir_x < 0)
	{
		ray->steps_x = -1;
		ray->side_dist_x = (cub->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->steps_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - cub->pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->steps_y = -1;
		ray->side_dist_y = (cub->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->steps_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - cub->pos_y) * ray->delta_dist_y;
	}
}
