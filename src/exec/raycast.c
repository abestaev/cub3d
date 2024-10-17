/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:02:26 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/17 20:11:26 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
void	ft_calcul_wall_text(t_player *p, int x)
{
	int		y;
	int		text_index;
	int		text_x;
	int		text_y;
	double	text_step;
	double	pos;
	int		color;
	double	dist_factor;
	t_ray	*ray;

	ray = p->ray;
	text_index = ft_get_text_index(p, p->ray);
	text_x = (int)(p->ray->wall_x * TEXTURE_SIZE);
	if ((p->ray->side == 0 && p->ray->dir_x < 0) || (p->ray->side == 1
			&& p->ray->dir_y > 0))
		text_x = TEXTURE_SIZE - text_x - 1;
	text_step = (double)TEXTURE_SIZE / p->ray->wall_height;
	pos = (ray->start_pxl - S_HEIGHT / 2 + p->ray->wall_height / 2) * text_step;
	y = ray->start_pxl;
	dist_factor = 1.0 / (1.0 + ray->wall_dist * ray->wall_dist * 0.1);
	while (y < ray->end_pxl)
	{
		text_y = (int)pos & (TEXTURE_SIZE - 1);
		pos += text_step;
		color = p->texture[text_index][TEXTURE_SIZE * text_y + text_x];
		my_pixel_put(p->img, x, y, ft_calcul_darkness(color, dist_factor));
		y++;
	}
}
void	ft_calcul_wall_text_doors(t_player *p, int x)
{
	int		y;
	int		text_index;
	int		text_x;
	int		text_y;
	double	text_step;
	double	pos;
	int		color;
	double	dist_factor;
	t_ray	*ray;

	ray = p->ray;
	text_index = ft_get_text_index(p, p->ray);
	text_x = (int)(p->ray->wall_x * TEXTURE_SIZE);
	if ((p->ray->side == 0 && p->ray->dir_x < 0) || (p->ray->side == 1
			&& p->ray->dir_y > 0))
		text_x = TEXTURE_SIZE - text_x - 1;
	text_step = (double)TEXTURE_SIZE / p->ray->wall_height;
	pos = (ray->start_pxl - S_HEIGHT / 2 + p->ray->wall_height / 2) * text_step;
	y = ray->start_pxl;
	dist_factor = 1.0 / (1.0 + ray->wall_dist * ray->wall_dist * 0.1);
	while (y < ray->end_pxl)
	{
		text_y = (int)pos & (TEXTURE_SIZE - 1);
		pos += text_step;
		color = p->texture[text_index][TEXTURE_SIZE * text_y + text_x];
		if(text_index == 4 && color > 0)
			my_pixel_put(p->img, x, y, ft_calcul_darkness(color, dist_factor));
		y++;
	}
}

/* We will take the distance from the camera plane to avoid the fish eyes effect */
/* If we get the sizeonly throuht the coordinate of the player we'll have the distortion,
if we increment some points along the camera vectore the distance will always have good proportion according to the distance from the wall to the camera vector */
void	ft_get_wall_size(t_player *p)
{
	t_ray	*ray;

	ray = p->ray;
	if (ray->side == 0)
		p->ray->wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		p->ray->wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	ray->wall_height = (int)(S_HEIGHT / p->ray->wall_dist);
	ray->start_pxl = -ray->wall_height / 2 + S_HEIGHT / 2;
	if (ray->start_pxl < 0)
		ray->start_pxl = 0;
	ray->end_pxl = ray->wall_height / 2 + S_HEIGHT / 2;
	if (ray->end_pxl >= S_HEIGHT)
		ray->end_pxl = S_HEIGHT - 1;
	if (ray->side == 0)
		ray->wall_x = p->pos.y + p->ray->wall_dist * ray->dir_y;
	else
		ray->wall_x = p->pos.x + p->ray->wall_dist * ray->dir_x;
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

void	ft_find_walls_doors(t_player *p)
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
		if (ft_inside_wall_doors(p, ray->map_x, ray->map_y))
			break ;
	}
}

void	ft_calcul_dda(t_player *p)
{
	t_ray	*ray;

	ray = p->ray;
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

void	ft_cast_ray(t_player *p)
{
	int	x;

	x = 0;
	while (x < S_WIDTH)
	{
		ft_init_ray(p, x);
		ft_calcul_dda(p);
		ft_find_walls(p);
		ft_get_wall_size(p);
		ft_calcul_wall_text(p, x);
		x++;
	}
}

void	ft_cast_ray_doors(t_player *p)
{
	int	x;

	x = 0;
	while (x < S_WIDTH)
	{
		ft_init_ray(p, x);
		ft_calcul_dda(p);
		ft_find_walls_doors(p);
		ft_get_wall_size(p);
		ft_calcul_wall_text_doors(p, x);
		x++;
	}
}
