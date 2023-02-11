/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:56:09 by bshintak          #+#    #+#             */
/*   Updated: 2023/02/11 21:22:38 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	ray_main(t_cub *cub)
{
	int i;
	i = 0;
	cub->mlx = mlx_init();
	cub->mlx_w = mlx_new_window(cub->mlx, CUB_W, CUB_H, "Cub3d");
	cub->w = 0;
	cub->a = 0;
	cub->s = 0;
	cub->d = 0;
	cub->r = 0;
	cub->l = 0;
	cub->h = 0;
	*mp_unit() = 10;
	cub->up = 0;
	cub->dw = 0;
	cub->tab = 0;
	cub->alt = 0;
	cub->sft = 1;
	cub->mouse = 0;
	mlx_mouse_hide(cub->mlx, cub->mlx_w);
	init_images(cub);
	search_player(cub);
	search_direction(cub);
	search_plane(cub);
	mlx_clear_window(cub->mlx, cub->mlx_w);
	mlx_hook(cub->mlx_w, 2, 1L << 0, raycasting_key, cub);
	mlx_hook(cub->mlx_w, 3, 1L << 1, key_up, cub);
	mlx_mouse_hook(cub->mlx_w, mouse_hook, NULL);
	mlx_loop_hook(cub->mlx, raycasting_loop, cub);
	mlx_hook(cub->mlx_w, 17, 0, close_win, (void *)"Did you give up? 😲​​\n");
	mlx_loop(cub->mlx);
}
