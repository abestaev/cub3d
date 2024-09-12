/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:34:01 by melmarti          #+#    #+#             */
/*   Updated: 2024/09/12 13:36:42 by melmarti         ###   ########.fr       */
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

int	ft_count_columns(char map[3][3])
{
	int	i;

	i = 0;
	while (map[0][i])
		i++;
	return (i);
}

void	ft_map_render(t_player *p)
{
	char	map[4][3] = {{'1', '1', '1'}, {'1', '0', '1'}, {'1', '0', '1'}, {'1', '1', '1'}};
	int		y;
	int		x;
	int		tile_size;
	int		index_x;
	int		index_y;
	int		columns;

	index_x = 0;
	index_y = 0;
	columns = ft_count_columns(map);
	tile_size = S_WIDTH / columns;
	y = 0;
	while (y < S_HEIGHT && index_y < columns)
	{
		x = 0;
		index_x = 0;
		while (x < S_WIDTH && map[index_y][index_x])
		{
			if (map[index_y][index_x] == '1')
				ft_draw_tile(p->img, x, y, tile_size, 0x00FFFFFF);
			else if (map[index_y][index_x] == '0')
				ft_draw_tile(p->img, x, y, tile_size, 0x00000000);
			x += tile_size;
			index_x++;
		}
		y += tile_size;
		index_y++;
	}
	mlx_put_image_to_window(p->img->mlx, p->img->win_ptr, p->img->img, 0, 0);
}


// // char	map[5][5] = {{'1', '1', '1', '1', '1'}, {'1', '0', '0', '0', '1'},
// // 		{'1', '0', '0', '0', '1'}, {'1', '0', '0', '0', '1'}, {'1', '1',
// // 		'1', '1', '1'}};
// int		y;
// int		x;
// int		tile_size;

// tile_size =  TILE_SIZE/ 5 ;
// x = 0;
// while (x < S_HEIGHT)
// {
// 	y = 0;
// 	while (y < S_WIDTH)
// 	{
// 		my_pixel_put(p->img->img, x, y, 0x0000000F);
// 		// y += tile_size;
// 		y++;
// 	}
// 	x++;
// }

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
	ft_map_render(p);
	while (x < start_x + TILE_SIZE / 5)
	{
		y = start_y;
		while (y < start_y + TILE_SIZE / 5)
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
