/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_frame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:15:59 by melmarti          #+#    #+#             */
/*   Updated: 2024/11/04 14:49:22 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_refresh(t_player *p)
{
	update_position(p);
	ft_sort_elem_by_dist(p, p->all_elem, p->nb_door + p->nb_sprite);
	ft_handle_doors(p, p->all_elem);
	ft_color_background(p->img);
	ft_raycast_walls(p);
	ft_raycast(p);
	ft_minimap(p);
	mlx_string_put(p->img->mlx_ptr, p->img->win_ptr, 100, 100, 0xFFFFFF, "Hello, welcome to Cub3D !");
	mlx_put_image_to_window(p->img->mlx_ptr, p->img->win_ptr, p->img->img_ptr, 0, 0);
	return (0);
}
