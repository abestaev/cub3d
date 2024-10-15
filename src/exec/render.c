/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:21:24 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/15 11:29:41 by albestae         ###   ########.fr       */
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
	while (y < (int)ft_strlen(p->map[0]) && y < index)
		y++;
	if (round(y) >= 14)
		return (13);
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
	while (x < ft_count_columns(p->map) && p->map[y][x] && x < index)
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
	if (round(p->p_x) > 12)
		return (round(x) - 1);
	return (round(x));
}

double ft_get_mini_y_offset(t_player *p, double mini_tile_size)
{
	if (p->p_y < ft_count_lines(p->map) / 2 - 1)
		return ((S_HEIGHT * 5 / 6) - p->p_y * mini_tile_size);
	else
		return ((S_HEIGHT * 5 / 6) - (6 * mini_tile_size));
}


double ft_get_mini_x_offset(t_player *p, double mini_tile_size)
{
	if (round(p->p_x) > ft_count_columns(p->map) / 2)
		return (0);
	else
		return ((7.0 - p->p_x) * mini_tile_size);
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
	// printf("p_x %f, p_y %f, case %c\n", p->p_x - 1, p->p_y, p->map[(int)round(p->p_y)][(int)round(p->p_x) - 1]);
	start_x = get_mini_x_index_before(p, round(p->p_x) - 7);
	end_x = get_mini_x_index_after(p, round(p->p_x) + 7);
	start_y = get_mini_y_index_before(p, round(p->p_y) - 7);
	end_y = get_mini_y_index_after(p, round(p->p_y) + 7);
	printf("start_x %d, end_x %d, start_y %d, end_y %d\n", start_x, end_x, start_y, end_y);
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
			printf("p->p_y : %f, x : %f, y : %f\n", p->p_y, x, y);
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

void update_position(t_player *p)
{
    if (p->move_forward)
        ft_go_up(p);
    if (p->move_backward)
        ft_go_down(p);
    if (p->move_left)
        ft_go_right(p);
    if (p->move_right)
		ft_go_left(p);
    if (p->rotate_left)
		ft_turn_right(p);
    if (p->rotate_right)
       ft_turn_left(p);
}

int	ft_cub_render(t_player *p)
{
	update_position(p);
	ft_refresh(p);
	// mlx_hook(p->img->win_ptr, KeyPress, KeyPressMask, ft_handle_hook, p);
	return (0);
	// mlx_loop(p->img->mlx);
}
