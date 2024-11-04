/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render_01.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:21:24 by melmarti          #+#    #+#             */
/*   Updated: 2024/11/04 17:05:50 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_player_render(t_player *p)
{
	t_point	start;

	start.x = p->mini->nb_tile * p->mini->tile_size + S_WIDTH / 25;
	start.y = p->mini->pos.y;
	ft_draw_tile(p->img, start, 5, COLOR_BLUE);
}

void	ft_draw_tile(t_image *img, t_point start, int size, int color)
{
	int	x;
	int	y;

	x = start.x;
	while (x < (start.x - 1) + size && x < 20 * img->p->mini->tile_size
		+ S_WIDTH / 25)
	{
		y = start.y;
		while (y < (start.y - 1) + size && y < (S_HEIGHT * 5 / 6) + 10
			* img->p->mini->tile_size && start.y > S_HEIGHT * 5 / 6 - 10
			* img->p->mini->tile_size)
		{
			if (x > S_WIDTH / 25 && x < S_WIDTH && y > 0 && y < S_HEIGHT)
				my_pixel_put(img, x, y, color);
			y++;
		}
		x++;
	}
}

void	ft_draw_mini_background(t_image *img, t_point start, t_point end)
{
	double	x;
	double	y;

	x = start.x;
	while (x < end.x)
	{
		y = start.y;
		while (y < end.y)
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
	while (thickness < 5)
	{
		ft_draw_horizontal_line((S_HEIGHT * 5 / 6) - 10 * p->mini->tile_size
			+ thickness, S_WIDTH / 25, 20 * p->mini->tile_size + S_WIDTH / 25,
			p->img);
		thickness++;
	}
	thickness = 0;
	while (thickness < 5)
	{
		ft_draw_horizontal_line((S_HEIGHT * 5 / 6) + 10 * p->mini->tile_size
			+ thickness, S_WIDTH / 25, 20 * p->mini->tile_size + S_WIDTH / 25
			+ thickness, p->img);
		thickness++;
	}
}

void	ft_countouring_render_00(t_player *p)
{
	int	thickness;

	thickness = S_WIDTH / 25;
	while (thickness < 5 + S_WIDTH / 25)
	{
		ft_draw_vertical_line(thickness, (S_HEIGHT * 5 / 6) - 10
			* p->mini->tile_size, (S_HEIGHT * 5 / 6) + 10 * p->mini->tile_size,
			p->img);
		thickness++;
	}
	thickness = S_WIDTH / 25;
	while (thickness < 5 + S_WIDTH / 25)
	{
		ft_draw_vertical_line(20 * p->mini->tile_size + thickness, (S_HEIGHT * 5
				/ 6) - 10 * p->mini->tile_size, (S_HEIGHT * 5 / 6) + 10
			* p->mini->tile_size + 4, p->img);
		thickness++;
	}
	ft_countouring_render_01(p);
}
