/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 21:13:03 by bshintak          #+#    #+#             */
/*   Updated: 2023/02/11 21:13:27 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	move_mouse(t_cub *cub)
{
	int x;
	int y;

	mlx_mouse_get_pos(cub->mlx, cub->mlx_w, &x, &y);
	mlx_mouse_move(cub->mlx, cub->mlx_w, CUB_W / 2, CUB_H / 2);
	if ((x != CUB_W / 2 || y != CUB_H / 2) && x >= 0 && x <= CUB_W 
		&& y >= 0 && y <= CUB_H)
	{
		if (x > CUB_W / 2)
			cub->mouse = ((double)x - CUB_W / 2) * MOUSE_SENSITIVITY_X;
		else if (x < CUB_W / 2)
			cub->mouse = ((double)x - CUB_W / 2) * MOUSE_SENSITIVITY_X;
		if (y > CUB_H / 2)
			cub->h -= ((double)y - CUB_H / 2) * MOUSE_SENSITIVITY_Y;
		else if (y < CUB_H / 2)
			cub->h -= ((double)y - CUB_H / 2) * MOUSE_SENSITIVITY_Y;
	}
}
