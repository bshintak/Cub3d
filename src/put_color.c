/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:35:08 by bshintak          #+#    #+#             */
/*   Updated: 2023/01/30 18:43:02 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	put_color(t_ray *ray, t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < ray->start)
		mlx_pixel_put(cub->mlx, cub->mlx_w, CUB_W - ray->i - 1,
		i, (0x000000FF / 6));
	while (++i < ray->end)
	{
		if (ray->side == 0)
			mlx_pixel_put(cub->mlx, cub->mlx_w, CUB_W - ray->i - 1,
			i, (0x0000FF00 / 2));
		else
			mlx_pixel_put(cub->mlx, cub->mlx_w, CUB_W - ray->i - 1,
			i, (0x0000FF00 / 6));
	}
	while (++i < CUB_H)
		mlx_pixel_put(cub->mlx, cub->mlx_w, CUB_W - ray->i - 1,
		i, (0x000000FF / 20));
}
