/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:24:51 by melmarti          #+#    #+#             */
/*   Updated: 2024/11/04 14:51:13 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_player_orientation_ew(char c, t_player *p)
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

void	ft_init_player_orientation_ns(char c, t_player *p)
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
	ft_init_player_orientation_ew(c, p);
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
				p->pos.x = j + 0.5;
				p->pos.y = i + 0.5;
				ft_init_player_orientation_ns(p->map[i][j], p);
				break ;
			}
			j++;
		}
		i++;
	}
}

void	ft_init_minimap(t_player *p)
{
	t_minimap	*mini;

	mini = malloc(sizeof(t_minimap));
	if (!mini)
		ft_escape(p);
	ft_memset(mini, 0, sizeof(t_minimap));
	p->mini = mini;
	p->mini->nb_tile = 10;
	p->mini->tile_size = 10;
	p->mini->pos.x = p->mini->nb_tile * p->mini->tile_size;
	p->mini->pos.y = (S_HEIGHT * 5 / 6);
}

void	ft_player_init(t_player *p, t_data *data)
{
	p->ray = malloc(sizeof(t_ray));
	p->ray_doors = malloc(sizeof(t_ray));
	if (!p->img || !p->img->img_ptr || !p->ray || !p->ray_doors)
		ft_escape(p);
	ft_memset(p->ray, 0, sizeof(t_ray));
	ft_memset(p->ray_doors, 0, sizeof(t_ray));
	p->map = data->map;
	ft_init_player_pos(p);
	ft_init_minimap(p);
	p->plr_speed = SPEED;
	p->speed_rot = ROT_SPEED;
	p->data = data;
	p->nb_line = p->data->textures->nb_lines;
	p->nb_col = p->data->textures->col;
	p->move_forward = 0;
	p->move_backward = 0;
	p->move_left = 0;
	p->move_right = 0;
	p->rotate_left = 0;
	p->rotate_right = 0;
	p->data->old_time = 0;
	p->data->actual_time = 0;
}
