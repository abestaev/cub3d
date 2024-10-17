/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render_01.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:21:24 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/17 16:20:16 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_player_render(t_player *p)
{
	ft_draw_tile(p->img, p->mini.nb_tile * p->mini.tile_size, p->mini.pos.y, 5,
		COLOR_BLUE);
}

void	ft_draw_mini_background(t_image *img, int x_start, int x_end,
		int y_start, int y_end)
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
			y += 2;
		}
		x += 2;
	}
}

static void	ft_countouring_render_01(t_player *p)
{
	int	thickness;

	thickness = 0;
	// droite
	while (thickness < 5)
	{
		ft_draw_horizontal_line((S_HEIGHT * 5 / 6) - 10 * p->mini.tile_size
			+ thickness, 0, 20 * p->mini.tile_size, p->img,
			p->data->textures->ceiling_col);
		thickness++;
	}
	thickness = 0;
	// gauche
	while (thickness < 5)
	{
		ft_draw_horizontal_line((S_HEIGHT * 5 / 6) + 10 * p->mini.tile_size
			+ thickness, 0, 20 * p->mini.tile_size + thickness, p->img,
			p->data->textures->ceiling_col);
		thickness++;
	}
}

void	ft_countouring_render_00(t_player *p)
{
	int	thickness;

	thickness = 0;
	// haut
	while (thickness < 5)
	{
		ft_draw_vertical_line(thickness, (S_HEIGHT * 5 / 6) - 10
			* p->mini.tile_size, (S_HEIGHT * 5 / 6) + 10 * p->mini.tile_size,
			p->img, p->data->textures->ceiling_col);
		thickness++;
	}
	thickness = 0;
	// bas
	while (thickness < 5)
	{
		ft_draw_vertical_line(20 * p->mini.tile_size + thickness, (S_HEIGHT * 5
				/ 6) - 10 * p->mini.tile_size, (S_HEIGHT * 5 / 6) + 10
			* p->mini.tile_size + thickness, p->img,
			p->data->textures->ceiling_col);
		thickness++;
	}
	ft_countouring_render_01(p);
}
