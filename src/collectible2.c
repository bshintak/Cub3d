/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 16:22:18 by ralves-g          #+#    #+#             */
/*   Updated: 2023/02/24 17:05:12 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	init_collectible2(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (!i)
			cub->collec_l[i].img = mlx_xpm_file_to_image(cub->mlx, \
		BATTERY_TEX_F, &cub->collec_l[i].x_size, &cub->collec_l[i].y_size);
		else if (i == 1)
			cub->collec_l[i].img = mlx_xpm_file_to_image(cub->mlx, \
		BATTERY_TEX_R, &cub->collec_l[i].x_size, &cub->collec_l[i].y_size);
		else if (i == 2)
			cub->collec_l[i].img = mlx_xpm_file_to_image(cub->mlx, \
		BATTERY_TEX_B, &cub->collec_l[i].x_size, &cub->collec_l[i].y_size);
		else if (i == 3)
			cub->collec_l[i].img = mlx_xpm_file_to_image(cub->mlx, \
		BATTERY_TEX_L, &cub->collec_l[i].x_size, &cub->collec_l[i].y_size);
		if (!cub->collec_l[i].img)
			return (1);
		cub->collec_l[i].addr = mlx_get_data_addr(cub->collec_l[i].img, \
			&cub->collec_l[i].bits_per_pixel, &cub->collec_l[i].line_length,
				&cub->collec_l[i].endian);
	}
	return (0);
}

void	free_collect(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (cub->collec_l[i].img)
			mlx_destroy_image(cub->mlx, cub->collec_l[i].img);
	}
}

int	check_collectible(t_cub *cub)
{
	int	y;
	int	x;

	y = -1;
	cub->parsing_collectible = 0;
	while (cub->map[++y])
	{
		x = -1;
		while (cub->map[y][++x])
		{
			if (cub->map[y][x] == 'B')
				cub->parsing_collectible = 1;
		}
	}
	return (cub->parsing_collectible);
}

void	animate_collec(t_cub *cub)
{
	static unsigned long	a_start = 0;
	static int				clock = 0;

	if (time_ms() - a_start >= 600)
	{
		a_start = time_ms();
		if (clock == 3)
			clock = 0;
		else
			clock++;
		cub->collec = cub->collec_l[clock];
	}
}
