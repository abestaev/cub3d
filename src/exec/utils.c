/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:07:23 by melmarti          #+#    #+#             */
/*   Updated: 2024/09/30 02:20:16 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	ft_dist(double x1, double y1, double x2, double y2)
{
	return (pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

int	ft_inside_wall(t_player *p, int x, int y)
{
	if ((x > 0 && x < S_WIDTH) || ((y > 0 || y < S_HEIGHT)
			&& ft_strlen(p->map[y])))
	{
		if (p->map[y][x] == '1')
			return (1);
	}
	return (0);
}

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
	int	len;

	i = 0;
	len = ft_strlen(map[0]);
	while (map[i])
	{
		i++;
		if (ft_strlen(map[i]) > (size_t)len)
			len = ft_strlen(map[i]);
	}
	return (len - 1);
}

double	ft_divide(double i, double j)
{
	return (i / j);
}

double	ft_get_tile_size(char **map)
{
	int	col;

	if (ft_divide(ft_count_columns(map),
			ft_count_lines(map)) >= ft_divide(S_WIDTH, S_HEIGHT))
	{
		col = ft_count_columns(map);
		return (S_WIDTH / col);
	}
	else
	{
		col = ft_count_lines(map);
		return (S_HEIGHT / col);
	}
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

/* optimize calcul to work directly with the memory where the pixels are store */
void ft_clear_image(t_image *img, unsigned int color)
{
    int total_pixels = S_WIDTH * S_HEIGHT;
    char *dst = img->addr;
    int i;

    for (i = 0; i < total_pixels; i++)
    {
        unsigned int *pixel = (unsigned int *)(dst + i * (img->bits_per_pixel / 8));
        *pixel = color;
    }
}

int get_col(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a << 0);	
}

void	ft_draw_vertical_line(int x_val, int start, int end, t_image *img,
		long color)
{
	int	y;

	y = start;
	if (start < 0)
		start = 0;
	if (end >= S_HEIGHT)
		end = S_HEIGHT - 1;
	while (y <= end)
	{
		my_pixel_put(img, x_val, y, color);
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
		if (y_end >= y_start)
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
		while (y <= y_end)
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