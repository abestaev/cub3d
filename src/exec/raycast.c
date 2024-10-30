/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:02:26 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/30 16:04:57 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_raycast(t_player *p)
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
				ft_find_door_hit(p, &p->all_elem[i]);
				ft_get_door_size(p, &p->all_elem[i].ray);
				ft_get_door_text(p, &p->all_elem[i], &p->all_elem[i].ray, x);
			}
		}
	}
}
