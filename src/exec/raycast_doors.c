/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_doors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:02:26 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/18 18:44:19 by melmarti         ###   ########.fr       */
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

	ray = p->ray;
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
		color = p->doors->text_doors[doors_index][TEXTURE_SIZE * text_y
			+ text_x];
		if (color > 0 && ray->side == 0)
			my_pixel_put(p->img, x, y, ft_calcul_darkness(color, dist_factor));
		y++;
	}
}

void	ft_find_walls_doors(t_player *p)
{
	t_ray	*ray;
	int		i;

	ray = p->ray;
	i = 0;
	while (i < ft_count_lines(p->map))
		// potentiellement voir si ca cause pas de soucis avec le fait que la map n est pas carre, potentiellement il faut iterer jusqu au cote le plus long
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
			{
				p->doors->hit_flag = 1;
				return ;
			}
			i++;
		}
	p->doors->hit_flag = 0;
}

void	ft_cast_ray_doors(t_player *p)
{
	int			x;

	x = 0;
	while (x < S_WIDTH)
	{
		ft_init_ray(p, x);
		ft_calcul_dda(p);
		ft_find_walls_doors(p);
		ft_get_wall_size(p);
		if (p->doors->hit_flag)
		{
			ft_calcul_doors_text(p, x, p->doors->index);
		}
		x++;
	}
}
