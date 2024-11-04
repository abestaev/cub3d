/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_frame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:15:59 by melmarti          #+#    #+#             */
/*   Updated: 2024/11/04 17:12:37 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_handle_message(t_player *p)
{
	int	i;

	i = ft_find_closest_door(p, p->all_elem);
	if (ft_is_in_adjacent_cells(p, p->pos.x, p->pos.y, 'P'))
	{
		if (p->all_elem[i].door_state == CLOSE)
		{
			mlx_string_put(p->img->mlx_ptr, p->img->win_ptr, 0.9 * S_WIDTH / 2,
				5 * S_HEIGHT / 6, 0xFFFFFF, "Open door with \"O\"");
		}
		if (p->all_elem[i].door_state == OPEN)
		{
			mlx_string_put(p->img->mlx_ptr, p->img->win_ptr, 0.9 * S_WIDTH / 2,
				5 * S_HEIGHT / 6, 0xFFFFFF, "Close door with \"C\"");
		}
	}
}

int	ft_refresh(t_player *p)
{
	update_position(p);
	ft_sort_elem_by_dist(p, p->all_elem, p->nb_door + p->nb_sprite);
	ft_handle_doors(p, p->all_elem);
	ft_color_background(p->img);
	ft_raycast_walls(p);
	ft_raycast(p);
	ft_minimap(p);
	mlx_put_image_to_window(p->img->mlx_ptr, p->img->win_ptr, p->img->img_ptr,
		0, 0);
	ft_handle_message(p);
	return (0);
}
