/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:08:50 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/31 17:01:42 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_find_closest_door(t_player *p, t_sprite *all_elem)
{
	int	i;

	i = p->nb_door + p->nb_sprite - 1;
	while (i >= 0)
	{
		if (all_elem[i].type == DOOR)
			return (i);
		i--;
	}
	return (0);
}

static void	ft_open_door(t_sprite *door, double curr_time, double *old_time)
{
	curr_time = ft_get_usec_time();
	if (curr_time - *old_time > 100)
	{
		door->animation_index++;
		*old_time = curr_time;
	}
	if (door->animation_index == 5)
	{
		door->door_state = OPEN;
		// door->animation_index = 0;
		old_time = 0;
	}
}

static void	ft_close_door(t_sprite *door, double curr_time, double *old_time)
{
	curr_time = ft_get_usec_time();
	if (curr_time - *old_time > 100)
	{
		door->animation_index--;
		*old_time = curr_time;
	}
	if (door->animation_index == 0)
	{
		door->door_state = CLOSE;
		// door->animation_index = 0;
		old_time = 0;
	}
}

/* The sprites are sorted from farthest to closest,
	so the last is always the closest to the player */
void	ft_handle_doors(t_player *p, t_sprite *all_elem)
{
	double			curr_time;
	static double	old_time = 0;
	int				i;

	curr_time = 0;
	i = ft_find_closest_door(p, all_elem);
	if (all_elem[i].door_state == IS_OPENING)
	{
		ft_open_door(&all_elem[i], curr_time, &old_time);
	}
	else if (all_elem[i].door_state == IS_CLOSING)
	{
		ft_close_door(&all_elem[i], curr_time, &old_time);
	}
}
