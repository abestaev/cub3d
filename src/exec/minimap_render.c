/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:21:24 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/16 17:57:22 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	get_mini_y_index_start(t_player *p, int nb_tile)
// {
// 	int	start_y;

// 	start_y = p->pos.y - nb_tile;
// 	if (start_y < 0)
// 		return (0);
// 	return (start_y);
// }

// int	get_mini_y_index_end(t_player *p, int nb_tile)
// {
// 	int	end_y;
// 	int	map_height;

// 	map_height = ft_count_lines(p->map);
// 	end_y = p->pos.y + nb_tile;
// 	if (end_y > map_height)
// 		return (map_height);
// 	return (end_y);
// }

// int	get_mini_x_index_start(t_player *p, int nb_tile)
// {
// 	int	start_x;

// 	start_x = p->pos.x - nb_tile;
// 	if (start_x < 0)
// 		return (0);
// 	return (start_x);
// }

// int	get_mini_x_index_end(t_player *p, int nb_tile)
// {
// 	int	end_x;
// 	int	map_width;

// 	map_width = ft_count_columns(p->map);
// 	end_x = p->pos.x + nb_tile;
// 	if (end_x > map_width)
// 		return (map_width);
// 	return (end_x);
// }
double	ft_get_mini_y_offset(t_player *p)
{
	return((S_HEIGHT * 1 / 10) - p->pos.y * MINIMAP_TILE + 2);
}

double	ft_get_mini_x_offset(t_player *p)
{
	return(10 * MINIMAP_TILE - p->pos.x * MINIMAP_TILE + 2);
}

void	ft_draw_map(t_player *p, char **map)
{
	int	index_x;
	int	index_y;
	int	x;
	int	y;

	y = ft_get_mini_y_offset(p);
	index_y = 0;
	while (index_y < ft_count_lines(map))
	{
		index_x = 0;
		x = ft_get_mini_x_offset(p);
		while (index_x < ft_count_columns(map))
		{
			if (map[index_y][index_x] == '1')
				ft_draw_tile(p->img, x, y, MINIMAP_TILE, COLOR_CYAN);
			x += MINIMAP_TILE;
			index_x++;
		}
		y += MINIMAP_TILE;
		index_y++;
	}
}

void	ft_minimap_render(t_player *p, char **map)
{
	// double	x;
	// int		index_x;
	// int		index_y;
	// int		start_x;
	// int		end_x;
	// int		start_y;
	// int		end_y;
	// double	y_offset;
	// double	x_offset;
(void)map;
	ft_draw_map(p, p->map);
	/* double	y;
	start_x = get_mini_x_index_start(p, 10);
	end_x = get_mini_x_index_end(p, 10);
	start_y = get_mini_y_index_start(p, 10);
	end_y = get_mini_y_index_end(p, 10);
	printf("start_x %d\n", start_x);
	printf("end_x %d\n", end_x);
	printf("start_y %d\n", start_y);
	printf("end_y %d\n", end_y);
	y_offset = (S_HEIGHT * 5 / 6) - 10 * MINIMAP_TILE;
	x_offset = 0;
	y = y_offset;
	index_y = start_y;
	while (index_y <= end_y && index_y < ft_count_lines(p->map))
	{
		index_x = start_x;
		x = x_offset;
		while (index_x <= end_x && index_x < ft_count_columns(p->map))
		{
			if (map[index_y][index_x] == '1')
				ft_draw_tile(p->img, x, y, MINIMAP_TILE, COLOR_CYAN);
			else
				ft_draw_alpha_tile(p->img, x, y, MINIMAP_TILE, COLOR_DARK_GRAY);
			x += MINIMAP_TILE;
			index_x++;
		}
		y += MINIMAP_TILE;
		index_y++;
	} */
}

void	ft_player_render(t_player *p)
{
	ft_draw_tile(p->img, 10 * MINIMAP_TILE, (S_HEIGHT * 1 / 10), 5,
		COLOR_BLUE);
}
void	ft_countouring_render(t_player *p)
{
	int	thickness;
	int	j;

	thickness = 0;
	j = 0;
	// haut
	while (thickness < 5)
	{
		ft_draw_vertical_line(thickness, (S_HEIGHT * 5 / 6) - 10 * MINIMAP_TILE,
			(S_HEIGHT * 5 / 6) + 10 * MINIMAP_TILE, p->img,
			p->data->textures->ceiling_col);
		thickness++;
	}
	thickness = 0;
	// bas
	while (thickness < 5)
	{
		ft_draw_vertical_line(20 * MINIMAP_TILE + thickness, (S_HEIGHT * 5 / 6)
			- 10 * MINIMAP_TILE, (S_HEIGHT * 5 / 6) + 10 * MINIMAP_TILE
			+ thickness, p->img, p->data->textures->ceiling_col);
		thickness++;
	}
	thickness = 0;
	// droite
	while (thickness < 5)
	{
		ft_draw_horizontal_line((S_HEIGHT * 5 / 6) - 10 * MINIMAP_TILE
			+ thickness, 0, 20 * MINIMAP_TILE, p->img,
			p->data->textures->ceiling_col);
		thickness++;
	}
	thickness = 0;
	// gauche
	while (thickness < 5)
	{
		ft_draw_horizontal_line((S_HEIGHT * 5 / 6) + 10 * MINIMAP_TILE
			+ thickness, 0, 20 * MINIMAP_TILE + thickness, p->img,
			p->data->textures->ceiling_col);
		thickness++;
	}
}
// int		i = 0;
// int		j = 0;

// while (i < 10)
// {
// 	ft_draw_vertical_line(p->mini->p_x - 7 * p->tile_size + i, p->mini->p_y - 7
// 		* p->tile_size, p->mini->p_y + 7 * p->tile_size, p->img, COLOR_BLUE);
// 	i++;
// }

// ft_draw_vertical_line(p->mini->p_x + 8 * p->tile_size, p->mini->p_y - 8
// 	* p->tile_size, p->mini->p_y + 8 * p->tile_size, p->img, COLOR_BLUE);
// ft_draw_horizontal_line(p->mini->p_y - 8 * p->tile_size, p->mini->p_x - 8
// 	* p->tile_size, p->mini->p_x + 8 * p->tile_size, p->img, COLOR_BLUE);
// ft_draw_horizontal_line(p->mini->p_y + 8 * p->tile_size, p->mini->p_x - 8
// 	* p->tile_size, p->mini->p_x + 8 * p->tile_size, p->img, COLOR_BLUE);
// ft_draw_vertical_line(p->mini->p_x - 8 * p->tile_size);

// ft_draw_tile(p->img, p->mini->p_x, p->mini->p_y, 20, COLOR_BLUE);
// }
