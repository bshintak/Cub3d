/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 10:46:57 by bshintak          #+#    #+#             */
/*   Updated: 2023/02/24 17:05:08 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	init_collectible(t_cub *cub)
{
	if (!check_collectible(cub))
		return (0);
	if (init_collectible2(cub))
		return (1);
	cub->collec = cub->collec_l[0];
	return (0);
}

void	print_map_collectible2(t_cub *cub, int m_x, int m_y, char chr)
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
			if (chr == 'B')
				minimap_wall_pixel(cub, c, w, 0);
			else
				minimap_wall_pixel(cub, c, w, 2);
		}
	}
}

void	print_map_collectible(t_cub *cub)
{
	int	y;
	int	x;

	y = -1;
	while (cub->map[++y])
	{
		x = -1;
		while (cub->map[y][++x])
		{
			if (cub->map[y][x] == 'B')
				print_map_collectible2(cub, x * (*mp_unit()), y
					* (*mp_unit()), cub->map[y][x]);
		}
	}
}

void	print_map_collectible_s(t_cub *cub)
{
	int	y;
	int	x;

	y = -1;
	while (cub->map[++y])
	{
		x = -1;
		while (cub->map[y][++x])
		{
			if (cub->map[y][x] == 'B')
				print_map_collectible2_s(cub, x * (*mp_unit()), y
					* (*mp_unit()), cub->map[y][x]);
		}
	}
}

void	print_map_collectible2_s(t_cub *cub, int m_x, int m_y, char chr)
{
	t_coords	c;
	t_wall		w;

	c.y = m_y - 1;
	while (++c.y < m_y + (*mp_unit()))
	{
		c.x = m_x - 1;
		while (++c.x < m_x + (*mp_unit()))
		{
			w.offset = 0;
			w.color = 0xFF00FF00;
			if (chr == 'B')
				minimap_wall_pixel_s(cub, c, w, 0);
			else
				minimap_wall_pixel_s(cub, c, w, 2);
		}
	}
}
