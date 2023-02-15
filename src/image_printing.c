/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_printing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:08:46 by ralves-g          #+#    #+#             */
/*   Updated: 2023/02/15 15:30:56 by bshintak         ###   ########.fr       */
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

int	rgb_spectrum(void)
{
	static int	angle = 0;
	static int	swtch = 0;
	int			red;
	int			green;
	int			blue;

	if (angle == 0)
		swtch = 0;
	else if (angle == 360)
		swtch = 1;
	const int HSVlights[61] =
	{
		0, 4, 8, 13, 17, 21, 25, 30, 34, 38, 42, 47, 51,
		55, 59, 64, 68, 72, 76, 81, 85, 89, 93, 98, 102,
		106, 110, 115, 119, 123, 127, 132, 136, 140, 144,
		149, 153, 157, 161, 166, 170, 174, 178, 183, 187,
		191, 195, 200, 204, 208, 212, 217, 221, 225, 229,
		234, 238, 242, 246, 251, 255
	};
	if (angle < 60)
	{
		red = 255;
		green = HSVlights[angle];
		blue = 0;
	}
	else if (angle < 120)
	{
		red = HSVlights[120 - angle];
		green = 255;
		blue = 0;
	}
	else if (angle < 180)
	{
		red = 0;
		green = 255;
		blue = HSVlights[angle - 120];
	}
	else if (angle < 240)
	{
		red = 0;
		green = HSVlights[240 - angle];
		blue = 255;
	}
	else if (angle < 300)
	{
		red = HSVlights[angle - 240];
		green = 0;
		blue = 255;
	}
	else
	{
		red = 255;
		green = 0;
		blue = HSVlights[360 - angle];
	}
	if (!swtch)
		angle += 2;
	else
		angle -= 2;
	return ((red << 16) + (green << 8) + blue);
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
