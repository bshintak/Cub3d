/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 19:42:02 by bshintak          #+#    #+#             */
/*   Updated: 2023/02/13 19:49:10 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	mouse_hook(int code)
{
	if (code == WHEEL_UP && *mp_unit() < 20)
		*mp_unit() += 1;
	else if (code == WHEEL_DW && *mp_unit() > 5)
		*mp_unit() -= 1;
	return (0);
}
