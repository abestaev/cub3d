/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:14:52 by melmarti          #+#    #+#             */
/*   Updated: 2024/11/04 15:56:44 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_go_down(t_player *p)
{
	double	new_x;
	double	new_y;

	new_x = p->pos.x - p->p_dir_x * p->plr_speed;
	new_y = p->pos.y - p->p_dir_y * p->plr_speed;
	if (!hit_box(p, new_x, p->pos.y))
		p->pos.x = new_x;
	if (!hit_box(p, p->pos.x, new_y))
		p->pos.y = new_y;
}

void	ft_go_up(t_player *p)
{
	double	new_x;
	double	new_y;

	new_x = p->pos.x + p->p_dir_x * p->plr_speed;
	new_y = p->pos.y + p->p_dir_y * p->plr_speed;
	if (!hit_box(p, new_x, p->pos.y))
		p->pos.x = new_x;
	if (!hit_box(p, p->pos.x, new_y))
		p->pos.y = new_y;
}
