/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 20:12:39 by bshintak          #+#    #+#             */
/*   Updated: 2023/02/13 20:13:03 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	hit_wall(t_cub *cub, t_ray *ray)
{
	ray->hitWall = 0;
	while (!(ray->hitWall))
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
		if (cub->map[ray->map_y][ray->map_x] == '1')
			ray->hitWall = 1;
	}
	if (ray->side == 0)
		ray->perpendicular = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perpendicular = ray->side_dist_y - ray->delta_dist_y;
}
