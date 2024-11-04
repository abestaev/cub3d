/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:24:51 by melmarti          #+#    #+#             */
/*   Updated: 2024/11/04 17:10:09 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_textures(t_player *p)
{
	ft_init_wall_textures(p);
	p->sprite_text = ft_init_sprite_text(p);
	p->door_text = ft_init_doors_text(p);
}

void	ft_init_ray(t_player *p, t_ray *ray, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)S_WIDTH - 1;
	ray->dir_x = p->p_dir_x + p->plane_x * camera_x;
	ray->dir_y = p->p_dir_y + p->plane_y * camera_x;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->map_x = (int)p->pos.x;
	ray->map_y = (int)p->pos.y;
}

void	ft_mlx_init(t_player *p)
{
	p->img = malloc(sizeof(t_image));
	if (!p->img)
		return ;
	p->img->mlx_ptr = mlx_init();
	p->img->win_ptr = mlx_new_window(p->img->mlx_ptr, S_WIDTH, S_HEIGHT,
			"Cub3D");
	p->img->img_ptr = mlx_new_image(p->img->mlx_ptr, S_WIDTH, S_HEIGHT);
	if (!p->img->img_ptr)
		return ;
	p->img->addr = mlx_get_data_addr(p->img->img_ptr, &p->img->bits_per_pixel,
			&p->img->line_length, &p->img->endian);
	p->img->p = p;
}
