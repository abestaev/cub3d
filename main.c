/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:34:01 by melmarti          #+#    #+#             */
/*   Updated: 2024/09/17 17:22:42 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <string.h>

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

	start_x = p->p_x - (ft_resize_tiles(map) / 4);
	start_y = p->p_y - (ft_resize_tiles(map) / 4);
	x = start_x;
	while (x < start_x + (ft_resize_tiles(map) / 2) && x >= 0 && x < S_WIDTH)
	{
		y = start_y;
		while (y < start_y + (ft_resize_tiles(map) / 2) && y >= 0
			&& y < S_HEIGHT)
		{
			my_pixel_put(p->img, x, y, 0x00FF0000);
			y++;
		}
		x++;
	}
	p->p_dir_x = p->p_x + S_WIDTH * cos(p->p_angl);
	// resize the coordinate 2 of the vector player
	p->p_dir_y = p->p_y + S_HEIGHT * sin(p->p_angl);
}

void	ft_cast_rays(t_player *p)
{
	int	x;
	int	y;
	int	i;

	x = p->p_angl - FOV / 2;
	y = p->p_angl - FOV / 2;
	i = 0;
	while (i < S_WIDTH)
	{
		ft_draw_line(p->p_x, p->p_y, x + p->p_dir_x, y + p->p_dir_y, p->img);
		x += p->p_angl + (FOV / S_WIDTH);
		y += p->p_angl + (FOV / S_WIDTH);
		i++;
	}
}

void	ft_refresh(t_player *p)
{
	ft_clear_image(p->img, 0x00000000);
	ft_map_render(p, p->map);
	ft_player_render(p, p->map);
	ft_cast_rays(p);
	// ft_draw_line(p->p_x, p->p_y, p->p_dir_x, p->p_dir_y, p->img);
	mlx_put_image_to_window(p->img->mlx, p->img->win_ptr, p->img->img, 0, 0);
}

void	ft_cub_render(t_player *p)
{
	ft_refresh(p);
	mlx_hook(p->img->win_ptr, KeyPress, KeyPressMask, ft_handle_hook, p);
	mlx_loop(p->img->mlx);
}

int	main(int argc, char **argv)
{
	t_player	*player;
	t_data		data;
	
	(void)argv;
	(void)argc;
	player = malloc(sizeof(t_player));
	if (parsing(argc, argv, &data.textures, &data))
		return (1);
	ft_player_init(player, &data);
	player->img = ft_mlx_init();
	ft_cub_render(player);
	free(player->img);
	free_parsing(&data.textures, &data);
	return (0);
}
