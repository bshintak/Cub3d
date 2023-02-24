/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_and_inits.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:56:09 by bshintak          #+#    #+#             */
/*   Updated: 2023/02/22 17:26:06 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	fun_ray(t_cub *cub)
{
	search_player(cub);
	search_direction(cub);
	search_plane(cub);
	*mouse_cub() = *cub;
	mlx_clear_window(cub->mlx, cub->mlx_w);
	mlx_hook(cub->mlx_w, 2, 1L << 0, raycasting_key, cub);
	mlx_hook(cub->mlx_w, 3, 1L << 1, key_up, cub);
	if (HAS_MOUSE)
		mlx_mouse_hook(cub->mlx_w, mouse_hook, NULL);
	mlx_loop_hook(cub->mlx, game, cub);
	mlx_hook(cub->mlx_w, 17, 0, close_win, cub);
}

void	ray_main(t_cub *cub)
{
	*starting_screen() = HAS_MOUSE;
	cub->mlx_w = mlx_new_window(cub->mlx, CUB_W, CUB_H, "Cub3d");
	cub->w = 0;
	cub->a = 0;
	cub->s = 0;
	cub->d = 0;
	cub->r = 0;
	cub->m = 0;
	cub->f = 0;
	cub->l = 0;
	cub->battery = 100;
	cub->a_r = 0;
	cub->a_l = 0;
	cub->h = 0;
	*mp_unit() = 10;
	cub->up = 0;
	cub->dw = 0;
	cub->tab = 0;
	cub->alt = 0;
	cub->sft = 1;
	cub->mouse = 0;
	fun_ray(cub);
	mlx_loop(cub->mlx);
}
