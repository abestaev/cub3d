/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:34:01 by melmarti          #+#    #+#             */
/*   Updated: 2024/09/11 11:58:18 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_mlx_init(void)
{
	void		*mlx;
	void		*mlx_win;
	t_player	p;
	t_image		data;
	int			start_x;
	int			start_y;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Cub3d");
	data.img = mlx_new_image(mlx, 1920, 1080);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
			&data.line_length, &data.endian);
	p.p_x = (1920 - TILE_SIZE) / 2;
	p.p_y = (1080 - TILE_SIZE) / 2;
	start_x = p.p_x + TILE_SIZE;
	start_y = p.p_y + TILE_SIZE;
    p.p_x = start_x;
	while (p.p_y < start_y)
	{
		p.p_x =  (1920 - TILE_SIZE) / 3;
		while (p.p_x < start_x)
		{
			my_pixel_put(&data, p.p_x, p.p_y, 0x000001);
			p.p_x++;
		}
		p.p_y++;
	}
	mlx_put_image_to_window(mlx, mlx_win, data.img, 0, 0);
	mlx_loop(mlx);
}

int	main(void)
{
	ft_mlx_init();
}
