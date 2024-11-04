/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:29:50 by melmarti          #+#    #+#             */
/*   Updated: 2024/11/04 12:47:40 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_inside_doors(t_player *p, int x, int y)
{
	int	i;

	i = ft_find_closest_door(p, p->all_elem);
	if (x > 0 && x < p->nb_col && y > 0 && y < p->nb_line)
	{
		if (p->map[y][x] == 'P' && p->all_elem[i].door_state == CLOSE)
			return (1);
	}
	return (0);
}

int	ft_hit(t_player *p, int x, int y)
{
	if (x > 0 && x < p->nb_col && y > 0 && y < p->nb_line)
		if (p->map[y][x] == 'P')
			return (1);
	return (0);
}

int	ft_collision(t_player *p, int x, int y)
{
	if (ft_inside_wall(p, x, y) || ft_inside_doors(p, x, y))
		return (1);
	return (0);
}

int	ft_inside_wall(t_player *p, int x, int y)
{
	if (p->map[y][x] == '1')
		return (1);
	return (0);
}

int	hit_box(t_player *p, double x, double y)
{
	return (ft_collision(p, x - HITBOX_SIZE, y - HITBOX_SIZE) || ft_collision(p,
			x + HITBOX_SIZE, y - HITBOX_SIZE) || ft_collision(p, x
			- HITBOX_SIZE, y + HITBOX_SIZE) || ft_collision(p, x + HITBOX_SIZE,
			y + HITBOX_SIZE));
}
