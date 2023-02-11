/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_printing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:08:46 by ralves-g          #+#    #+#             */
/*   Updated: 2023/02/11 21:02:45 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

unsigned int	*get_img_pixel(t_data *data, int x, int y)
{
	char	*pixel;

	pixel = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return ((unsigned int *) pixel);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	my_mlx_pixel_put_add(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	
	// printf("color = %d\n", *(unsigned int *)dst);
	// if (*(unsigned int *)dst)
		*(unsigned int *)dst += color;
	// else
	// 	*(unsigned int *)dst = color;
}

void	my_mlx_pixel_put_inv(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	if (!*(unsigned int *)dst)
		*(unsigned int *)dst = 0x00FFFFFF;
	else
		*(unsigned int *)dst = -(*(unsigned int *)dst);
}

void	my_mlx_pixel_put_drk(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = (*(unsigned int *)dst & 0x00FEFEFE) >> 1;
}

void	init_images(t_cub *cub)
{
	cub->tex[WALL_1].img = mlx_xpm_file_to_image(cub->mlx, "stone.xpm", &cub->tex[WALL_1].img_width, &cub->tex[WALL_1].img_height);
	cub->tex[WALL_1].addr = mlx_get_data_addr(cub->tex[WALL_1].img, &cub->tex[WALL_1].bits_per_pixel, &cub->tex[WALL_1].line_length, &cub->tex[WALL_1].endian);
	cub->tex[WALL_2].img = mlx_xpm_file_to_image(cub->mlx, "stone.xpm", &cub->tex[WALL_2].img_width, &cub->tex[WALL_2].img_height);
	cub->tex[WALL_2].addr = mlx_get_data_addr(cub->tex[WALL_2].img, &cub->tex[WALL_2].bits_per_pixel, &cub->tex[WALL_2].line_length, &cub->tex[WALL_2].endian);
	cub->tex[WALL_3].img = mlx_xpm_file_to_image(cub->mlx, "stone.xpm", &cub->tex[WALL_3].img_width, &cub->tex[WALL_3].img_height);
	cub->tex[WALL_3].addr = mlx_get_data_addr(cub->tex[WALL_3].img, &cub->tex[WALL_3].bits_per_pixel, &cub->tex[WALL_3].line_length, &cub->tex[WALL_3].endian);
	cub->tex[WALL_4].img = mlx_xpm_file_to_image(cub->mlx, "stone.xpm", &cub->tex[WALL_4].img_width, &cub->tex[WALL_4].img_height);
	cub->tex[WALL_4].addr = mlx_get_data_addr(cub->tex[WALL_4].img, &cub->tex[WALL_4].bits_per_pixel, &cub->tex[WALL_4].line_length, &cub->tex[WALL_4].endian);
}

void	create_image(t_cub *cub, t_data *data, int size_x, int size_y)
{
	data->img = mlx_new_image(cub->mlx, size_x, size_y);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
}

void	draw_ray(t_cub *cub, t_ray *ray)
{
	int y;

	y = 0;
	while (y < ray->start)
	{
		my_mlx_pixel_put(&cub->frame, CUB_W - ray->i - 1, y, 0x000000FF / 6);
		y++;
	}
	y = ray->start;
	while (++y < ray->end)
	{
		ray->tex_y = (int)ray->tex_pos & (cub->tex[ray->side].img_height - 1);
		ray->tex_pos += ray->step;
		ray->color = *(get_img_pixel(&(cub->tex[ray->side]), ray->tex_x, ray->tex_y));
		if (ray->side == WE || ray->side == EA)
			ray->color = mlx_get_color_value(cub->mlx, (int)((ray->color & 0x0000FF) * 0.70)
				| (int)(((ray->color >> 8) & 0x0000FF) * 0.70) << 8
				| (int)((ray->color >> 16) * 0.70) << 16);
		my_mlx_pixel_put(&cub->frame, CUB_W - ray->i - 1, y, ray->color);
	}
}
