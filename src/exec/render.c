/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:21:24 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/01 12:06:35 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void get_mini_pos(t_player *p)
{
	double	y;
	double	x;
	int		index_x;
	int		index_y;

	index_y = 0;
	y = S_HEIGHT * 5/6;
	while (index_y < ft_count_lines(p->map))
	{
		index_x = 0;
		x = 0;
		while (index_x < ft_count_columns(p->map) && p->map[index_y][index_x])
		{
			if (isplayer(p->map[index_y][index_x]))
			{
				p->mini->p_x = x;
				p->mini->p_y = y;
			}
			x += 20;
			index_x++;
		}
		y += 20;
		index_y++;
	}
}

int get_mini_y_index_after(t_player *p, int index)
{
	int y;

	y = round(p->p_y);
	while (p->map[y] && y < (int)ft_strlen(p->map[y]) && y < index)
	{
		y++;
	}
	return(y);
}

int get_mini_y_index_before(t_player *p, int index)
{
	int y;

	y = round(p->p_y);
	while (y >= 0 && p->map[y] && y > index)
	{
		y--;
	}
	return(y);
}

int get_mini_x_index_after(t_player *p, int index)
{
	int x;

	x = round(p->p_x);
	while (x < (int)ft_strlen(p->map[x]) && p->map[(int)p->p_y][x] && x < index)
	{
		x++;
	}
	return(x);
}

int get_mini_x_index_before(t_player *p, int index)
{
	int x;

	x = round(p->p_x);
	while (x >= 0 && p->map[(int)p->p_y][x] && x > index)
	{
		x--;
	}
	return(x);
}

void	ft_minimap_render(t_player *p, char **map)
{
	double	y;
	double	x;
	int		index_x;
	int		index_y;
	int start_x;
	int end_x;
	int start_y;
	int end_y;

	start_x = get_mini_x_index_before(p, p->p_x - 3);
	end_x = get_mini_x_index_after(p, p->p_x + 3);
	start_y = get_mini_y_index_before(p, p->p_y - 3);
	end_y = get_mini_y_index_after(p, p->p_y + 3);
	printf("p_x %f\n", p->p_x);
	printf("p_y %f\n", p->p_y);
	
	printf("start_x %d, end_x %d, start_y %d, end_y %d\n",start_x , end_x, start_y, end_y);
	
	y = S_HEIGHT * 5/6;
	index_y = start_y;
	while (index_y <= end_y)
	{
		index_x = start_x;
		x = 0;
		while (index_x <= end_x)
		{
			if (map[index_y][index_x] == '1')
				ft_draw_tile(p->img, x, y, 10, 0xEF92EE);
			else if (map[index_y][index_x] == '0' || isplayer(map[index_y][index_x]))
				ft_draw_tile(p->img, x, y, 10, COLOR_DARK_GRAY);
			x += 10;
			index_x++;
		}
		y += 10;
		index_y++;
	}
	ft_draw_tile(p->img, 3 * 10, S_HEIGHT * 5/6 + 3 * 10, 10, COLOR_BLUE);
}

void	ft_player_render(t_player *p)
{
	ft_draw_tile(p->img, p->mini->p_x, p->mini->p_y, 10, COLOR_BLUE);
}

void	ft_cub_render(t_player *p)
{
	ft_refresh(p);
	mlx_hook(p->img->win_ptr, KeyPress, KeyPressMask, ft_handle_hook, p);
	mlx_hook(p->img->win_ptr, 33, 1L << 17, &ft_escape, p);
	mlx_loop(p->img->mlx);
}
