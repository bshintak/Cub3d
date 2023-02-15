/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 19:15:27 by bshintak          #+#    #+#             */
/*   Updated: 2023/02/13 19:53:12 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	change_pos(t_cub *cub, double new_dir_x, double new_dir_y)
{
	if (cub->map[(int)cub->pos_y][(int)(cub->pos_x
		+ new_dir_x * MOVE * cub->sft)] == '0')
		cub->pos_x += new_dir_x * MOVE * cub->sft;
	if (cub->map[(int)(cub->pos_y + (new_dir_y * MOVE * cub->sft))]
		[(int)cub->pos_x] == '0')
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

void	move(t_cub *cub, int ws, int ad)
{
	double	new_dir_x;
	double	new_dir_y;

	if (ad == 1 || ad == -1)
	{
		new_dir_x = cub->dir_x * cos(M_PI_2 * (-ad))
			- cub->dir_y * sin(M_PI_2 * (-ad));
		new_dir_y = cub->dir_x * sin(M_PI_2 * (-ad))
			+ cub->dir_y * cos(M_PI_2 * (-ad));
		change_pos(cub, new_dir_x, new_dir_y);
	}
	is_ws(cub, &new_dir_x, &new_dir_y, ws);
	if (ws == 1 || ws == -1)
		change_pos(cub, new_dir_x, new_dir_y);
	if (ws || ad)
		cub->mp_a = atan2(ws, ad) - M_PI_2;
	else
		cub->mp_a = 0;
}
