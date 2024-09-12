/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:34:01 by melmarti          #+#    #+#             */
/*   Updated: 2024/09/12 17:41:15 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <string.h>

char	**allocate_map(int rows, int cols)
{
	char	**map;
	int		i;

	map = malloc(sizeof(char *) * rows);
	if (!map)
		return (NULL);
	for (i = 0; i < rows; i++)
		map[i] = malloc(sizeof(char) * (cols + 1));
	strcpy(map[0], "111111");
	strcpy(map[1], "101111");
	strcpy(map[2], "101111");
	strcpy(map[3], "101001");
	strcpy(map[4], "101001");
	strcpy(map[5], "101011");
	strcpy(map[6], "100011");
	strcpy(map[7], "111111");
	map[8] = NULL;
	return (map);
}

void	ft_map_render(t_player *p, char **map)
{
	double	y;
	double	x;
	int		tile_size;
	int		index_x;
	int		index_y;

	tile_size = ft_resize_tiles(map);
	index_y = 0;
	y = (S_HEIGHT / 2) - (ft_count_lines(map) * tile_size) / 2;
	while (index_y < ft_count_lines(map))
	{
		x = (S_WIDTH / 2) - (ft_count_columns(map) * tile_size) / 2;
		index_x = 0;
		while (index_x < ft_count_columns(map) && map[index_y][index_x])
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

void	ft_cub_render(t_player *p)
{
	t_image	*img;
	int		y;
	int		x;
	int		start_x;
	int		start_y;
	char	**map;

	map = allocate_map(8, 6);
	img = p->img;
	ft_clear_image(img, 0x00000000);
	x = p->p_x;
	y = p->p_y;
	start_x = p->p_x - (ft_resize_tiles(map) / 2);
	start_y = p->p_y - (ft_resize_tiles(map) / 2);
	x = start_x;
	ft_map_render(p, map);
	while (x < start_x + (ft_resize_tiles(map) / 2))
	{
		y = start_y;
		while (y < start_y + (ft_resize_tiles(map) / 2))
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
	p.p_x = (S_WIDTH / 2) - (TILE_SIZE / 2);
	p.p_y = (S_HEIGHT / 2) - (TILE_SIZE / 2);
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
