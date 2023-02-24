/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 19:15:27 by bshintak          #+#    #+#             */
/*   Updated: 2023/02/24 16:05:11 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	change_pos(t_cub *cub, double new_dir_x, double new_dir_y)
{
	if (cub->map[(int)cub->pos_y][(int)(cub->pos_x
		+ new_dir_x * MOVE * cub->sft)] == '0'
		|| cub->map[(int)cub->pos_y][(int)(cub->pos_x
		+ new_dir_x * MOVE * cub->sft)] == 'd'
		|| cub->map[(int)cub->pos_y][(int)(cub->pos_x
		+ new_dir_x * MOVE * cub->sft)] == 'b' )
		cub->pos_x += new_dir_x * MOVE * cub->sft;
	if (cub->map[(int)(cub->pos_y + (new_dir_y * MOVE * cub->sft))]
		[(int)cub->pos_x] == '0' || cub->map[(int)(cub->pos_y
			+ (new_dir_y * MOVE * cub->sft))][(int)cub->pos_x] == 'd'
			|| cub->map[(int)(cub->pos_y
			+ (new_dir_y * MOVE * cub->sft))][(int)cub->pos_x] == 'b')
		cub->pos_y += new_dir_y * MOVE * cub->sft;
}

void	is_ws(t_cub *cub, double *x, double *y, int ws)
{
	double	new_dir_x;
	double	new_dir_y;

	new_dir_x = *x;
	new_dir_y = *y;
	if (ws == 1)
	{
		new_dir_x = cub->dir_x * cos(0) - cub->dir_y * sin(0);
		new_dir_y = cub->dir_x * sin(0) + cub->dir_y * cos(0);
	}
	else if (ws == -1)
	{
		new_dir_x = cub->dir_x * cos(M_PI) - cub->dir_y * sin(M_PI);
		new_dir_y = cub->dir_x * sin(M_PI) + cub->dir_y * cos(M_PI);
	}
	*x = new_dir_x;
	*y = new_dir_y;
}

double	get_angle(int ws, int ad)
{
	double	angle;

	if (ws == 1 && !ad)
		angle = 0;
	else if (ws == -1 && !ad)
		angle = M_PI;
	else if (ad == 1 && !ws)
		angle = -M_PI_2;
	else if (ad == -1 && !ws)
		angle = M_PI_2;
	else if (ws == -1 && ad == 1)
		angle = M_PI_4 + M_PI;
	else if (ws == -1 && ad == -1)
		angle = -M_PI_4 + M_PI;
	else if (ws == 1 && ad == -1)
		angle = M_PI_4;
	else
		angle = -M_PI_4;
	return (angle);
}

void	move(t_cub *cub, int ws, int ad)
{
	double	new_dir_x;
	double	new_dir_y;
	double	angle;

	if (ws || ad)
	{
		angle = get_angle(ws, ad);
		new_dir_x = cub->dir_x * cos(angle) - cub->dir_y * sin(angle);
		new_dir_y = cub->dir_x * sin(angle) + cub->dir_y * cos(angle);
		change_pos(cub, new_dir_x, new_dir_y);
	}
	if (ws || ad)
		cub->mp_a = atan2(ws, ad) - M_PI_2;
	else
		cub->mp_a = 0;
}
