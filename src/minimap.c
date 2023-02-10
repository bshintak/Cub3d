/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:44:43 by ralves-g          #+#    #+#             */
/*   Updated: 2023/02/06 18:21:30 by ralves-g         ###   ########.fr       */
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
	double	x;
	double	y;
	double	w;

	w = 0;
	y = - height / 2;
	while (y < height / 2)
	{
		x = - w;
		while (x <= + w)
		{
			//TODO ROTATE PLAYER
			// x = 
			// y = 
			my_mlx_pixel_put_inv(&cub->frame, x + cub->mp_x , y + cub->mp_y);
			x+=1.0;
		}
		y+=1.0;
		w+=0.3;
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
	
	if ((cub->tab || (new_x * new_x + new_y * new_y
		<= MAP_RADIUS * MAP_RADIUS)) && check_borders(new_x + cub->mp_x,
		new_y + cub->mp_y))
	{
		my_mlx_pixel_put(&(cub->frame), 
		new_x + cub->mp_x, 
		new_y + cub->mp_y, 
			0);
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

	if ((cub->tab || (new_x * new_x + new_y * new_y
		<= MAP_RADIUS * MAP_RADIUS)) && check_borders(new_x + cub->mp_x,
		new_y + cub->mp_y))
	{
		if (!mode)
			my_mlx_pixel_put_add(&(cub->frame), new_x + cub->mp_x, 
			new_y + cub->mp_y, w.color);
		else
			my_mlx_pixel_put(&(cub->frame), new_x + cub->mp_x, 
		new_y + cub->mp_y, 0x00FFFFFF);
	}
}

void	print_minimap_wall(t_cub *cub, int m_x, int m_y)
{
	t_coords c;
	t_wall w;

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
			if (test >= MAP_RADIUS * MAP_RADIUS)
			{
				// if (test<= (MAP_RADIUS + MAP_OUTLINE * 2) * (MAP_RADIUS + MAP_OUTLINE * 2))
				// 	my_mlx_pixel_put(&(cub->frame), x, y, MAP_OUTL_CLR * 10);
				if (test <= (MAP_RADIUS + MAP_OUTLINE) * (MAP_RADIUS + MAP_OUTLINE))
					my_mlx_pixel_put_drk(&(cub->frame), x, y);
					// my_mlx_pixel_put(&(cub->frame), x, y, MAP_OUTL_CLR);
			}
			else
				my_mlx_pixel_put(&(cub->frame), x, y, 0);
			x++;
		}
		y++;
	}
}

void	print_minimap(t_cub *cub)
{
	int	y;
	int	x;
	// int	old_unit;

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
			if (cub->map[y][x] == '1')
				print_minimap_wall(cub, x * (*mp_unit()), y * (*mp_unit()));
	}
	draw_player(cub, *mp_unit() + 5);
}
