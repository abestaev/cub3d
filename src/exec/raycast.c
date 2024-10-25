/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:02:26 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/25 17:41:30 by melmarti         ###   ########.fr       */
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
	dist_factor = 1.0 / (1.0 + ray->wall_dist * ray->wall_dist * 0.05);
	while (y < ray->end_pxl)
	{
		text_y = (int)pos & (TEXTURE_SIZE - 1);
		pos += text_step;
		color = p->texture[text_index][TEXTURE_SIZE * text_y + text_x];
		my_pixel_put(p->img, x, y, ft_calcul_darkness(color, dist_factor));
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
		x++;
	}
}

int	ft_hit(t_player *p, int x, int y)
{
	if (x > 0 && x < p->nb_col && y > 0 && y < p->nb_line)
	{
		if (p->map[y][x] == 'P')
			return (1);
		if (p->map[y][x] == 'V')
			return (1);
	}
	return (0);
}

void	ft_find_hits(t_player *p, t_sprite *sprite)
{
	int	i;
	int	end;

	if (p->nb_col < p->nb_line)
		end = p->nb_line;
	else
		end = p->nb_col;
	i = -1;
	while (++i < 800)
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
			p->sprite->hit_flag = 1;
			break ;
		}
	}
}

void	ft_get_sprite_size(t_player *p, t_ray *ray)
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

void	ft_get_door_text(t_player *p, t_sprite *sprite, t_ray *ray, int x)
{
	int		y;
	int		text_x;
	int		text_y;
	double	text_step;
	double	pos;
	int		color;
	double	dist_factor;

	(void)p;
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
		if (sprite->door_state == CLOSE)
			color = sprite->text[0][TEXTURE_SIZE * text_y + text_x];
		else if (sprite->door_state == OPEN)
		{
			color = sprite->text[6][TEXTURE_SIZE * text_y + text_x];
		}
		else if (sprite->door_state == IS_OPENING)
		{
			color = sprite->text[sprite->door_animation_index][TEXTURE_SIZE
				* text_y + text_x];
		}
		if (color > 0)
			my_pixel_put(p->img, x, y, ft_calcul_darkness(color, dist_factor));
		y++;
	}
}

void	ft_get_sprite_text(t_player *p, t_sprite *sprite, t_ray *ray, int x)
{
	ft_get_door_text(p, sprite, ray, x);
	// ft_get_vilain_text();
}
t_sprite	*ft_find_next_layer(t_sprite *sprite, int nb_sprite)
{
	int			i;
	t_sprite	*last_sprite;

	last_sprite = NULL;
	i = 0;
	while (i < nb_sprite)
	{
		if (!sprite[i].already_print)
		{
			last_sprite = &sprite[i];
			break ;
		}
		i++;
	}
	while (i < nb_sprite - 1)
	{
		if (last_sprite->ray.wall_dist < sprite[i + 1].ray.wall_dist)
		{
			if (!sprite[i].already_print)
				last_sprite = &sprite[i + 1];
		}
		i++;
	}
	if (last_sprite)
		last_sprite->already_print = 1;
	return (last_sprite);
}

void	ft_copy_sprite_in_main_img(t_image *main_img, t_image *img)
{
	int	offset_main;
	int	offset_sprite;

	int x, y;
	y = 0;
	while (y < S_HEIGHT)
	{
		x = 0;
		while (x < S_WIDTH)
		{
			offset_main = (y * main_img->line_length) + (x * 4);
			offset_sprite = (y * img->line_length) + (x * 4);
			if (*(int *)(img->addr + offset_sprite) != 0x00000000)
				*(int *)(main_img->addr + offset_main) = *(int *)(img->addr
						+ offset_sprite);
			x++;
		}
		y++;
	}
}

void	ft_superpose_sprite(t_player *p)
{
	int			i;
	t_sprite	*next_sprite;

	next_sprite = NULL;
	i = 0;
	while (i < p->nb_sprite)
	{
		// next_sprite = ft_find_next_layer(p->sprite, p->nb_sprite);
		// if(!next_sprite)
		// 	break ;
		// ft_copy_sprite_in_main_img(p->img, p->sprite[i].img);
		// mlx_destroy_image(p->img->mlx, p->sprite[i].img->img);
		// free(next_sprite->img);
		i++;
	}
}

void	ft_cast_ray(t_player *p)
{
	int	x;
	int	i;

	ft_raycast_walls(p);
	ft_sort_sprites_by_dist(p);
	i = -1;
	while (++i < p->nb_sprite)
	{
		x = 0;
		while (x < S_WIDTH)
		{
			ft_init_ray(p, &p->sprite[i].ray, x);
			ft_calcul_dda(p, &p->sprite[i].ray);
			ft_find_hits(p, &p->sprite[i]);
			// if (p->sprite[i].hit_flag)
			// {
			ft_get_sprite_size(p, &p->sprite[i].ray);
			ft_get_sprite_text(p, &p->sprite[i], &p->sprite[i].ray, x);
			// p->sprite[i].hit_flag = 0;
			// }
			x++;
		}
	}
}
