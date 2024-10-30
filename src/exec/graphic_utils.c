/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:16:09 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/30 14:15:22 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_vertical_line(int x_val, int start, int end, t_image *img)
{
	int	y;

	y = start;
	if (start < 0)
		start = 0;
	if (end >= S_HEIGHT)
		end = S_HEIGHT - 1;
	while (y <= end)
	{
		my_pixel_put(img, x_val, y, COLOR_BLACK);
		y++;
	}
}

void	ft_draw_horizontal_line(int y_val, int start, int end, t_image *img)
{
	int	x;

	x = start;
	if (start < 0)
		start = 0;
	if (end >= S_WIDTH)
		end = S_WIDTH - 1;
	while (x <= end)
	{
		my_pixel_put(img, x, y_val, COLOR_BLACK);
		x++;
	}
}

void	my_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	ft_calc_dark(int color, double factor)
{
	return (((int)((color >> 16 & 0xFF) * factor) << 16)
		+ ((int)((color >> 8 & 0xFF) * factor) << 8) + (int)((color & 0xFF)
		* factor));
}

int	get_hexa_color(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}
