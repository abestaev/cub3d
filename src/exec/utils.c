/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:07:23 by melmarti          #+#    #+#             */
/*   Updated: 2024/09/12 13:37:59 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

// int	*ft_exit(void *param)
// {
// 	t_image *img;

// 	img = (t_image *)img;
// 	mlx_destroy_image(img->win_ptr, img->img);
// 	mlx_destroy_window(img->win_ptr, img->img);
// 	mlx_loop_end(img->win_ptr);
// 	return (NULL);
// }