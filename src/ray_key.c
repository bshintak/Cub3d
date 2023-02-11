/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:00:23 by bshintak          #+#    #+#             */
/*   Updated: 2023/02/11 21:07:34 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move(t_cub *cub, int ws, int ad)
{
	double	new_dir_x;
	double	new_dir_y;
	if (ad == 1 || ad == -1)
	{
		new_dir_x = cub->dir_x * cos(M_PI_2 * (-ad)) - cub->dir_y * sin(M_PI_2 * (-ad));
		new_dir_y = cub->dir_x * sin(M_PI_2 * (-ad)) + cub->dir_y * cos(M_PI_2 * (-ad));
		if (cub->map[(int)cub->pos_y][(int)(cub->pos_x + new_dir_x * MOVE * cub->sft)] == '0')
			cub->pos_x += new_dir_x * MOVE * cub->sft;
		if (cub->map[(int)(cub->pos_y + (new_dir_y * MOVE * cub->sft))] [(int)cub->pos_x] == '0')
			cub->pos_y += new_dir_y * MOVE * cub->sft;
	}
	if (ws == 1 || ws == -1)
	{
		if (ws == 1)
		{
			new_dir_x = cub->dir_x * cos(0) - cub->dir_y * sin(0);
			new_dir_y = cub->dir_x * sin(0) + cub->dir_y * cos(0);
		}
		else
		{
			new_dir_x = cub->dir_x * cos(M_PI) - cub->dir_y * sin(M_PI);
			new_dir_y = cub->dir_x * sin(M_PI) + cub->dir_y * cos(M_PI);
		}
		if (cub->map[(int)cub->pos_y][(int)(cub->pos_x + new_dir_x * MOVE * cub->sft)] == '0')
			cub->pos_x += new_dir_x * MOVE * cub->sft;
		if (cub->map[(int)(cub->pos_y + (new_dir_y * MOVE * cub->sft))] [(int)cub->pos_x] == '0')
			cub->pos_y += new_dir_y * MOVE * cub->sft;
	}
}

void	rotate(t_cub *cub, int rl, int ud)
{
	double oldDirX;
	double oldPlaneX;
	
	oldDirX = cub->dir_x;
	cub->dir_x = cub->dir_x * cos(ROT * rl) - cub->dir_y * sin(ROT * rl);
	cub->dir_y = oldDirX * sin(ROT * rl) + cub->dir_y * cos(ROT * rl);
	oldPlaneX = cub->plane_x;
	cub->plane_x = cub->plane_x * cos(ROT * rl) - cub->plane_y * sin(ROT * rl);
	cub->plane_y = oldPlaneX * sin(ROT * rl) + cub->plane_y * cos(ROT * rl);

	oldDirX = cub->dir_x;
	cub->dir_x = cub->dir_x * cos(ROT * cub->mouse) - cub->dir_y * sin(ROT * cub->mouse);
	cub->dir_y = oldDirX * sin(ROT * cub->mouse) + cub->dir_y * cos(ROT * cub->mouse);
	oldPlaneX = cub->plane_x;
	cub->plane_x = cub->plane_x * cos(ROT * cub->mouse) - cub->plane_y * sin(ROT * cub->mouse);
	cub->plane_y = oldPlaneX * sin(ROT * cub->mouse) + cub->plane_y * cos(ROT * cub->mouse);

	cub->mouse = 0;
	cub->h += ud * 10;
	if (cub->h > CUB_H)
		cub->h = CUB_H - 1;
	if (cub->h < -CUB_H)
		cub->h = -(CUB_H - 1);
}

int mouse_hook(int code)
{	if (code == WHEEL_UP && *mp_unit() < 20)
		*mp_unit() += 1;
	else if (code == WHEEL_DW && *mp_unit() > 5)
		*mp_unit() -= 1;
	return (0);
}

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

int	raycasting_key(int key, t_cub *cub)
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
	else if (key == KEY_TAB)
	{
		if (cub->tab)
			cub->tab = 0;
		else
			cub->tab = 1;
	}
	else if (key == KEY_SFT)
		cub->sft = 3;
	else if (key == KEY_ALT)
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
	if (key == KEY_ESC)
		close_win();
	return (0);
}
