/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:00:23 by bshintak          #+#    #+#             */
/*   Updated: 2023/02/13 19:46:20 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	key_up(int key, t_cub *cub)
{
	if (key == KEY_W)
		cub->w = 0;
	else if (key == KEY_S)
		cub->s = 0;
	else if (key == KEY_A)
		cub->a = 0;
	else if (key == KEY_D)
		cub->d = 0;
	else if (key == KEY_R)
		cub->r = 0;
	else if (key == KEY_L)
		cub->l = 0;
	else if (key == KEY_UP)
		cub->up = 0;
	else if (key == KEY_DW)
		cub->dw = 0;
	else if (key == KEY_SFT)
		cub->sft = 1;
	return (0);
}

void	verif_key(int key, t_cub *cub)
{
	if (key == KEY_W)
		cub->w = 1;
	else if (key == KEY_S)
		cub->s = 1;
	else if (key == KEY_A)
		cub->a = 1;
	else if (key == KEY_D)
		cub->d = 1;
	else if (key == KEY_R)
		cub->r = 1;
	else if (key == KEY_L)
		cub->l = 1;
	else if (key == KEY_UP)
		cub->up = 1;
	else if (key == KEY_DW)
		cub->dw = 1;
}

void	show_hide_mouse(int key, t_cub *cub)
{
	if (key == KEY_ALT)
	{
		if (cub->alt == 1)
		{
			cub->alt = 0;
			mlx_mouse_hide(cub->mlx, cub->mlx_w);
		}
		else
		{
			cub->alt = 1;
			mlx_mouse_show(cub->mlx, cub->mlx_w);
		}
	}
}

int	raycasting_key(int key, t_cub *cub)
{
	verif_key(key, cub);
	if (key == KEY_TAB)
	{
		if (cub->tab)
			cub->tab = 0;
		else
			cub->tab = 1;
	}
	else if (key == KEY_SFT)
		cub->sft = 3;
	show_hide_mouse(key, cub);
	if (key == KEY_ESC)
		close_win();
	return (0);
}
