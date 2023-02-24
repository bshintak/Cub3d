/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 19:42:02 by bshintak          #+#    #+#             */
/*   Updated: 2023/02/24 17:38:52 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	mouse_hook(int code)
{
	t_coords	c;

	if (*starting_screen())
	{
		mlx_mouse_get_pos(mouse_cub()->mlx, mouse_cub()->mlx_w, &c.ix, &c.iy);
		if (c.ix >= (CUB_W / 2 - 150) && c.ix <= (CUB_W / 2 + 150) && c.iy \
			>= (CUB_H / 2 - 55) && c.iy <= (CUB_H / 2 + 54)
			&& code == 1)
		{
			*starting_screen() = 0;
			mlx_mouse_hide(mouse_cub()->mlx, mouse_cub()->mlx_w);
		}
		return (1);
	}
	if (code == WHEEL_UP && *mp_unit() < 20)
		*mp_unit() += 1;
	else if (code == WHEEL_DW && *mp_unit() > 1)
		*mp_unit() -= 1;
	return (0);
}
