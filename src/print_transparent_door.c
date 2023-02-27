/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_transparent_door.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 22:32:34 by hanhuka           #+#    #+#             */
/*   Updated: 2023/02/25 15:56:07 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	transparency_loop(t_cub *cub, t_ray *ray)
{
	while (ray->t_walls)
	{
		raycasting(cub, ray, 1);
		if (cub->map[ray->map_y][ray->map_x] == 'D')
			print_textures_t(cub, *ray);
		else
			print_textures_c(cub, *ray);
		ray->t_walls--;
	}
}

void	print_textures_t(t_cub *cub, t_ray ray)
{
	double			start;

	start = 0;
	ray.size = ray.end - ray.start;
	ceiling_color(cub, &ray, &start);
	floor_color(cub, &ray);
	start = ray.start;
	if (ray.start < 0)
		ray.start = 0;
	if (ray.end > CUB_H)
		ray.end = CUB_H;
	while (ray.start <= ray.end)
	{
		if (ray.start >= 0 && ray.start <= CUB_H)
			textures_t(cub, &ray, &start);
		if (start * 2 + ray.size * 2 - ray.start >= 0 && start * 2
			+ ray.size * 2 - ray.start <= CUB_H && cub->r)
			reflections_t(cub, &ray, &start);
		ray.start++;
	}
}

void	textures_t(t_cub *cub, t_ray *ray, double *start)
{
	double			tmp_start;
	unsigned int	color;

	tmp_start = *start;
	color = get_image_color(&cub->doors, cub->doors.x_size
			- cub->doors.x_size * ray->wall_x, cub->doors.y_size
			* ((ray->start - tmp_start + 1) / ray->size));
	if (color != 0xFF000000)
	{
		my_mlx_pixel_put(&cub->frame, CUB_W - ray->i - 1, ray->start, color);
		if ((((CUB_W - ray->i - 1 - CUB_W / 2) * (CUB_W - ray->i - 1 - CUB_W
						/ 2) + (ray->start - CUB_H / 2) * (ray->start - CUB_H
						/ 2) >= 175 * 175) || (!cub->f || !cub->battery))
			&& cub->l)
		{
			my_mlx_pixel_put_drk(&cub->frame, CUB_W - ray->i - 1, ray->start);
			my_mlx_pixel_put_drk(&cub->frame, CUB_W - ray->i - 1, ray->start);
			my_mlx_pixel_put_drk(&cub->frame, CUB_W - ray->i - 1, ray->start);
			my_mlx_pixel_put_drk(&cub->frame, CUB_W - ray->i - 1, ray->start);
		}
	}
	*start = tmp_start;
}

void	reflections_t(t_cub *cub, t_ray *ray, double *start)
{
	double	tmp_start;

	tmp_start = *start;
	my_mlx_pixel_put(&cub->frame, CUB_W - ray->i - 1,
		tmp_start * 2 + ray->size * 2 - ray->start, cub->color[FLOOR]);
	my_mlx_pixel_put_sub(&cub->frame, CUB_W - ray->i - 1,
		tmp_start * 2 + ray->size * 2 - ray->start,
		get_image_color(&cub->doors, cub->doors.x_size
			- cub->doors.x_size * ray->wall_x,
			cub->doors.y_size
			* ((ray->start - tmp_start + 1) / ray->size)));
	my_mlx_pixel_put_drk(&cub->frame, CUB_W
		- ray->i - 1, tmp_start * 2 + ray->size * 2 - ray->start);
	my_mlx_pixel_put_drk(&cub->frame, CUB_W - ray->i
		- 1, tmp_start * 2 + ray->size * 2 - ray->start);
	my_mlx_pixel_put_drk(&cub->frame, CUB_W - ray->i
		- 1, tmp_start * 2 + ray->size * 2 - ray->start);
	*start = tmp_start;
}
