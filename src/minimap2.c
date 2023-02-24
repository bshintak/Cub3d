/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:24:51 by bshintak          #+#    #+#             */
/*   Updated: 2023/02/22 16:46:00 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_minimap_wall(t_cub *cub, int m_x, int m_y)
{
	t_coords	c;
	t_wall		w;

	w.angle = atan2(-cub->dir_y, cub->dir_x) - M_PI_2;
	c.y = m_y - 1;
	while (++c.y < m_y + (*mp_unit()))
	{
		c.x = m_x - 1;
		while (++c.x < m_x + (*mp_unit()))
		{
			w.offset = 0;
			w.color = 0xFF00FF00;
			minimap_wall_pixel(cub, c, w, 0);
			w.color = 0xFFFF0000;
			w.offset = -OFFSET;
			minimap_wall_pixel(cub, c, w, 0);
			w.color = 0xFF0000FF;
			w.offset = OFFSET;
			minimap_wall_pixel(cub, c, w, 0);
		}
	}
}

void	print_map_door(t_cub *cub)
{
	int	y;
	int	x;

	y = -1;
	while (cub->map[++y])
	{
		x = -1;
		while (cub->map[y][++x])
		{
			if (cub->map[y][x] == 'D' || cub->map[y][x] == 'd')
				print_map_door2(cub, x * (*mp_unit()), y
					* (*mp_unit()), cub->map[y][x]);
		}
	}
}

void	print_map_door2(t_cub *cub, int m_x, int m_y, char chr)
{
	t_coords	c;
	t_wall		w;

	w.angle = atan2(-cub->dir_y, cub->dir_x) - M_PI_2;
	c.y = m_y - 1;
	while (++c.y < m_y + (*mp_unit()))
	{
		c.x = m_x - 1;
		while (++c.x < m_x + (*mp_unit()))
		{
			w.offset = 0;
			w.color = 0xFFFF0000;
			if (chr == 'D')
				minimap_wall_pixel(cub, c, w, 0);
			else
				minimap_wall_pixel(cub, c, w, 2);
		}
	}
}

void	print_outline(t_cub *cub)
{
	int	y;
	int	x;
	int	test;

	y = cub->mp_y - MAP_RADIUS - MAP_OUTLINE;
	while (y < cub->mp_y + MAP_RADIUS + MAP_OUTLINE)
	{
		x = cub->mp_x - MAP_RADIUS - MAP_OUTLINE;
		while (x < cub->mp_x + MAP_RADIUS + MAP_OUTLINE)
		{
			test = (x - cub->mp_x) * (x - cub->mp_x)
				+ (y - cub->mp_y) * (y - cub->mp_y);
			print_outline2(cub, x, y, test);
			x++;
		}
		y++;
	}
}

void	print_minimap(t_cub *cub)
{
	int	y;
	int	x;

	y = -1;
	if (cub->tab)
	{
		cub->mp_x = CUB_W / 2;
		cub->mp_y = CUB_H / 2;
	}
	else
	{
		cub->mp_x = CUB_W - MAP_RADIUS * 1.2;
		cub->mp_y = MAP_RADIUS * 1.2;
	}
	if (!cub->tab)
		print_outline(cub);
	while (cub->map[++y])
	{
		x = -1;
		while (cub->map[y][++x])
		{
			if (cub->map[y][x] == '1')
				print_minimap_wall(cub, x * (*mp_unit()), y * (*mp_unit()));
		}
	}
}
