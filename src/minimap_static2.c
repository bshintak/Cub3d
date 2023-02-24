/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_static2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:24:21 by ralves-g          #+#    #+#             */
/*   Updated: 2023/02/16 15:03:40 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_player_s2(t_cub *cub, t_coords c, double a)
{
	double		x;
	double		y;

	x = (c.x * cos(a + cub->mp_a)) - (c.y * sin(a + cub->mp_a));
	y = (c.x * sin(a + cub->mp_a)) + (c.y * cos(a + cub->mp_a));
	my_mlx_pixel_put_add(&cub->frame, x + cub->mp_x - OFFSET, y
		+ cub->mp_y - OFFSET, (0xFFFF0000 & 0x00555555) >> 1);
	my_mlx_pixel_put_add(&cub->frame, x + cub->mp_x, y + cub->mp_y,
		(0xFF00FF00 & 0x00555555) >> 1);
	my_mlx_pixel_put_add(&cub->frame, x + cub->mp_x + OFFSET, y
		+ cub->mp_y + OFFSET, (0xFF0000FF & 0x00555555) >> 1);
	c.x += 1.0;
}

void	draw_player_s(t_cub *cub, int height)
{
	t_coords	c;
	double		w;
	double		a;

	w = 0;
	c.y = -height / 2;
	a = -atan2(-cub->dir_y, cub->dir_x) + M_PI_2;
	while (c.y < height / 2)
	{
		c.x = -w;
		while (c.x <= +w)
		{
			draw_player_s2(cub, c, a);
			c.x += 1.0;
		}
		c.y += 1.0;
		w += 0.3;
	}
}
