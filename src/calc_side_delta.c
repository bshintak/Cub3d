/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 21:26:24 by bshintak          #+#    #+#             */
/*   Updated: 2023/02/11 21:27:14 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
