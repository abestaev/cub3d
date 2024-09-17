/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:07:23 by melmarti          #+#    #+#             */
/*   Updated: 2024/09/17 14:42:32 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_count_lines(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	ft_count_columns(char **map)
{
	int	i;

	i = 0;
	while (map[0][i])
		i++;
	return (i);
}

int	ft_resize_tiles(char **map)
{
	int	col;

	if (ft_count_columns(map) > ft_count_lines(map))
		col = ft_count_columns(map);
	else
		col = ft_count_lines(map);
	if (S_WIDTH < S_HEIGHT)
		return (S_WIDTH / col);
	else
		return (S_HEIGHT / col);
}

void	ft_draw_tile(t_image *img, int start_x, int start_y, int size,
		int color)
{
	int	x;
	int	y;

	x = start_x;
	while (x < start_x - 1 + size)
	{
		y = start_y;
		while (y < start_y - 1 + size)
		{
			if (x >= 0 && x < S_WIDTH && y >= 0 && y < S_HEIGHT)
				my_pixel_put(img, x, y, color);
			y++;
		}
		x++;
	}
}
void	ft_clear_image(t_image *img, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < S_HEIGHT)
	{
		x = 0;
		while (x < S_WIDTH)
		{
			my_pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	ft_draw_line(int x_start, int y_start, int x_end, int y_end,
		t_image *img)
{
	int	delta_x;
	int	delta_y;
	int	d;
	int	temp;
	int	y;
	int	x;
	int	y_inc;
	int	x_inc;

	// Debugging information
	printf("x_start %d, y_start %d, x_end %d, y_end %d\n", x_start, y_start,
		x_end, y_end);
	delta_x = abs(x_end - x_start);
	delta_y = abs(y_end - y_start);
	// Si l'axe X domine
	if (delta_x > delta_y)
	{
		// Inverser les points si nécessaire
		if (x_start > x_end)
		{
			temp = x_start;
			x_start = x_end;
			x_end = temp;
			temp = y_start;
			y_start = y_end;
			y_end = temp;
		}
		y_inc = -1;
		if(y_end >= y_start)
			y_inc = 1;
		y = y_start;
		x = x_start;
		d = 2 * delta_y - delta_x;
		while (x <= x_end)
		{
			if (x >= 0 && x < S_WIDTH && y >= 0 && y < S_HEIGHT)
				my_pixel_put(img, x, y, 0x00FF0000);
			if (d > 0)
			{
				y += y_inc;
				d -= 2 * delta_x;
			}
			d += 2 * delta_y;
			x++;
		}
	}
	// Si l'axe Y domine
	else
	{
		// Inverser les points si nécessaire
		if (y_start > y_end)
		{
			temp = x_start;
			x_start = x_end;
			x_end = temp;
			temp = y_start;
			y_start = y_end;
			y_end = temp;
		}
		x_inc = -1;
		if (x_end >= x_start)
			x_inc = 1;
		x = x_start;
		y = y_start;
		d = 2 * delta_x - delta_y;
		while(y <= y_end)
		{
			if (x >= 0 && x < S_WIDTH && y >= 0 && y < S_HEIGHT)
				my_pixel_put(img, x, y, 0x00FF0000);
			if (d > 0)
			{
				x += x_inc;
				d -= 2 * delta_y;
			}
			d += 2 * delta_x;
			y++;
		}
	}
}
// int	*ft_exit(void *param)
// {
// 	t_image *img;

// 	img = (t_image *)img;
// 	mlx_destroy_image(img->win_ptr, img->img);
// 	mlx_destroy_window(img->win_ptr, img->img);
// 	mlx_loop_end(img->win_ptr);
// 	return (NULL);
// }