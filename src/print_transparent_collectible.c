/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_transparent_collectible.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:17:43 by bshintak          #+#    #+#             */
/*   Updated: 2023/02/24 15:49:37 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_textures_c(t_cub *cub, t_ray ray)
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
			textures_c(cub, &ray, &start);
		if (start * 2 + ray.size * 2 - ray.start >= 0 && start * 2
			+ ray.size * 2 - ray.start <= CUB_H && cub->r)
			reflections_c(cub, &ray, &start);
		ray.start++;
	}
}

void	textures_c(t_cub *cub, t_ray *ray, double *start)
{
	double			tmp_start;
	unsigned int	color;

	tmp_start = *start;
	color = get_image_color(&cub->collec, cub->collec.x_size
			- cub->collec.x_size * ray->wall_x, cub->collec.y_size
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

void	reflections_c(t_cub *cub, t_ray *ray, double *start)
{
	double	tmp_start;

	tmp_start = *start;
	my_mlx_pixel_put(&cub->frame, CUB_W - ray->i - 1,
		tmp_start * 2 + ray->size * 2 - ray->start, cub->color[FLOOR]);
	my_mlx_pixel_put_sub(&cub->frame, CUB_W - ray->i - 1,
		tmp_start * 2 + ray->size * 2 - ray->start,
		get_image_color(&cub->collec, cub->collec.x_size
			- cub->collec.x_size * ray->wall_x,
			cub->collec.y_size
			* ((ray->start - tmp_start + 1) / ray->size)));
	my_mlx_pixel_put_drk(&cub->frame, CUB_W
		- ray->i - 1, tmp_start * 2 + ray->size * 2 - ray->start);
	my_mlx_pixel_put_drk(&cub->frame, CUB_W - ray->i
		- 1, tmp_start * 2 + ray->size * 2 - ray->start);
	my_mlx_pixel_put_drk(&cub->frame, CUB_W - ray->i
		- 1, tmp_start * 2 + ray->size * 2 - ray->start);
	*start = tmp_start;
}
