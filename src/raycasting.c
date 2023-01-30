/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:56:09 by bshintak          #+#    #+#             */
/*   Updated: 2023/01/30 17:18:44 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ray_main(t_cub *cub)
{
	cub->mlx = mlx_init();
	cub->mlx_w = mlx_new_window(cub->mlx, CUB_W, CUB_H, "Cub3d");
	search_player(cub);
	search_direction(cub);
	search_plane(cub);
	mlx_clear_window(cub->mlx, cub->mlx_w);
	mlx_hook(cub->mlx_w, 2, 1, raycasting_key, cub);
	mlx_loop_hook(cub->mlx, raycasting_loop, cub);
	mlx_hook(cub->mlx_w, 17, 0, close_win, (void *)"Did you give up? 😲​​\n");
	mlx_loop(cub->mlx);
}
