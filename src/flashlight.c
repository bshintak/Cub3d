/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flashlight.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:10:38 by ralves-g          #+#    #+#             */
/*   Updated: 2023/02/24 17:24:17 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	flashlight_euclidean(t_cub *cub, t_ray *ray)
{
	double	m;
	double	b;

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
	return (sqrt((cub->pos_x - ray->wall_hit_x) * (cub->pos_x - ray->wall_hit_x)
			+ (cub->pos_y - ray->wall_hit_y) * (cub->pos_y - ray->wall_hit_y)));
}

unsigned long	time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	count_battery(t_cub *cub)
{
	if (cub->num_collectible)
	{
		cub->battery = 100;
		cub->num_collectible = 0;
	}
	if (cub->f && cub->battery && (time_ms() - cub->t_start) \
		>= BATTERY_RATE)
	{
		cub->battery--;
		cub->t_start = time_ms();
	}
}

void	print_battery(t_cub *cub)
{
	t_coords	c;

	count_battery(cub);
	c.y = MAP_RADIUS * 0.2;
	while (c.y <= 50)
	{
		c.x = 0;
		while (c.x <= 240)
		{
			if (c.x >= 20 && c.x < cub->battery * 2 + 20 && c.y >= 30
				&& c.y <= 40)
			{
				if (cub->battery < 20)
					my_mlx_pixel_put(&(cub->frame), c.x + 20, c.y, 0xFFFF3A00);
				else if (cub->battery < 50)
					my_mlx_pixel_put(&(cub->frame), c.x + 20, c.y, 0xFFEBFF00);
				else
					my_mlx_pixel_put(&(cub->frame), c.x + 20, c.y, 0xFF61FF00);
			}
			else
				my_mlx_pixel_put_drk(&(cub->frame), c.x + 20, c.y);
			c.x++;
		}
		c.y++;
	}
}
