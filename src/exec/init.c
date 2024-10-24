/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:24:51 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/17 17:31:08 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_player_orientation_01(char c, t_player *p)
{
	if (c == 'E')
	{
		p->p_dir_x = 1;
		p->p_dir_y = 0;
		p->plane_x = 0;
		p->plane_y = 0.66;
	}
	else if (c == 'W')
	{
		p->p_dir_x = -1;
		p->p_dir_y = 0;
		p->plane_x = 0;
		p->plane_y = -0.66;
	}
}

void	ft_init_player_orientation_00(char c, t_player *p)
{
	if (c == 'N')
	{
		p->p_dir_x = 0;
		p->p_dir_y = -1;
		p->plane_x = 0.66;
		p->plane_y = 0;
	}
	else if (c == 'S')
	{
		p->p_dir_x = 0;
		p->p_dir_y = 1;
		p->plane_x = -0.66;
		p->plane_y = 0;
	}
	ft_init_player_orientation_01(c, p);
}

void	ft_init_player_pos(t_player *p)
{
	int	i;
	int	j;

	i = 0;
	while (p->map[i])
	{
		j = 0;
		while (p->map[i][j])
		{
			if (isplayer(p->map[i][j]))
			{
				p->pos.x = j + 0.2;
				p->pos.y = i + 0.2;
				ft_init_player_orientation_00(p->map[i][j], p);
				break ;
			}
			j++;
		}
		i++;
	}
}

void	ft_init_minimap(t_player *p)
{
	t_minimap *mini;
	
	mini = malloc(sizeof(t_minimap));
	ft_memset(mini, 0, sizeof(t_minimap));
	p->mini = mini;
	p->mini->nb_tile = 10;
	p->mini->tile_size = 10;
	p->mini->pos.x = p->mini->nb_tile * p->mini->tile_size;
	p->mini->pos.y = (S_HEIGHT * 5 / 6);
}

void	ft_player_init(t_player *p, t_data *data)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	ft_memset(ray, 0, sizeof(t_ray));
	p->map = data->map;
	ft_init_player_pos(p);
	ft_init_minimap(p);
	p->tile_size = ft_get_tile_size(p->map);
	p->ray = ray;
	p->plr_speed = SPEED;
	p->speed_rot = ROT_SPEED;
	p->data = data;
	p->move_forward = 0;
	p->move_backward = 0;
	p->move_left = 0;
	p->move_right = 0;
	p->rotate_left = 0;
	p->rotate_right = 0;
}
