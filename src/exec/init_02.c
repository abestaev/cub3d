/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_02.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:32:30 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/30 16:21:28 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_count_door(char **map)
{
	int	y;
	int	x;
	int	size;

	size = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P')
				size++;
			x++;
		}
		y++;
	}
	return (size);
}

int	ft_count_sprite(char **map)
{
	int	y;
	int	x;
	int	size;

	size = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'V')
				size++;
			x++;
		}
		y++;
	}
	return (size);
}

static void	ft_init_maps_door(t_player *p)
{
	int	y;
	int	x;
	int	i;

	p->door = calloc(sizeof(t_sprite), ft_count_door(p->map));
	ft_memset(p->door, 0, sizeof(t_sprite));
	p->nb_door = ft_count_door(p->map);
	i = 0;
	y = -1;
	while (p->map[++y])
	{
		x = -1;
		while (p->map[y][++x])
		{
			if (p->map[y][x] == 'P')
			{
				ft_memset(&p->door[i].sprite_ray, 0, sizeof(t_spriteray));
				p->door[i].type = DOOR;
				p->door[i].door_state = CLOSE;
				p->door[i].pos.x = x;
				p->door[i++].pos.y = y;
			}
		}
	}
}

static void	ft_init_maps_sprite(t_player *p)
{
	int	y;
	int	x;
	int	i;

	p->sprite = calloc(sizeof(t_sprite), ft_count_sprite(p->map));
	ft_memset(p->sprite, 0, sizeof(t_sprite));
	p->nb_sprite = ft_count_sprite(p->map);
	i = 0;
	y = 0;
	while (p->map[y])
	{
		x = 0;
		while (p->map[y][x])
		{
			if (p->map[y][x] == 'V')
			{
				ft_memset(&p->sprite[i].sprite_ray, 0, sizeof(t_spriteray));
				p->sprite[i].type = SPRITE;
				p->sprite[i].pos.x = x + 0.5;
				p->sprite[i++].pos.y = y + 0.5;
			}
			x++;
		}
		y++;
	}
}

void	ft_init_elements(t_player *p)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	ft_init_maps_door(p);
	ft_init_maps_sprite(p);
	p->all_elem = ft_calloc(p->nb_sprite + p->nb_door + 1, sizeof(t_sprite));
	if (!p->all_elem)
		ft_escape(p);
	while (j < p->nb_door)
	{
		p->all_elem[i] = p->door[j];
		j++;
		i++;
	}
	j = 0;
	while (j < p->nb_sprite)
	{
		p->all_elem[i] = p->sprite[j];
		j++;
		i++;
	}
}
