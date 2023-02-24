/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_static3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:36:27 by ralves-g          #+#    #+#             */
/*   Updated: 2023/02/24 14:31:38 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	minimap_loop_s(t_cub *cub, t_ray *ray)
{
	print_minimap_s(cub);
	ray->i = -1;
	cub->mp_color = rgb_spectrum();
	while (++ray->i < CUB_W)
	{
		raycasting(cub, ray, 2);
		minimap_raycasting_s(cub, ray);
	}
	print_map_collectible_s(cub);
	print_map_door_s(cub);
	draw_player_s(cub, *mp_unit() + 5);
}

void	minimap_raycasting_s(t_cub *cub, t_ray *ray)
{
	double	m;
	double	b;
	double	size;

	if (ray->side == 1)
		ray->wall_hit_x = ray->wall_x + (double)ray->map_x;
	else
		ray->wall_hit_y = ray->wall_x + (double)ray->map_y;
	if (!ray->ray_dir_x)
		m = 1e30;
	else
		m = ray->ray_dir_y / ray->ray_dir_x;
	b = cub->pos_y - (m * cub->pos_x);
	if (ray->side == 1)
		ray->wall_hit_y = m * ray->wall_hit_x + b;
	else
	{
		if (!m)
			ray->wall_hit_x = 1e30;
		else
			ray->wall_hit_x = (ray->wall_hit_y - b) / m;
	}
	size = sqrt((cub->pos_x - ray->wall_hit_x) * (cub->pos_x - ray->wall_hit_x)
			+ (cub->pos_y - ray->wall_hit_y) * (cub->pos_y - ray->wall_hit_y));
	draw_vector(cub, ray->ray_dir_x, ray->ray_dir_y, size * (*mp_unit()));
}
