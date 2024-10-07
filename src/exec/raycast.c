/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:02:26 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/07 16:00:09 by melmarti         ###   ########.fr       */
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

