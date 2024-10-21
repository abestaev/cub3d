/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_doors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:02:26 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/21 17:38:25 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_calcul_doors_text(t_player *p, int x, int doors_index)
{
	int		y;
	int		text_x;
	int		text_y;
	double	text_step;
	double	pos;
	int		color;
	double	dist_factor;
	t_ray	*ray;

	ray = p->ray_doors;
	text_x = (int)(ray->wall_x * TEXTURE_SIZE);
	if ((ray->side == 0 && ray->dir_x < 0) || (ray->side == 1
			&& ray->dir_y > 0))
		text_x = TEXTURE_SIZE - text_x - 1;
	text_step = (double)TEXTURE_SIZE / ray->wall_height;
	pos = (ray->start_pxl - S_HEIGHT / 2 + ray->wall_height / 2) * text_step;
	y = ray->start_pxl;
	dist_factor = 1.0 / (1.0 + ray->wall_dist * ray->wall_dist * 0.1);
	while (y < ray->end_pxl)
	{
		text_y = (int)pos & (TEXTURE_SIZE - 1);
		pos += text_step;
		color = p->doors->text_doors[doors_index][TEXTURE_SIZE * text_y
			+ text_x];
		if (color > 0 && ray->wall_dist <= p->ray->wall_dist)
			my_pixel_put(p->img, x, y,  ft_calcul_darkness(color, dist_factor));
		y++;
	}
}

void	ft_find_walls_doors(t_player *p, t_ray *ray)
{
	int		i;
	int end;

	i = -1;
	if(ft_count_columns(p->map) < ft_count_lines(p->map))
		end = ft_count_lines(p->map);
	else 
		end = ft_count_columns(p->map);
	while (++i < end)
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
		if (ft_inside_doors(p, ray->map_x, ray->map_y))
			break;
	}
}

