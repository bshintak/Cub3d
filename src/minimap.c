/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:44:43 by ralves-g          #+#    #+#             */
/*   Updated: 2023/02/15 14:25:42 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_borders(int x, int y)
{
	(void)x;
	(void)y;
	if (x > 0 && x < CUB_W - 1 && y > 0 && y < CUB_H - 1)
		return (1);
	return (0);
}

void	draw_player(t_cub *cub, int height)
{
	t_coords	c;
	double		w;
	double		x;
	double		y;

	w = 0;
	c.y = -height / 2;
	while (c.y < height / 2)
	{
		c.x = -w;
		while (c.x <= +w)
		{
			x = (c.x * cos(cub->mp_a)) - (c.y * sin(cub->mp_a));
			y = (c.x * sin(cub->mp_a)) + (c.y * cos(cub->mp_a));
			my_mlx_pixel_put_add(&cub->frame, x + cub->mp_x - OFFSET, y
				+ cub->mp_y - OFFSET, (0xFFFF0000 & 0x00555555) >> 1);
			my_mlx_pixel_put_add(&cub->frame, x + cub->mp_x, y + cub->mp_y,
				(0xFF00FF00 & 0x00555555) >> 1);
			my_mlx_pixel_put_add(&cub->frame, x + cub->mp_x + OFFSET, y
				+ cub->mp_y + OFFSET, (0xFF0000FF & 0x00555555) >> 1);
			c.x += 1.0;
		}
		c.y += 1.0;
		w += 0.3;
	}
}

void	print_minimap_wall_fill(t_cub *cub, t_coords c, t_wall w, int offset)
{
	double	new_x;
	double	new_y;

	new_x = (c.x + offset - cub->pos_x * (*mp_unit())) * cos(w.angle)
		- (c.y + offset - cub->pos_y * (*mp_unit())) * sin(w.angle);
	new_y = (c.x + offset - cub->pos_x * (*mp_unit())) * sin(w.angle)
		+ (c.y + offset - cub->pos_y * (*mp_unit())) * cos(w.angle);
	if ((cub->tab || (new_x * new_x + new_y * new_y <= MAP_RADIUS * MAP_RADIUS))
		&& check_borders(new_x + cub->mp_x, new_y + cub->mp_y))
	{
		my_mlx_pixel_put(&(cub->frame),
			new_x + cub->mp_x, new_y + cub->mp_y, 0);
	}
}

void	minimap_wall_pixel(t_cub *cub, t_coords c, t_wall w, int mode)
{
	double	new_x;
	double	new_y;

	new_x = (c.x + w.offset - cub->pos_x * (*mp_unit())) * cos(w.angle)
		- (c.y + w.offset - cub->pos_y * (*mp_unit())) * sin(w.angle);
	new_y = (c.x + w.offset - cub->pos_x * (*mp_unit())) * sin(w.angle)
		+ (c.y + w.offset - cub->pos_y * (*mp_unit())) * cos(w.angle);
	if ((cub->tab || (new_x * new_x + new_y * new_y <= MAP_RADIUS * MAP_RADIUS))
		&& check_borders(new_x + cub->mp_x, new_y + cub->mp_y))
	{
		if (!mode)
			my_mlx_pixel_put_add(&(cub->frame), new_x + cub->mp_x,
				new_y + cub->mp_y, w.color);
		else
			my_mlx_pixel_put(&(cub->frame), new_x + cub->mp_x,
				new_y + cub->mp_y, 0x00FFFFFF);
	}
}
