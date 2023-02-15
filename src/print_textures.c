/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:53:12 by bshintak          #+#    #+#             */
/*   Updated: 2023/02/15 17:40:49 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	first(t_cub *cub, t_ray *ray, double *start, int *side)
{
	double	tmp_start;
	int		tmp_side;

	tmp_start = *start;
	tmp_side = *side;
	my_mlx_pixel_put(&cub->frame, CUB_W - ray->i - 1, ray->start,
		get_image_color(&cub->wall_t[tmp_side], cub->wall_t[tmp_side].x_size
			- cub->wall_t[tmp_side].x_size * ray->wall_x,
			cub->wall_t[tmp_side].y_size
			* ((ray->start - tmp_start + 1) / ray->size)));
	*start = tmp_start;
	*side = tmp_side;
}

void	second(t_cub *cub, t_ray *ray, double *start, int *side)
{
	double	tmp_start;
	int		tmp_side;

	tmp_start = *start;
	tmp_side = *side;
	my_mlx_pixel_put(&cub->frame, CUB_W - ray->i - 1,
		tmp_start * 2 + ray->size * 2 - ray->start, cub->color[FLOOR]);
	my_mlx_pixel_put_sub(&cub->frame, CUB_W - ray->i - 1,
		tmp_start * 2 + ray->size * 2 - ray->start,
		get_image_color(&cub->wall_t[tmp_side], cub->wall_t[tmp_side].x_size
			- cub->wall_t[tmp_side].x_size * ray->wall_x,
			cub->wall_t[tmp_side].y_size
			* ((ray->start - tmp_start + 1) / ray->size)));
	my_mlx_pixel_put_drk(&cub->frame, CUB_W
		- ray->i - 1, tmp_start * 2 + ray->size * 2 - ray->start);
	my_mlx_pixel_put_drk(&cub->frame, CUB_W - ray->i
		- 1, tmp_start * 2 + ray->size * 2 - ray->start);
	my_mlx_pixel_put_drk(&cub->frame, CUB_W - ray->i
		- 1, tmp_start * 2 + ray->size * 2 - ray->start);
	*start = tmp_start;
	*side = tmp_side;
}

void	print_textures(t_cub *cub, t_ray ray)
{
	double	start;
	int		side;

	start = 0;
	ray.size = ray.end - ray.start;
	side = get_side(ray);
	while (start < ray.start)
	{
		if (start >= 0 && start <= CUB_H)
			my_mlx_pixel_put(&cub->frame, CUB_W - ray.i - 1,
				start, cub->color[CEILING]);
		start++;
	}
	start = ray.start;
	while (ray.start <= ray.end)
	{
		if (ray.start >= 0 && ray.start <= CUB_H)
			first(cub, &ray, &start, &side);
		if (start * 2 + ray.size * 2 - ray.start >= 0 && start * 2
			+ ray.size * 2 - ray.start <= CUB_H)
			second(cub, &ray, &start, &side);
		ray.start++;
	}
	ray.start = start + ray.size * 2;
	while (ray.start <= CUB_H)
	{
		my_mlx_pixel_put(&cub->frame, CUB_W - ray.i - 1,
			ray.start, cub->color[FLOOR]);
		ray.start++;
	}
}
