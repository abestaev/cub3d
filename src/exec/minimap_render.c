/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renard <renard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:21:24 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/17 10:50:23 by renard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	ft_get_mini_y_offset(t_player *p)
{
	return ((S_HEIGHT * 5 / 6) - p->pos.y * MINIMAP_TILE + 2.5);
}

double	ft_get_mini_x_offset(t_player *p)
{
	return (10 * MINIMAP_TILE - p->pos.x * MINIMAP_TILE + 2.5);
}

void	ft_minimap_render(t_player *p, char **map)
{
	int	index_x;
	int	index_y;
	int	x;
	int	y;

	y = ft_get_mini_y_offset(p);
	index_y = 0;
	while (index_y < ft_count_lines(map))
	{
		index_x = 0;
		x = ft_get_mini_x_offset(p);
		while (index_x < ft_count_columns(map))
		{
			if (map[index_y][index_x] == '1')
				ft_draw_tile(p->img, x, y, MINIMAP_TILE, COLOR_CYAN);
			x += MINIMAP_TILE;
			index_x++;
		}
		y += MINIMAP_TILE;
		index_y++;
	}
}

void ft_draw_mini_background(t_image *img, int x_start, int x_end, int y_start, int y_end)
{
	double	x;
	double	y;

	x = x_start;
	while (x < x_end)
	{
		y = y_start;
		while (y < y_end)
		{
			if (x > 0 && x < S_WIDTH && y > 0 && y < S_HEIGHT)
				my_pixel_put(img, x, y, COLOR_DARK_GRAY);
			y+=2;
		}
		x+=2;
	}
}

void	ft_player_render(t_player *p)
{
	ft_draw_tile(p->img, 10 * MINIMAP_TILE, (S_HEIGHT * 5 / 6), 5, COLOR_BLUE);
}

void	ft_countouring_render(t_player *p)
{
	int	thickness;

	thickness = 0;
	// haut
	while (thickness < 5)
	{
		ft_draw_vertical_line(thickness, (S_HEIGHT * 5 / 6) - 10 * MINIMAP_TILE,
			(S_HEIGHT * 5 / 6) + 10 * MINIMAP_TILE, p->img,
			p->data->textures->ceiling_col);
		thickness++;
	}
	thickness = 0;
	// bas
	while (thickness < 5)
	{
		ft_draw_vertical_line(20 * MINIMAP_TILE + thickness, (S_HEIGHT * 5 / 6)
			- 10 * MINIMAP_TILE, (S_HEIGHT * 5 / 6) + 10 * MINIMAP_TILE
			+ thickness, p->img, p->data->textures->ceiling_col);
		thickness++;
	}
	thickness = 0;
	// droite
	while (thickness < 5)
	{
		ft_draw_horizontal_line((S_HEIGHT * 5 / 6) - 10 * MINIMAP_TILE
			+ thickness, 0, 20 * MINIMAP_TILE, p->img,
			p->data->textures->ceiling_col);
		thickness++;
	}
	thickness = 0;
	// gauche
	while (thickness < 5)
	{
		ft_draw_horizontal_line((S_HEIGHT * 5 / 6) + 10 * MINIMAP_TILE
			+ thickness, 0, 20 * MINIMAP_TILE + thickness, p->img,
			p->data->textures->ceiling_col);
		thickness++;
	}
}

 