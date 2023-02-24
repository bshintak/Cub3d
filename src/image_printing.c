/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_printing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:08:46 by ralves-g          #+#    #+#             */
/*   Updated: 2023/02/22 17:00:22 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	create_image(t_cub *cub, t_data *data, int size_x, int size_y)
{
	data->img = mlx_new_image(cub->mlx, size_x, size_y);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
}

void	draw_ray(t_cub *cub, t_ray ray, int color)
{
	int	y;

	y = 0;
	while (y < ray.start)
	{
		my_mlx_pixel_put(&cub->frame, CUB_W - ray.i - 1, y,
			cub->color[CEILING]);
		y++;
	}
	while (ray.start <= CUB_H)
	{
		if (ray.start <= ray.end)
			my_mlx_pixel_put(&cub->frame, CUB_W - ray.i - 1, ray.start, color);
		else
			my_mlx_pixel_put(&cub->frame, CUB_W - ray.i - 1,
				ray.start, cub->color[FLOOR]);
		ray.start++;
	}
}

void	draw_vector(t_cub *cub, double dir_x, double dir_y, double max_size)
{
	double	start_x;
	double	start_y;
	double	x;
	double	y;

	start_x = (double)cub->mp_x;
	start_y = (double)cub->mp_y;
	x = start_x;
	y = start_y;
	while (x >= 0 && x < CUB_W && y >= 0 && y < CUB_H
		&& (start_x - x) * (start_x - x) + (start_y - y) * (start_y - y)
		<= max_size * max_size)
	{
		if ((cub->tab || (start_x - x) * (start_x - x) + (start_y - y)
				* (start_y - y) <= MAP_RADIUS * MAP_RADIUS))
			my_mlx_pixel_put(&cub->frame, x, y, cub->mp_color);
		x += dir_x / 10.0;
		y += dir_y / 10.0;
	}
}
