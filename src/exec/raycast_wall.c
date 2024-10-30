/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:09:17 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/30 14:36:56 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_calcul_wall_text(t_player *p, int x)
{
	int		y;
	int		text_index;
	double	dist_factor;
	t_ray	*ray;

	ray = p->ray;
	text_index = ft_get_text_index(p->ray);
	ray->text_x = (int)(p->ray->wall_x * WALL_TEXT_SIZE);
	if ((p->ray->side == 0 && p->ray->dir_x < 0) || (p->ray->side == 1
			&& p->ray->dir_y > 0))
		ray->text_x = WALL_TEXT_SIZE - ray->text_x - 1;
	ray->text_step = (double)WALL_TEXT_SIZE / p->ray->wall_height;
	ray->pos = (ray->start_pxl - S_HEIGHT / 2 + p->ray->wall_height / 2)
		* ray->text_step;
	y = ray->start_pxl;
	dist_factor = 1.0 / (1.0 + ray->wall_dist * ray->wall_dist * 0.05);
	while (y < ray->end_pxl)
	{
		ray->text_y = (int)ray->pos & (WALL_TEXT_SIZE - 1);
		ray->pos += ray->text_step;
		ray->color = p->texture[text_index][WALL_TEXT_SIZE * ray->text_y
			+ ray->text_x];
		my_pixel_put(p->img, x, y, ft_calc_dark(ray->color, dist_factor));
		y++;
	}
}

void	ft_get_wall_size(t_player *p, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	ray->wall_height = (int)(S_HEIGHT / ray->wall_dist);
	ray->start_pxl = -ray->wall_height / 2 + S_HEIGHT / 2;
	if (ray->start_pxl < 0)
		ray->start_pxl = 0;
	ray->end_pxl = ray->wall_height / 2 + S_HEIGHT / 2;
	if (ray->end_pxl >= S_HEIGHT)
		ray->end_pxl = S_HEIGHT - 1;
	if (ray->side == 0)
		ray->wall_x = p->pos.y + ray->wall_dist * ray->dir_y;
	else
		ray->wall_x = p->pos.x + ray->wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

void	ft_find_walls(t_player *p)
{
	t_ray	*ray;

	ray = p->ray;
	while (1)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ft_inside_wall(p, ray->map_x, ray->map_y))
			break ;
	}
}

void	ft_calcul_dda(t_player *p, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (p->pos.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - p->pos.x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (p->pos.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - p->pos.y) * ray->delta_dist_y;
	}
}

void	ft_raycast_walls(t_player *p)
{
	int	x;

	x = 0;
	while (x < S_WIDTH)
	{
		ft_init_ray(p, p->ray, x);
		ft_calcul_dda(p, p->ray);
		ft_find_walls(p);
		ft_get_wall_size(p, p->ray);
		ft_calcul_wall_text(p, x);
		p->ray->dist_buffer[x] = p->ray->wall_dist;
		x++;
	}
}
