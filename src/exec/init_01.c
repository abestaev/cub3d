/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:24:51 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/17 16:21:54 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_ray(t_player *p, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)S_WIDTH - 1;
	p->ray->dir_x = p->p_dir_x + p->plane_x * camera_x;
	p->ray->dir_y = p->p_dir_y + p->plane_y * camera_x;
	p->ray->delta_dist_x = fabs(1 / p->ray->dir_x);
	p->ray->delta_dist_y = fabs(1 / p->ray->dir_y);
	p->ray->map_x = (int)p->pos.x;
	p->ray->map_y = (int)p->pos.y;
}

void	ft_mlx_init(t_player *p)
{
	p->img = malloc(sizeof(t_image));
	p->img->mlx = mlx_init();
	p->img->win_ptr = mlx_new_window(p->img->mlx, S_WIDTH, S_HEIGHT, "Cub3D");
	p->img->img = mlx_new_image(p->img->mlx, S_WIDTH, S_HEIGHT);
	if (!p->img->img)
		return;
	p->img->addr = mlx_get_data_addr(p->img->img, &p->img->bits_per_pixel,
			&p->img->line_length, &p->img->endian);
	mlx_hook(p->img->win_ptr, KeyPress, KeyPressMask, ft_handle_hook, p);
	mlx_hook(p->img->win_ptr, 33, 1L << 17, &ft_escape, p);
	p->img->p = p;
}
