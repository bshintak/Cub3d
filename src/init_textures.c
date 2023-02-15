/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:51:49 by bshintak          #+#    #+#             */
/*   Updated: 2023/02/15 15:52:26 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	init_textures(t_cub *cub)
{
	int	i;

	cub->mlx = mlx_init();
	i = -1;
	while (++i < 4)
		cub->wall_t[i].img = NULL;
	i = 0;
	while (i < 4)
	{
		cub->wall_t[i].img = mlx_xpm_file_to_image(cub->mlx, cub->walls[i],
				&cub->wall_t[i].x_size, &cub->wall_t[i].y_size);
		if (!cub->wall_t[i].img)
		{
			printf("Error\nInvalid texture path\n");
			free_matrix(cub->map);
			free_textures(*cub);
			return (1);
		}
		cub->wall_t[i].addr = mlx_get_data_addr(cub->wall_t[i].img,
				&cub->wall_t[i].bits_per_pixel, &cub->wall_t[i].line_length,
				&cub->wall_t[i].endian);
		i++;
	}
	free_textures(*cub);
	return (0);
}
