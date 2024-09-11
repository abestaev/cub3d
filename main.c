/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:34:01 by melmarti          #+#    #+#             */
/*   Updated: 2024/09/11 17:47:35 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	ft_cub_render(t_player *p)
{
	t_image	*img;
	int		y;
	int		x;
	int		start_x;
	int		start_y;

	img = p->img;
	ft_clear_image(img, 0x00000000);
	x = p->p_x;
	y = p->p_y;
	start_x = p->p_x - TILE_SIZE / 2;
	start_y = p->p_y - TILE_SIZE / 2;
	x = start_x;
	while (x < start_x + TILE_SIZE)
	{
		y = start_y;
		while (y < start_y + TILE_SIZE)
		{
			my_pixel_put(img, x, y, 0x00FF0000);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(img->mlx, img->win_ptr, img->img, 0, 0);
}

void	ft_mlx_init(void)
{
	t_player	p;
	t_image		img;

	img.mlx = mlx_init();
	img.win_ptr = mlx_new_window(img.mlx, S_WIDTH, S_HEIGHT, "Cub3D");
	img.img = mlx_new_image(img.mlx, S_WIDTH, S_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	p.img = &img;
	p.p_x = S_WIDTH / 2;
	p.p_y = S_HEIGHT / 2;
	ft_cub_render(&p);
	mlx_hook(img.win_ptr, KeyPress, KeyPressMask, ft_handle_hook, &p);
	mlx_put_image_to_window(img.mlx, img.win_ptr, img.img, 0, 0);
	mlx_loop(img.mlx);
}

int	main(int argc, char **argv)
{
	t_data	data;

	(void)argv;
	(void)argc;
	(void)data;
	// if (parsing(argc, argv, &data.textures))
	// 	return (1);
	ft_mlx_init();
	return (0);
}
