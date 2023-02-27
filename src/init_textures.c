/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:51:49 by bshintak          #+#    #+#             */
/*   Updated: 2023/02/25 17:23:30 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	start_images(t_cub *cub)
{
	int	i;

	cub->background = mlx_xpm_file_to_image(cub->mlx, BACKGROUND, &i, &i);
	cub->start = mlx_xpm_file_to_image(cub->mlx, START, &i, &i);
	cub->start_selected = mlx_xpm_file_to_image(cub->mlx, START_SELEC, &i, &i);
	if (!cub->background || !cub->start || !cub->start_selected)
	{
		if (cub->background)
			mlx_destroy_image(cub->mlx, cub->background);
		if (cub->start)
			mlx_destroy_image(cub->mlx, cub->start);
		if (cub->start_selected)
			mlx_destroy_image(cub->mlx, cub->start_selected);
		return (1);
	}
	return (0);
}

int	doors(t_cub *cub)
{
	int	y;
	int	x;

	y = -1;
	while (cub->map[++y])
	{
		x = -1;
		while (cub->map[y][++x])
			if (cub->map[y][x] == 'D')
				cub->parsing_doors = 1;
	}
	if (!cub->parsing_doors)
		return (0);
	cub->doors.img = mlx_xpm_file_to_image(cub->mlx, DOOR_TEXTURE,
			&cub->doors.x_size, &cub->doors.y_size);
	if (!cub->doors.img)
		return (1);
	cub->doors.addr = mlx_get_data_addr(cub->doors.img,
			&cub->doors.bits_per_pixel, &cub->doors.line_length,
			&cub->doors.endian);
	return (0);
}

void	free_textures(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < 4)
		if (cub->wall_t[i].img)
			mlx_destroy_image(cub->mlx, cub->wall_t[i].img);
	if (cub->start)
		mlx_destroy_image(cub->mlx, cub->start);
	if (cub->start_selected)
		mlx_destroy_image(cub->mlx, cub->start_selected);
	if (cub->background)
		mlx_destroy_image(cub->mlx, cub->background);
	if (cub->parsing_doors)
	{
		if (cub->doors.img)
			mlx_destroy_image(cub->mlx, cub->doors.img);
	}
	if (cub->parsing_collectible)
		free_collect(cub);
}

int	error_init_textures(t_cub *cub)
{
	printf("Error\nInvalid texture path\n");
	free_matrix(cub->map);
	free_textures_char(*cub);
	free_textures(cub);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	return (1);
}

int	init_textures(t_cub *cub)
{
	int	i;

	cub->mlx = mlx_init();
	cub->parsing_doors = 0;
	cub->parsing_collectible = 0;
	init_textures_null(cub);
	i = 0;
	while (i < 4)
	{
		cub->wall_t[i].img = mlx_xpm_file_to_image(cub->mlx, cub->walls[i],
				&cub->wall_t[i].x_size, &cub->wall_t[i].y_size);
		if (!cub->wall_t[i].img)
			return (error_init_textures(cub));
		cub->wall_t[i].addr = mlx_get_data_addr(cub->wall_t[i].img,
				&cub->wall_t[i].bits_per_pixel, &cub->wall_t[i].line_length,
				&cub->wall_t[i].endian);
		i++;
	}
	if (doors(cub) || start_images(cub) || init_collectible(cub))
		return (error_init_textures(cub));
	free_textures_char(*cub);
	return (0);
}
