/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:07:23 by melmarti          #+#    #+#             */
/*   Updated: 2024/09/12 17:41:25 by melmarti         ###   ########.fr       */
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
	while (x < start_x + size)
	{
		y = start_y;
		while (y < start_y + size)
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
// int	*ft_exit(void *param)
// {
// 	t_image *img;

// 	img = (t_image *)img;
// 	mlx_destroy_image(img->win_ptr, img->img);
// 	mlx_destroy_window(img->win_ptr, img->img);
// 	mlx_loop_end(img->win_ptr);
// 	return (NULL);
// }