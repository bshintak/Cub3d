/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:20:45 by ralves-g          #+#    #+#             */
/*   Updated: 2023/02/11 21:27:04 by bshintak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	hit_wall(t_cub *cub, t_ray *ray)
{
	ray->hitWall = 0;
	while (!(ray->hitWall))
	{
		if (ray->sideDist_x < ray->sideDist_y)
		{
			ray->sideDist_x += ray->deltaDist_x;
			ray->map_x += ray->steps_x;
			ray->side = 0;
		}
		else
		{
			ray->sideDist_y += ray->deltaDist_y;
			ray->map_y += ray->steps_y;
			ray->side = 1;
		}
		if (cub->map[ray->map_y][ray->map_x] == '1')
			ray->hitWall = 1;
	}
	if (ray->side == 0)
	{
		if (ray->rayDir_x < 0)
			ray->side = WE;
		else
			ray->side = EA;
		ray->perpendicular = ray->sideDist_x - ray->deltaDist_x;
	}
	else
	{
		if (ray->rayDir_y < 0)
			ray->side = NO;
		else
			ray->side = SO;
		ray->perpendicular = ray->sideDist_y - ray->deltaDist_y;
	}
}

void	calc_texture(t_ray *ray, t_cub *cub)
{
	if (ray->side == EA || ray->side == WE)
		ray->wall_x = cub->pos_y + ray->perpendicular * ray->rayDir_y;
	else if (ray->side == NO || ray->side == SO)
		ray->wall_x = cub->pos_x + ray->perpendicular * ray->rayDir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * cub->tex[ray->side].img_width);
	if ((ray->side == EA || ray->side == WE) && ray->rayDir_x < 0)
		ray->tex_x = cub->tex[ray->side].img_width - ray->tex_x - 1;
	else if ((ray->side == NO || ray->side == SO) && ray->rayDir_y > 0)
		ray->tex_x = cub->tex[ray->side].img_width - ray->tex_x - 1;
}

int	raycasting_loop(t_cub *cub)
{
	t_ray			ray;

	ray.i = -1;
	if (!cub->alt)
		move_mouse(cub);
	move(cub, cub->w - cub->s, cub->a - cub->d);
	rotate(cub, cub->r - cub->l, cub->up - cub->dw);
	create_image(cub, &cub->frame, CUB_W, CUB_H);
	while (++ray.i < CUB_W && !cub->tab)
	{
		ray.camera_x = 2 * ray.i / (double)CUB_W - 1;
		ray.rayDir_x = cub->dir_x + cub->plane_x * ray.camera_x;
		ray.rayDir_y = cub->dir_y + cub->plane_y * ray.camera_x;
		calc_deltaDist(&ray);
		calc_sideDist(&ray, cub);
		hit_wall(cub, &ray);
		calc_texture(&ray, cub);
		ray.line_h = (int)(CUB_H / ray.perpendicular);
		ray.step = 1.0 * cub->tex[ray.side].img_height / ray.line_h;
		ray.start = (-ray.line_h + cub->h) / 2 + CUB_H / 2;
		if (ray.start < 0)
			ray.start = 0;
		ray.end = (ray.line_h + cub->h) / 2 + CUB_H / 2;
		if (ray.end > CUB_H)
			ray.end = CUB_H;
		ray.tex_pos = (ray.start - ((cub->h + CUB_H) / 2) + ray.line_h / 2) * ray.step;
		draw_ray(cub, &ray);
	}
	print_minimap(cub);
	mlx_clear_window(cub->mlx, cub->mlx_w);
	mlx_put_image_to_window(cub->mlx, cub->mlx_w, cub->frame.img, 0, 0);
	mlx_destroy_image(cub->mlx, cub->frame.img);
	return (0);
}

int	main(int ac, char **av)
{
	t_cub	cub;

	if (parse_file(ac, av, &cub))
		return (1);
	print_vars(cub);
	ray_main(&cub);
}
