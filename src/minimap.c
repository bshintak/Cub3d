/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:44:43 by ralves-g          #+#    #+#             */
/*   Updated: 2023/02/24 16:08:27 by ralves-g         ###   ########.fr       */
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

t_coords	calc_new(t_cub *cub, t_coords c, t_wall w)
{
	t_coords	c2;

	c2 = c;
	c2.n_x = (c.x + w.offset - cub->pos_x * (*mp_unit())) * cos(w.angle)
		- (c.y + w.offset - cub->pos_y * (*mp_unit())) * sin(w.angle);
	c2.n_y = (c.x + w.offset - cub->pos_x * (*mp_unit())) * sin(w.angle)
		+ (c.y + w.offset - cub->pos_y * (*mp_unit())) * cos(w.angle);
	return (c2);
}

void	minimap_wall_pixel(t_cub *cub, t_coords c, t_wall w, int mode)
{
	c = calc_new(cub, c, w);
	if (((cub->tab || (((c.n_x * c.n_x + c.n_y * c.n_y <= MAP_RADIUS \
		* MAP_RADIUS) \
		&& (cub->m == 0 || cub->m == 2)) || ((cub->m == 1 || cub->m == 3) \
			&& c.n_x >= -MAP_RADIUS && c.n_x <= MAP_RADIUS \
		&& c.n_y >= -MAP_RADIUS && c.n_y <= MAP_RADIUS))) \
		&& check_borders(c.n_x + cub->mp_x, c.n_y + cub->mp_y)))
	{
		if (!mode)
			my_mlx_pixel_put_add(&(cub->frame), c.n_x + cub->mp_x,
				c.n_y + cub->mp_y, w.color);
		else if (mode == 1)
			my_mlx_pixel_put(&(cub->frame), c.n_x + cub->mp_x,
				c.n_y + cub->mp_y, 0x00FFFFFF);
		else
		{
			my_mlx_pixel_put_door(&(cub->frame), c.n_x + cub->mp_x,
				c.n_y + cub->mp_y);
		}
	}
}

void	print_outline2(t_cub *cub, int x, int y, int test)
{
	if ((test >= MAP_RADIUS * MAP_RADIUS && (!cub->m || cub->m == 2)) \
		|| ((cub->m == 1 || cub->m == 3) && ((x <= cub->mp_x - MAP_RADIUS \
			|| x >= cub->mp_x + MAP_RADIUS) || (y <= cub->mp_y - MAP_RADIUS \
				|| y >= cub->mp_y + MAP_RADIUS))))
	{
		if (test <= (MAP_RADIUS + MAP_OUTLINE) * (MAP_RADIUS + MAP_OUTLINE) || \
				cub->m == 1 || cub->m == 3)
			my_mlx_pixel_put_drk(&(cub->frame), x, y);
	}
	else
		my_mlx_pixel_put(&(cub->frame), x, y, 0);
}
