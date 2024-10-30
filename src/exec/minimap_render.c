/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:21:24 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/30 14:55:36 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	ft_get_mini_y_offset(t_player *p)
{
	return ((S_HEIGHT * 5 / 6) - p->pos.y * p->mini->tile_size + 2.5);
}

double	ft_get_mini_x_offset(t_player *p)
{
	return (10 * p->mini->tile_size - p->pos.x * p->mini->tile_size + 2.5);
}

void	ft_minimap_render(t_player *p, char **map)
{
	int		index_x;
	int		index_y;
	t_point	start;

	start.y = ft_get_mini_y_offset(p);
	index_y = 0;
	while (index_y < p->nb_line)
	{
		index_x = 0;
		start.x = ft_get_mini_x_offset(p);
		while (index_x < p->nb_col)
		{
			if (map[index_y][index_x] == '1')
				ft_draw_tile(p->img, start, p->mini->tile_size, COLOR_CYAN);
			start.x += p->mini->tile_size;
			index_x++;
		}
		start.y += p->mini->tile_size;
		index_y++;
	}
}

void	ft_minimap(t_player *p)
{
	t_point	start;
	t_point	end;

	start.x = 0;
	end.x = 2 * p->mini->nb_tile * p->mini->tile_size;
	start.y = p->mini->pos.y - 10 * p->mini->tile_size;
	end.y = p->mini->pos.y + p->mini->nb_tile * p->mini->tile_size;
	ft_draw_mini_background(p->img, start, end);
	ft_minimap_render(p, p->map);
	ft_player_render(p);
	start.x = p->mini->pos.x + 2.5;
	start.y = p->mini->pos.y + 2.5;
	end.x = p->mini->pos.x + (p->p_dir_x * 15);
	end.y = p->mini->pos.y + (p->p_dir_y * 15);
	ft_draw_line(p, start, end);
	ft_countouring_render_00(p);
}
