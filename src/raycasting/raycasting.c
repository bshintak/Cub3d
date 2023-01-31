/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:56:09 by bshintak          #+#    #+#             */
/*   Updated: 2023/01/31 16:04:16 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	raycasting_loop(t_cub *cub)
{
	t_ray	ray;

	ray.i = -1;
	while (++ray.i < CUB_W)
	{
		ray.camera_x = 2 * ray.i / (double)CUB_W - 1;
		ray.ray_dir_x = cub->dir_x + cub->plane_x * ray.camera_x;
		ray.ray_dir_y = cub->dir_y + cub->plane_y * ray.camera_x;
		calc_delta_dist(&ray);
		calc_side_dist(&ray, cub);
		hit_wall(cub, &ray);
		ray.line_h = (int)(CUB_H / ray.perpendicular);
		ray.start = -ray.line_h / 2 + CUB_H / 2;
		if (ray.start < 0)
			ray.start = 0;
		ray.end = ray.line_h / 2 + CUB_H / 2;
		if (ray.end >= CUB_H)
			ray.end = CUB_H -1;
		put_color(&ray, cub);
	}
	return (0);
}

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
