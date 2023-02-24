/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_utils3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanhuka <hanhuka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:57:01 by ralves-g          #+#    #+#             */
/*   Updated: 2023/02/15 20:52:24 by hanhuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	parse_error(char *line, t_cub *cub, char *msg)
{
	int	i;

	if (line)
		free(line);
	i = -1;
	while (++i < 4)
		if (cub->walls[i])
			free(cub->walls[i]);
	if (msg)
		printf("%s", msg);
	return (1);
}

void	free_textures_char(t_cub cub)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (cub.walls[i])
			free(cub.walls[i]);
		i++;
	}
}
