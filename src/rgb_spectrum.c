/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_spectrum.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:59:02 by ralves-g          #+#    #+#             */
/*   Updated: 2023/02/22 17:03:06 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rgb_spectrum3(int *red, int *green, int *blue, int angle)
{
	if (angle < 180)
	{
		*red = 0;
		*green = 255;
		*blue = (angle - 120) * 4;
	}
	else if (angle < 240)
	{
		*red = 0;
		*green = (240 - angle) * 4;
		*blue = 255;
	}
	else if (angle < 300)
	{
		*red = (angle - 240) * 4;
		*green = 0;
		*blue = 255;
	}
	else
	{
		*red = 255;
		*green = 0;
		*blue = (360 - angle) * 4;
	}
}

void	rgb_spectrum2(int *red, int *green, int *blue, int angle)
{
	if (angle < 60)
	{
		*red = 255;
		*green = angle * 4;
		*blue = 0;
	}
	else if (angle < 120)
	{
		*red = (120 - angle) * 4;
		*green = 255;
		*blue = 0;
	}
	else if (angle < 120)
	{
		*red = (120 - angle) * 4;
		*green = 255;
		*blue = 0;
	}
	else
		rgb_spectrum3(red, green, blue, angle);
}

int	rgb_spectrum(void)
{
	static int	angle = 0;
	static int	swtch = 0;
	int			red;
	int			green;
	int			blue;

	if (angle == 0)
		swtch = 0;
	else if (angle == 360)
		swtch = 1;
	rgb_spectrum2(&red, &green, &blue, angle);
	if (!swtch)
		angle += 2;
	else
		angle -= 2;
	return ((red << 16) + (green << 8) + blue);
}
