/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:02:26 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/14 20:10:23 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	ft_init_ray(t_player *p, int x)
{
	double camera_x ;
	
	camera_x = 2 * x / (double)S_WIDTH - 1;
	p->ray->dir_x = p->p_dir_x + p->plane_x * camera_x;
	p->ray->dir_y = p->p_dir_y + p->plane_y * camera_x;
	p->ray->delta_dist_x = fabs(1 / p->ray->dir_x);
	p->ray->delta_dist_y = fabs(1 / p->ray->dir_y);
	p->ray->map_x = (int)p->pos.x;
	p->ray->map_y = (int)p->pos.y;
}
void	ft_cast_ray(t_player *p)
{
	t_ray	*ray;
	int		x;
	int		step_x;
	int		step_y;

	ray = p->ray;
	x = 0;
	while (x < S_WIDTH)
	{
		ft_init_ray(p, x);
		
		if (ray->dir_x < 0)
		{
			step_x = -1;
			ray->side_dist_x = (p->pos.x - ray->map_x) * ray->delta_dist_x;
		}
		else
		{
			step_x = 1;
			ray->side_dist_x = (ray->map_x + 1.0 - p->pos.x) * ray->delta_dist_x;
		}
		if (ray->dir_y < 0)
		{
			step_y = -1;
			ray->side_dist_y = (p->pos.y - ray->map_y) * ray->delta_dist_y;
		}
		else
		{
			step_y = 1;
			ray->side_dist_y = (ray->map_y + 1.0 - p->pos.y) * ray->delta_dist_y;
		}
		while (1)
		{
			if (ray->side_dist_x < ray->side_dist_y)
			{
				ray->side_dist_x += ray->delta_dist_x;
				ray->map_x += step_x;
				ray->side = 0;
			}
			else
			{
				ray->side_dist_y += ray->delta_dist_y;
				ray->map_y += step_y;
				ray->side = 1;
			}
			if (ft_inside_wall(p, ray->map_x, ray->map_y))
				break ;
		}
		ft_get_wall_size(p, x);
		x++;
	}

}
