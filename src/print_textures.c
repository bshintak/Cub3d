/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:53:12 by bshintak          #+#    #+#             */
/*   Updated: 2023/02/16 18:38:26 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ceiling_color(t_cub *cub, t_ray *ray, double *start)
{
	while (*start < ray->start)
	{
		if (*start >= 0 && *start <= CUB_H)
			my_mlx_pixel_put(&cub->frame, CUB_W - ray->i - 1,
				*start, cub->color[CEILING]);
		*start += 1;
	}
}

void	floor_color(t_cub *cub, t_ray *ray)
{
	int	s_start;

	s_start = ray->end;
	while (s_start <= CUB_H)
	{
		my_mlx_pixel_put(&cub->frame, CUB_W - ray->i - 1,
			s_start, cub->color[FLOOR]);
		s_start++;
	}
}

void	textures(t_cub *cub, t_ray *ray, double *start, int *side)
{
	double			tmp_start;
	int				tmp_side;

	tmp_start = *start;
	tmp_side = *side;
	my_mlx_pixel_put(&cub->frame, CUB_W - ray->i - 1, ray->start,
		get_image_color(&cub->wall_t[tmp_side], cub->wall_t[tmp_side].x_size
			- cub->wall_t[tmp_side].x_size * ray->wall_x,
			cub->wall_t[tmp_side].y_size
			* ((ray->start - tmp_start + 1) / ray->size)));
	if ((((CUB_W - ray->i - 1 - CUB_W / 2) * (CUB_W - ray->i - 1
					- CUB_W / 2) + (ray->start - CUB_H / 2) * (ray->start
					- CUB_H / 2) >= 175 * 175) || (!cub->f || !cub->battery))
		&& cub->l)
	{
		my_mlx_pixel_put_drk(&cub->frame, CUB_W - ray->i - 1, ray->start);
		my_mlx_pixel_put_drk(&cub->frame, CUB_W - ray->i - 1, ray->start);
		my_mlx_pixel_put_drk(&cub->frame, CUB_W - ray->i - 1, ray->start);
		my_mlx_pixel_put_drk(&cub->frame, CUB_W - ray->i - 1, ray->start);
	}
	*start = tmp_start;
	*side = tmp_side;
}

void	reflections(t_cub *cub, t_ray *ray, double *start, int *side)
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
	double			start;
	int				side;

	start = 0;
	ray.size = ray.end - ray.start;
	side = get_side(ray);
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
			textures(cub, &ray, &start, &side);
		if (start * 2 + ray.size * 2 - ray.start >= 0 && start * 2
			+ ray.size * 2 - ray.start <= CUB_H && cub->r)
			reflections(cub, &ray, &start, &side);
		ray.start++;
	}
}
