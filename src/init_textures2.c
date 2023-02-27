/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:41:09 by ralves-g          #+#    #+#             */
/*   Updated: 2023/02/25 16:49:24 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_textures_null(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		cub->wall_t[i].img = NULL;
		cub->collec_l[i].img = NULL;
	}
	cub->doors.img = NULL;
	cub->start = NULL;
	cub->start_selected = NULL;
	cub->background = NULL;
}
