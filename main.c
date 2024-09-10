/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:34:01 by melmarti          #+#    #+#             */
/*   Updated: 2024/09/10 18:44:04 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_mlx_init(void)
{
	void		*mlx;
	void		*mlx_win;
	t_player	p;
	t_data		data;
	int			i;
	int			start;
	int			end;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Cub3d");
	data.img = mlx_new_image(mlx, 1920, 1080);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
			&data.line_length, &data.endian);
	p.p_x = (1920 - TILE_SIZE) / 2;
	p.p_y = (1080 - TILE_SIZE) / 2;
	start = p.p_x + TILE_SIZE;
	end = p.p_y + TILE_SIZE;
	i = 0;
	while (p.p_y < end)
	{
		p.p_x = (1920 - TILE_SIZE) / 2;
		while (p.p_x < start)
		{
			if (p.p_x > 50)
				my_pixel_put(&data, p.p_x, p.p_y, 0xFFFFFFF1);
			else
				my_pixel_put(&data, p.p_x, p.p_y, 0xFF00009F);
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
