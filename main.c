/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renard <renard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:34:01 by melmarti          #+#    #+#             */
/*   Updated: 2024/09/16 00:25:32 by renard           ###   ########.fr       */
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
				ft_draw_tile(p->img, x, y, tile_size, 0xEF92EE);
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

void	ft_player_render(t_player *p, char **map)
{
	t_image	*img;
	int		y;
	int		x;
	int		start_x;
	int		start_y;

	img = p->img;
	start_x = p->p_x - (ft_resize_tiles(map) / 2);
	start_y = p->p_y - (ft_resize_tiles(map) / 2);
	x = start_x;
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

void	ft_cub_render(t_player *p)
{
	char	**map;

	map = allocate_map(8, 6);
	ft_clear_image(p->img, 0x00000000);
	ft_map_render(p, map);
	ft_clear_image(p->img, 0x00000000);
	ft_player_render(p, map);
	ft_clear_image(p->img, 0x00000000);
	// ft_clear_image(p->img, 0x00000000);
	// visualize the player angle
}

void	ft_draw_line(int x_start, int y_start, int x_end, int y_end,
		t_image img)
{
	int	delta_x;
	int	delta_y;
	int	d;
	int	temp;
	int	y;
	int	x;
	int	y_inc;

	delta_x = x_end - x_start;
	delta_y = y_end - y_start;
	d = 2 * delta_y - delta_x;
	if (abs(delta_x) > abs(delta_y))
	{
		if (x_start > x_end)
		{
			temp = x_start;
			x_start = x_end;
			x_end = temp;
			delta_x *= -1;
			delta_y *= -1;
		}
	}
	y_inc = 1;
	if (delta_y < 0)
	{
		y_inc = -1;
		delta_y *= -1;
	}
	y = y_start;
	x = x_start;
	while (x < x_end)
	{
		if (x >= 0 && x < S_WIDTH && y >= 0 && y < S_HEIGHT)
			my_pixel_put(img.img, x, y, 0x00FF0000);
		if (d < 0)
		{
			d += 2 * delta_y;
		}
		else 
		{
			d += 2 * (delta_y - delta_x);
			y += y_inc;
		}
		x++;
	}
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
	img.p = &p;
	ft_draw_line(20, 20, 20, 20, img);
	mlx_put_image_to_window(img.mlx, img.win_ptr, img.img, 0, 0);
	mlx_loop(img.mlx);
	exit(0);
	p.p_x = (S_WIDTH / 2);
	p.p_y = (S_HEIGHT / 2);
	p.p_angl = PI / 2;
	p.p_dir_x = cos(p.p_angl);
	p.p_dir_y = sin(p.p_angl);
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
