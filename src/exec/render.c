/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:21:24 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/01 16:14:07 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_mini_pos(t_player *p)
{
	double	y;
	double	x;
	int		index_x;
	int		index_y;

	index_y = 0;
	y = S_HEIGHT * 5 / 6;
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

int	get_mini_y_index_after(t_player *p, int index)
{
	int	y;

	y = p->p_y;
	while (y < (int)ft_strlen(p->map[y]) && y < index)
	{
		y++;
	}
	return (round(y));
}

int	get_mini_y_index_before(t_player *p, int index)
{
	int	y;

	y = p->p_y;
	while (y > 0 && p->map[y][(int)p->p_x] && y > index)
	{
		y--;
	}
	return (round(y));
}

int	get_mini_x_index_after(t_player *p, int index)
{
	int	x;
	int	y;

	y = p->p_y;
	x = p->p_x;
	while (x < (int)ft_strlen(p->map[y]) && p->map[y][x] && x < index)
	{
		x++;
	}
	return (round(x));
}

int	get_mini_x_index_before(t_player *p, int index)
{
	int	x;

	x = p->p_x;
	while (x > 0 && x > index)
	{
		x--;
	}
	return (round(x));
}

double ft_get_mini_offset(t_player *p)
{
	if(round(p->p_x) < ft_strlen(p->map[0]) / 2)
	{
		printf("%f, %zu\n",round(p->p_x), ft_strlen(p->map[0]));
		printf("yo\n");
		return (ft_strlen(p->map[0]) / 2 - round(p->p_x));
	}
	return(0);
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
	int		mini_tile_size;

	mini_tile_size = 10;
	start_x = get_mini_x_index_before(p, p->p_x - 7);
	end_x = get_mini_x_index_after(p, p->p_x + 7);
	start_y = get_mini_y_index_before(p, p->p_y - 7);
	end_y = get_mini_y_index_after(p, p->p_y + 7);
	printf("p_x %f\n", p->p_x);
	printf("p_y %f\n", p->p_y);
	printf("start_x %d, end_x %d, start_y %d, end_y %d\n", start_x, end_x,
		start_y, end_y);
	y = S_HEIGHT * 5 / 6;
	index_y = start_y;
	while (index_y < end_y)
	{
		index_x = start_x;
		x = ft_get_mini_offset(p);
		while (index_x <= end_x)
		{
			// printf("%c : x = %d y = %d\n", map[index_y][index_x], index_x, index_y);
			if (map[index_y][index_x] == '1')
			{
				ft_draw_tile(p->img, x, y, mini_tile_size, 0xEF92EE);
			}
			else if (map[index_y][index_x] == '0'
				|| isplayer(map[index_y][index_x]))
			{
				ft_draw_tile(p->img, x, y, mini_tile_size, COLOR_DARK_GRAY);
			}
			x += mini_tile_size;
			index_x++;
		}
		y += mini_tile_size;
		index_y++;
	}
	ft_draw_tile(p->img, 7 * mini_tile_size, S_HEIGHT * 5 / 6 + 7
		* mini_tile_size, mini_tile_size, COLOR_BLUE);
}

void	ft_player_render(t_player *p)
{
	ft_draw_tile(p->img, p->mini->p_x, p->mini->p_y, 20, COLOR_BLUE);
}

void	ft_cub_render(t_player *p)
{
	ft_refresh(p);
	mlx_hook(p->img->win_ptr, KeyPress, KeyPressMask, ft_handle_hook, p);
	mlx_hook(p->img->win_ptr, 33, 1L << 17, &ft_escape, p);
	mlx_loop(p->img->mlx);
}
