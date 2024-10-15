/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:21:24 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/15 11:59:52 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_mini_y_index_after(t_player *p, int index)
{
	int	y;

	y = p->pos.y;
	while (y < (int)ft_strlen(p->map[0]) && y < index)
		y++;
	return (round(y));
}

int	get_mini_y_index_before(t_player *p, int index)
{
	int	y;

	y = p->pos.y;
	while (y > 0 && p->map[y][(int)p->pos.x] && y > index)
	{
		y--;
	}
	return (round(y));
}

int	get_mini_x_index_after(t_player *p, int index)
{
	int	x;
	int	y;

	y = p->pos.y;
	x = p->pos.x;
	while (x < ft_count_columns(p->map) && p->map[y][x] && x < index)
	{
		x++;
	}
	return (round(x));
}

int	get_mini_x_index_before(t_player *p, int index)
{
	int	x;

	x = p->pos.x;
	while (x > 0 && x > index)
	{
		x--;
	}
	if (round(p->pos.x) > 12)
		return (round(x) - 1);
	return (round(x));
}

double ft_get_mini_y_offset(t_player *p, double mini_tile_size)
{
	if (p->pos.y < ft_count_lines(p->map) / 2 - 1)
		return ((S_HEIGHT * 5 / 6) - p->pos.y * mini_tile_size);
	else
		return ((S_HEIGHT * 5 / 6) - (6 * mini_tile_size));
}


double ft_get_mini_x_offset(t_player *p, double mini_tile_size)
{
	if (round(p->pos.x) > ft_count_columns(p->map) / 2)
		return (0);
	else
		return ((7.0 - p->pos.x) * mini_tile_size);
}

void	ft_minimap_render(t_player *p, char **map)
{
	double	y;
	double	x;
	int		index_x;
	int		index_y;
	int		start_x;
	int		end_x;
	int		start_y;
	int		end_y;
	double		mini_tile_size;

	mini_tile_size = 10.0;
	// printf("p_x %f, p_y %f, case %c\n", p->pos.x - 1, p->pos.y, p->map[(int)round(p->pos.y)][(int)round(p->pos.x) - 1]);
	start_x = get_mini_x_index_before(p, round(p->pos.x) - 7);
	end_x = get_mini_x_index_after(p, round(p->pos.x) + 7);
	start_y = get_mini_y_index_before(p, round(p->pos.y) - 7);
	end_y = get_mini_y_index_after(p, round(p->pos.y) + 7);
	// printf("start_x %d, end_x %d, start_y %d, end_y %d\n", start_x, end_x, start_y, end_y);
	// y = ft_get_mini_y_offset(p, mini_tile_size);
	y = ft_get_mini_y_offset(p, mini_tile_size);
	index_y = start_y;
	while (index_y <= end_y)
	{
		index_x = start_x;
		x = ft_get_mini_x_offset(p, mini_tile_size);
		while (index_x <= end_x)
		{
			// printf("%c : x = %d y = %d\n", map[index_y][index_x], index_x, index_y);
			// printf("p->pos.y : %f, x : %f, y : %f\n", p->pos.y, x, y);
			if (map[index_y][index_x] == '1')
			{
				ft_draw_tile(p->img, x, y, mini_tile_size, 0xEF92EE);
			}
			else if (map[index_y][index_x] == '0' || isplayer(map[index_y][index_x]))
			{
				ft_draw_tile(p->img, x, y, mini_tile_size, COLOR_DARK_GRAY);
			}
			x += mini_tile_size;
			index_x++;
		}
		y += mini_tile_size;
		index_y++;
	}
	ft_draw_tile(p->img, 7 * mini_tile_size, (S_HEIGHT * 5 / 6), mini_tile_size, COLOR_BLUE);
}

void	ft_player_render(t_player *p)
{
	ft_draw_tile(p->img, p->mini->p_x, p->mini->p_y, 20, COLOR_BLUE);
}
