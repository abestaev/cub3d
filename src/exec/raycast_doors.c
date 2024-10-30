/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_doors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:02:26 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/30 14:34:50 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_find_door_hit(t_player *p, t_sprite *sprite)
{
	int	i;

	i = -1;
	while (++i < 40)
	{
		if (sprite->ray.side_dist_x < sprite->ray.side_dist_y)
		{
			sprite->ray.side_dist_x += sprite->ray.delta_dist_x;
			sprite->ray.map_x += sprite->ray.step_x;
			sprite->ray.side = 0;
		}
		else
		{
			sprite->ray.side_dist_y += sprite->ray.delta_dist_y;
			sprite->ray.map_y += sprite->ray.step_y;
			sprite->ray.side = 1;
		}
		if (ft_hit(p, sprite->ray.map_x, sprite->ray.map_y)
			&& (int)sprite->pos.x == (int)sprite->ray.map_x
			&& (int)sprite->pos.y == (int)sprite->ray.map_y)
		{
			break ;
		}
	}
}

void	ft_get_door_size(t_player *p, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->side_dist_x - ray->delta_dist_x) + 0.5;
	else
		ray->wall_dist = (ray->side_dist_y - ray->delta_dist_y) + 0.5;
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

static void	ft_get_door_animation_text(t_player *p, t_ray *ray, t_sprite *door,
		t_point pos)
{
	double	dist_factor;

	dist_factor = 1.0 / (1.0 + ray->wall_dist * ray->wall_dist * 0.1);
	ray->text_y = (int)ray->pos & (DOOR_TEXT_SIZE - 1);
	ray->pos += ray->text_step;
	if (door->door_state == CLOSE)
		ray->color = p->door_text[0][DOOR_TEXT_SIZE * ray->text_y
			+ ray->text_x];
	else if (door->door_state == OPEN)
		ray->color = p->door_text[5][DOOR_TEXT_SIZE * ray->text_y
			+ ray->text_x];
	else if (door->door_state == IS_OPENING)
	{
		ray->color = p->door_text[door->animation_index][DOOR_TEXT_SIZE
			* ray->text_y + ray->text_x];
	}
	if (ray->color > 0 && ray->wall_dist < p->ray->dist_buffer[(int)pos.x])
		my_pixel_put(p->img, pos.x, pos.y, ft_calc_dark(ray->color,
				dist_factor));
}

void	ft_get_door_text(t_player *p, t_sprite *door, t_ray *ray, int x)
{
	t_point	pos;

	pos.x = x;
	ray->text_x = (int)(ray->wall_x * DOOR_TEXT_SIZE);
	if ((ray->side == 0 && ray->dir_x < 0) || (ray->side == 1
			&& ray->dir_y > 0))
		ray->text_x = DOOR_TEXT_SIZE - ray->text_x - 1;
	ray->text_step = (double)DOOR_TEXT_SIZE / ray->wall_height;
	ray->pos = (ray->start_pxl - S_HEIGHT / 2 + ray->wall_height / 2)
		* ray->text_step;
	pos.y = ray->start_pxl - 1;
	while (++pos.y < ray->end_pxl)
		ft_get_door_animation_text(p, ray, door, pos);
}

void	ft_get_doors_size(t_player *p, t_ray *ray)
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
