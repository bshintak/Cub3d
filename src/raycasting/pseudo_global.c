/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pseudo_global.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 19:11:34 by bshintak          #+#    #+#             */
/*   Updated: 2023/02/18 05:51:09 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	*mp_unit(void)
{
	static int	cubaskgfkasf;

	return (&cubaskgfkasf);
}

int	*starting_screen(void)
{
	static int	aaaaaaaaaaaaaaahhhhh;

	return (&aaaaaaaaaaaaaaahhhhh);
}

t_cub	*mouse_cub(void)
{
	static t_cub	massive_bruh;

	return (&massive_bruh);
}
