/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:02:26 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/30 11:32:05 by melmarti         ###   ########.fr       */
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

/* We will take the distance from the camera plane to avoid the fish eyes effect */
/* If we get the sizeonly throuht the coordinate of the player we'll have the distortion,
if we increment some points along the camera vectore the distance will always have good proportion according to the distance from the wall to the camera vector */
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

void	ft_find_hits(t_player *p, t_sprite *sprite)
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

void	ft_get_door_text(t_player *p, t_sprite *door, t_ray *ray, int x)
{
	int		y;
	double	dist_factor;

	ray->text_x = (int)(ray->wall_x * DOOR_TEXT_SIZE);
	if ((ray->side == 0 && ray->dir_x < 0) || (ray->side == 1
			&& ray->dir_y > 0))
		ray->text_x = DOOR_TEXT_SIZE - ray->text_x - 1;
	ray->text_step = (double)DOOR_TEXT_SIZE / ray->wall_height;
	ray->pos = (ray->start_pxl - S_HEIGHT / 2 + ray->wall_height / 2)
		* ray->text_step;
	y = ray->start_pxl - 1;
	dist_factor = 1.0 / (1.0 + ray->wall_dist * ray->wall_dist * 0.1);
	while (++y < ray->end_pxl)
	{
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
		if (ray->color > 0 && ray->wall_dist < p->ray->dist_buffer[x])
			my_pixel_put(p->img, x, y, ft_calc_dark(ray->color, dist_factor));
	}
}

void	ft_raycast_elem(t_player *p)
{
	int	x;
	int	i;
	
	i = -1;
	while (++i < p->nb_sprite + p->nb_door)
	{
		if (p->all_elem[i].type == SPRITE)
		{
			ft_calcul_sprite(p, &p->all_elem[i].sprite_ray, &p->all_elem[i], i);
			ft_calc_sprite_hight(&p->all_elem[i].sprite_ray);
			ft_draw_sprites(p, &p->all_elem[i].sprite_ray, &p->all_elem[i]);
		}
		else if (p->all_elem[i].type == DOOR)
		{
			x = -1;
			while (++x < S_WIDTH)
			{
				ft_init_ray(p, &p->all_elem[i].ray, x);
				ft_calcul_dda(p, &p->all_elem[i].ray);
				ft_find_hits(p, &p->all_elem[i]);
				ft_get_door_size(p, &p->all_elem[i].ray);
				ft_get_door_text(p, &p->all_elem[i], &p->all_elem[i].ray, x);
			}
		}
	}
}
