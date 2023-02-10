/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshintak <bshintak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:20:45 by ralves-g          #+#    #+#             */
/*   Updated: 2023/02/10 18:27:34 by bshintak         ###   ########.fr       */
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
				cub->pos_x = x + 0.5;
				cub->pos_y = y + 0.5;
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

void	calc_sideDist(t_ray *ray, t_cub *cub)
{
	ray->map_x = (int)cub->pos_x;
	ray->map_y = (int)cub->pos_y;
	if (ray->rayDir_x < 0)
	{
		ray->steps_x = -1;
		ray->sideDist_x = (cub->pos_x - ray->map_x) * ray->deltaDist_x;
	}
	else
	{
		ray->steps_x = 1;
		ray->sideDist_x = (ray->map_x + 1.0 - cub->pos_x) * ray->deltaDist_x;
	}
	if (ray->rayDir_y < 0)
	{
		ray->steps_y = -1;
		ray->sideDist_y = (cub->pos_y - ray->map_y) * ray->deltaDist_y;
	}
	else
	{
		ray->steps_y = 1;
		ray->sideDist_y = (ray->map_y + 1.0 - cub->pos_y) * ray->deltaDist_y;
	}
}

void	calc_deltaDist(t_ray *ray)
{
	if (ray->rayDir_x == 0)
		ray->deltaDist_x = 1e30;
	else
		ray->deltaDist_x = fabs(1 / ray->rayDir_x);
	if (ray->rayDir_y == 0)
		ray->deltaDist_y = 1e30;
	else
		ray->deltaDist_y = fabs(1 / ray->rayDir_y);
}

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
		ray.step = 1.0 * cub->frame.img_height / ray.line_h;
		ray.start = (-ray.line_h + cub->h) / 2 + CUB_H / 2;
		if (ray.start < 0)
			ray.start = 0;
		ray.end = (ray.line_h + cub->h) / 2 + CUB_H / 2;
		if (ray.end > CUB_H)
			ray.end = CUB_H;
		ray.tex_pos = (ray.start - ((CUB_H + cub->h) / 2) + ray.line_h / 2) * ray.step;
		// if (ray.side == 1)
			draw_ray(cub, &ray);
		// else
			// draw_ray(cub, ray, 0x0000FF00);
	}
		// print_minimap(cub);
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
