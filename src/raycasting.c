/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:56:09 by bshintak          #+#    #+#             */
/*   Updated: 2023/02/08 17:34:43 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int *mp_unit(void)
{
	static int cubaskgfkasf;

	return (&cubaskgfkasf);
}

void	move_mouse(t_cub *cub)
{
	int x;
	int y;

	mlx_mouse_get_pos(cub->mlx, cub->mlx_w, &x, &y);
	mlx_mouse_move(cub->mlx, cub->mlx_w, CUB_W / 2, CUB_H / 2);
	// printf("mouse x[%d] y[%d]\n", x, y);
	if ((x != CUB_W / 2 || y != CUB_H / 2) && x >= 0 && x <= CUB_W 
		&& y >= 0 && y <= CUB_H)
	{
		if (x > CUB_W / 2)
			cub->mouse = ((double)x - CUB_W / 2) * MOUSE_SENSITIVITY_X;
		else if (x < CUB_W / 2)
			cub->mouse = ((double)x - CUB_W / 2) * MOUSE_SENSITIVITY_X;
		if (y > CUB_H / 2)
			cub->h -= ((double)y - CUB_H / 2) * MOUSE_SENSITIVITY_Y;
		else if (y < CUB_H / 2)
			cub->h -= ((double)y - CUB_H / 2) * MOUSE_SENSITIVITY_Y;
	}
}

void	ray_main(t_cub *cub)
{
	int i;
	i = 0;
	cub->mlx = mlx_init();
	cub->mlx_w = mlx_new_window(cub->mlx, CUB_W, CUB_H, "Cub3d");
	// cub->frame.img = mlx_xpm_file_to_image(cub->mlx, "Background_64.xpm", &i, &i);
	// mlx_put_image_to_window(cub->mlx, cub->mlx_w, cub->frame.img, 0 ,0);
	cub->w = 0;
	cub->a = 0;
	cub->s = 0;
	cub->d = 0;
	cub->r = 0;
	cub->l = 0;
	cub->h = 0;
	*mp_unit() = 10;
	cub->up = 0;
	cub->dw = 0;
	cub->tab = 0;
	cub->alt = 0;
	cub->sft = 1;
	cub->mouse = 0;
	mlx_mouse_hide(cub->mlx, cub->mlx_w);
	// create_image(cub, &cub->frame, CUB_W, CUB_H);
	init_images(cub);
	search_player(cub);
	search_direction(cub);
	search_plane(cub);
	mlx_clear_window(cub->mlx, cub->mlx_w);
	mlx_hook(cub->mlx_w, 2, 1L << 0, raycasting_key, cub);
	mlx_hook(cub->mlx_w, 3, 1L << 1, key_up, cub);
	mlx_mouse_hook(cub->mlx_w, mouse_hook, NULL);
	mlx_loop_hook(cub->mlx, raycasting_loop, cub);
	mlx_hook(cub->mlx_w, 17, 0, close_win, (void *)"Did you give up? 😲​​\n");
	mlx_loop(cub->mlx);
}
