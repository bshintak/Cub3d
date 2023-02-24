/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:02:55 by bshintak          #+#    #+#             */
/*   Updated: 2023/02/24 17:00:29 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	close_win(t_cub *cub)
{
	free_textures(cub);
	mlx_clear_window(cub->mlx, cub->mlx_w);
	mlx_destroy_window(cub->mlx, cub->mlx_w);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	free_matrix(cub->map);
	exit(0);
	return (0);
}
