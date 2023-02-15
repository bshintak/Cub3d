/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 19:31:49 by bshintak          #+#    #+#             */
/*   Updated: 2023/02/13 19:50:34 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	rotate_mouse(t_cub *cub, double *dir, double *plane)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = *dir;
	old_plane_x = *plane;
	old_dir_x = cub->dir_x;
	cub->dir_x = cub->dir_x * cos(ROT * cub->mouse)
		- cub->dir_y * sin(ROT * cub->mouse);
	cub->dir_y = old_dir_x * sin(ROT * cub->mouse)
		+ cub->dir_y * cos(ROT * cub->mouse);
	old_plane_x = cub->plane_x;
	cub->plane_x = cub->plane_x * cos(ROT * cub->mouse)
		- cub->plane_y * sin(ROT * cub->mouse);
	cub->plane_y = old_plane_x * sin(ROT * cub->mouse)
		+ cub->plane_y * cos(ROT * cub->mouse);
	*dir = old_dir_x;
	*plane = old_plane_x;
}

void	rotate_player(t_cub *cub, double *dir, double *plane, int rl)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = *dir;
	old_plane_x = *plane;
	old_dir_x = cub->dir_x;
	cub->dir_x = cub->dir_x * cos(ROT * rl) - cub->dir_y * sin(ROT * rl);
	cub->dir_y = old_dir_x * sin(ROT * rl) + cub->dir_y * cos(ROT * rl);
	old_plane_x = cub->plane_x;
	cub->plane_x = cub->plane_x * cos(ROT * rl) - cub->plane_y * sin(ROT * rl);
	cub->plane_y = old_plane_x * sin(ROT * rl) + cub->plane_y * cos(ROT * rl);
	*dir = old_dir_x;
	*plane = old_plane_x;
}

void	rotate(t_cub *cub, int rl, int ud)
{
	double	old_dir_x;
	double	old_plane_x;

	rotate_player(cub, &old_dir_x, &old_plane_x, rl);
	rotate_mouse(cub, &old_dir_x, &old_plane_x);
	cub->mouse = 0;
	cub->h += ud * 10;
	if (cub->h > CUB_H)
		cub->h = CUB_H - 1;
	if (cub->h < -CUB_H)
		cub->h = -(CUB_H - 1);
}
