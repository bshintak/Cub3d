/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 21:40:14 by hanhuka           #+#    #+#             */
/*   Updated: 2023/02/24 16:50:55 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	minimap_loop(t_cub *cub, t_ray *ray)
{
	print_minimap(cub);
	ray->i = -1;
	cub->mp_color = rgb_spectrum();
	while (++ray->i < CUB_W)
	{
		raycasting(cub, ray, 2);
		minimap_raycasting(cub, ray);
	}
	print_map_collectible(cub);
	print_map_door(cub);
	draw_player(cub, *mp_unit() + 5);
}

void	minimap_raycasting(t_cub *cub, t_ray *ray)
{
	double	m;
	double	b;
	double	size;

	if (ray->side == 1)
		ray->wall_hit_x = ray->wall_x + (double)ray->map_x;
	else
		ray->wall_hit_y = ray->wall_x + (double)ray->map_y;
	if (!ray->ray_dir_x)
		m = 1e30;
	else
		m = ray->ray_dir_y / ray->ray_dir_x;
	b = cub->pos_y - (m * cub->pos_x);
	if (ray->side == 1)
		ray->wall_hit_y = m * ray->wall_hit_x + b;
	else
	{
		if (!m)
			ray->wall_hit_x = 1e30;
		else
			ray->wall_hit_x = (ray->wall_hit_y - b) / m;
	}
	size = sqrt((cub->pos_x - ray->wall_hit_x) * (cub->pos_x - ray->wall_hit_x)
			+ (cub->pos_y - ray->wall_hit_y) * (cub->pos_y - ray->wall_hit_y));
	draw_vector(cub, -0.66 * ray->camera_x, -1, size * (*mp_unit()));
}

void	raycasting(t_cub *cub, t_ray *ray, int opt)
{
	ray->camera_x = 2 * ray->i / (double)CUB_W - 1;
	ray->ray_dir_x = cub->dir_x + cub->plane_x * ray->camera_x;
	ray->ray_dir_y = cub->dir_y + cub->plane_y * ray->camera_x;
	calc_delta_dist(ray);
	calc_side_dist(ray, cub);
	if (!opt)
		hit_wall(cub, ray);
	else if (opt == 1)
		hit_t_wall(cub, ray);
	else if (opt == 3)
		hit_c_wall(cub, ray);
	else
		hit_m_wall(cub, ray);
	ray->line_h = (int)(CUB_H / ray->perpendicular);
	ray->start = (-ray->line_h + cub->h) / 2 + CUB_H / 2;
	ray->end = (ray->line_h + cub->h) / 2 + CUB_H / 2;
	if (ray->side == 0)
		ray->wall_x = cub->pos_y + ray->perpendicular * ray->ray_dir_y;
	else
		ray->wall_x = cub->pos_x + ray->perpendicular * ray->ray_dir_x;
	ray->wall_x -= floor((ray->wall_x));
}

int	get_side(t_ray ray)
{
	if (ray.side == 0)
	{
		if (ray.ray_dir_x > 0)
			return (C_WE);
		return (C_EA);
	}
	else
	{
		if (ray.ray_dir_y > 0)
		{
			return (C_NO);
		}
		return (C_SO);
	}
}

int	raycasting_loop(t_cub *cub)
{
	t_ray	ray;

	ray.i = -1;
	if (!cub->alt)
		move_mouse(cub);
	animate_collec(cub);
	move(cub, cub->w - cub->s, cub->a - cub->d);
	rotate(cub, cub->a_r - cub->a_l, cub->up - cub->dw);
	create_image(cub, &cub->frame, CUB_W, CUB_H);
	while (++ray.i < CUB_W && !cub->tab)
	{
		raycasting(cub, &ray, 0);
		print_textures(cub, ray);
		transparency_loop(cub, &ray);
	}
	if (!cub->m || cub->m == 1)
		minimap_loop(cub, &ray);
	else if (cub->m == 2 || cub->m == 3)
		minimap_loop_s(cub, &ray);
	if (cub->l)
		print_battery(cub);
	mlx_clear_window(cub->mlx, cub->mlx_w);
	mlx_put_image_to_window(cub->mlx, cub->mlx_w, cub->frame.img, 0, 0);
	mlx_destroy_image(cub->mlx, cub->frame.img);
	return (0);
}
