/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:06:10 by bshintak          #+#    #+#             */
/*   Updated: 2023/01/30 18:32:36 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	search_player(t_cub *cub)
{
	int	y;
	int	x;

	y = 0;
	while (cub->map[y])
	{
		x = 0;
		while (cub->map[y][x])
		{
			if (cub->map[y][x] == 'N' || cub->map[y][x] == 'S' ||
			cub->map[y][x] == 'W' || cub->map[y][x] == 'E')
			{
				cub->pos_x = x;
				cub->pos_y = y;
				cub->direction = cub->map[y][x];
				cub->map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
}

void	search_direction(t_cub *cub)
{
	if (cub->direction == 'N' || cub->direction == 'S')
	{
		cub->dir_x = 0;
		if (cub->direction == 'N')
			cub->dir_y = -1;
		else if (cub->direction == 'S')
			cub->dir_y = 1;
	}
	else if (cub->direction == 'W' || cub->direction == 'E')
	{
		cub->dir_y = 0;
		if (cub->direction == 'W')
			cub->dir_x = -1;
		else if (cub->direction == 'E')
			cub->dir_x = 1;
	}
}

void	search_plane(t_cub *cub)
{
	if (cub->direction == 'N' || cub->direction == 'S')
	{
		cub->plane_x = (0.66 * cub->dir_y) * 1;
		cub->plane_y = (0.66 * cub->dir_x) * 1;
	}
	else if (cub->direction == 'W' || cub->direction == 'E')
	{
		cub->plane_x = (0.66 * cub->dir_y) * -1;
		cub->plane_y = (0.66 * cub->dir_x) * -1;
	}
}
