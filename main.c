/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:34:01 by melmarti          #+#    #+#             */
/*   Updated: 2024/09/16 19:20:35 by melmarti         ###   ########.fr       */
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
}

void	ft_player_render(t_player *p, char **map)
{
	int	y;
	int	x;
	int	start_x;
	int	start_y;

	start_x = p->p_x - (ft_resize_tiles(map) / 2);
	start_y = p->p_y - (ft_resize_tiles(map) / 2);
	x = start_x;
	while (x < start_x + (ft_resize_tiles(map) / 2))
	{
		y = start_y;
		while (y < start_y + (ft_resize_tiles(map) / 2))
		{
			my_pixel_put(p->img, x, y, 0x00FF0000);
			y++;
		}
		x++;
	}
}

void	ft_refresh(t_player *p)
{
	// ft_clear_image(p->img, 0x00000000);
	// ft_map_render(p, p->map);
	ft_player_render(p, p->map);
	ft_draw_line(p->p_x, p->p_y, 700, 200, p->img);
	mlx_put_image_to_window(p->img->mlx, p->img->win_ptr, p->img->img, 0, 0);
}

void	ft_cub_render(t_player *p)
{
	//mlx_put_image_to_window(p->img->mlx, p->img->win_ptr, p->img->img, 0, 0);
	ft_refresh(p);
	mlx_hook(p->img->win_ptr, KeyPress, KeyPressMask, ft_handle_hook, p);
	mlx_loop(p->img->mlx);
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

	//printf("x_start %d, y_start %d, x_end %d, y_end %d\n", x_start, y_start,
	//	x_end, y_end);
	delta_x = x_end - x_start;
	delta_y = y_end - y_start;
	if (abs(delta_x) > abs(delta_y))
	{
		if (x_start > x_end)
		{
			temp = x_start;
			x_start = x_end;
			x_end = temp;
			temp = y_start;
			y_start = y_end;
			y_end = temp;
			delta_x *= -1;
			delta_y *= -1;
		}
		y_inc = 1;
		if (delta_y < 0)
		{
			y_inc = -1;
			delta_y *= -1;
		}
		y = y_start;
		d = 2 * delta_y - delta_x;
		x = x_start;
		while (x < x_end)
		{
			if (x >= 0 && x < S_WIDTH && y >= 0 && y < S_HEIGHT)
				my_pixel_put(img, x, y,
					0x00FF0000);
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
	else
	{
		if (y_start > y_end)
		{
			temp = x_end;
			x_end = x_start;
			x_start = temp;
			temp = y_start;
			y_start = y_end;
			y_end = temp;
			delta_x *= -1;
			delta_y *= -1;
		}
		x_inc = 1;
		if (delta_x < 0)
		{
			x_inc = -1;
			delta_x *= -1;
		}
		d = 2 * delta_x - delta_y;
		x = x_start;
		y = y_start;
		while (y < y_end)
		{
			if (x >= 0 && x < S_WIDTH && y >= 0 && y < S_HEIGHT)
				my_pixel_put(img, x, y,
					0x00FF0000);
			if (d < 0)
				d += 2 * delta_x;
			else
			{
				d += 2 * (delta_x - delta_y);
				x += x_inc;
			}
		}
	}
}

int	main(int argc, char **argv)
{
	t_player	*player;

	(void)argv;
	(void)argc;
	player = malloc(sizeof(t_player));
	player->map = allocate_map(8, 6);
	// if (parsing(argc, argv, &data.textures))
	// 	return (1);
	ft_player_init(player);
	player->img = ft_mlx_init();
	ft_cub_render(player);
	free(player->img);
	return (0);
}
