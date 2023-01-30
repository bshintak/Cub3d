/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:00:23 by bshintak          #+#    #+#             */
/*   Updated: 2023/01/30 18:13:31 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_w(t_cub *cub)
{
	if (cub->map[(int)cub->pos_y][(int)(cub->pos_x + cub->dir_x * MOVE)] == '0')
		cub->pos_x += cub->dir_x * MOVE;
	if (cub->map[(int)(cub->pos_y + cub->dir_x * MOVE)][(int)cub->pos_x] == '0')
		cub->pos_y += cub->dir_y * MOVE;
}

void	move_s(t_cub *cub)
{
	if (cub->map[(int)cub->pos_y][(int)(cub->pos_x + cub->dir_x * MOVE)] == '0')
		cub->pos_x -= cub->dir_x * MOVE;
	if (cub->map[(int)(cub->pos_y + cub->dir_x * MOVE)][(int)cub->pos_x] == '0')
		cub->pos_y -= cub->dir_y * MOVE;
}

void	rotate_right(t_cub *cub)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub->dir_x;
	cub->dir_x = cub->dir_x * cos(ROT) - cub->dir_y * sin(ROT);
	cub->dir_y = old_dir_x * sin(ROT) + cub->dir_y * cos(ROT);
	old_plane_x = cub->plane_x;
	cub->plane_x = cub->plane_x * cos(ROT) - cub->plane_y * sin(ROT);
	cub->plane_y = old_plane_x * sin(ROT) + cub->plane_y * cos(ROT);
}

void	rotate_left(t_cub *cub)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub->dir_x;
	cub->dir_x = cub->dir_x * cos(-ROT) - cub->dir_y * sin(-ROT);
	cub->dir_y = old_dir_x * sin(-ROT) + cub->dir_y * cos(-ROT);
	old_plane_x = cub->plane_x;
	cub->plane_x = cub->plane_x * cos(-ROT) - cub->plane_y * sin(-ROT);
	cub->plane_y = old_plane_x * sin(-ROT) + cub->plane_y * cos(-ROT);
}

int	raycasting_key(int key, t_cub *cub)
{
	if (key == KEY_ESC)
		close_win();
	if (key == KEY_W)
		move_w(cub);
	if (key == KEY_S)
		move_s(cub);
	if (key == KEY_L)
		rotate_left(cub);
	if (key == KEY_R)
		rotate_right(cub);
	return (0);
}
