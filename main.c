/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:34:01 by melmarti          #+#    #+#             */
/*   Updated: 2024/09/19 16:48:11 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <string.h>

void	ft_map_render(t_player *p, char **map)
{
	double	y;
	double	x;
	int		index_x;
	int		index_y;

	index_y = 0;
	y = 0;
	while (index_y < ft_count_lines(map))
	{
		index_x = 0;
		x = 0;
		while (index_x < ft_count_columns(map) && map[index_y][index_x])
		{
			if (map[index_y][index_x] == '1')
				ft_draw_tile(p->img, x, y, p->tile_size, 0xEF92EE);
			else if (map[index_y][index_x] == '0')
				ft_draw_tile(p->img, x, y, p->tile_size, 0x00000000);
			x += p->tile_size;
			index_x++;
		}
		y += p->tile_size;
		index_y++;
	}
}

void	ft_player_render(t_player *p)
{
	int	start_x;
	int	start_y;

	start_x = p->p_x - (p->tile_size / 16);
	start_y = p->p_y - (p->tile_size / 16);
	ft_draw_tile(p->img, start_x, start_y, p->tile_size / 8, 0x00FF0000);
	p->plr_offset = p->tile_size / 8 / 2;
	// resize the coordinate 2 of the vector player
	p->p_dir_x = p->p_x + S_WIDTH * cos(p->p_angl);
	p->p_dir_y = p->p_y + S_HEIGHT * sin(p->p_angl);
}

double	ft_norm_angl(double degrees)
{
	double	angl;

	angl = degrees * (PI / 180);
	return (angl);
}
double	ft_find_next_x_tile(double point, t_player *p)
{
	int	i;

	i = 0;
	while (i <= S_WIDTH)
	{
		if (i > point)
		{
			if (p->p_angl > PI && p->p_angl < PI * 2)
				return (i - p->tile_size);
			return (i);
		}
		i += p->tile_size;
	}
	return (0);
}

double	ft_find_next_y_tile(double point, t_player *p)
{
	int	i;

	// trouver l'intersection sur les axes x
	i = 0;
	// if (p->p_angl > PI && p->p_angl < PI * 2)
	// // If my player is watching the south,
	// // I want to find the next tile after him
	// {
	while (i <= S_HEIGHT)
	{
		if (i > point)
		{
			if (p->p_angl > PI / 2 && p->p_angl < 3 * PI / 2)
				return (i - p->tile_size);
			return (i);
		}
		i += p->tile_size;
	}
	return (0);
	// }
	// else
	// 	while (i <= S_HEIGHT) // If my player is watching the north,
	// 	// I want to find the next tile before him
	// 	{printf("p_y : %f\n", p->p_y);
	// 		if (i > p->p_y)
	// 			return (i);
	// 		i += ft_get_tile_size(p->map);
	// 	}
}
void	ft_cast_rays(t_player *p)
{
	int		i;
	int		opp_side;
	int		adj;
	double	ray_angl;
	double	y_step;
	double	x_step;

	i = 0;
	ray_angl = p->p_angl - (ft_norm_angl(FOV) / 2);
	ft_draw_line(p->p_x, p->p_y, p->p_dir_x, p->p_dir_y, p->img);
	// exit(0);
	while (i < S_WIDTH)
	{
		if ((ray_angl > 0 && ray_angl < PI) || (ray_angl > PI && ray_angl < PI
				* 2))
		{
			y_step = ft_find_next_x_tile(p->p_x, p); //find the first perpendicular intersection
			while (y_step < S_HEIGHT && y_step > 0)
			{
				adj = fabs(y_step - p->p_y);
				opp_side = tan(ray_angl) * adj;
				y_step += p->tile_size;
				// printf("CASE = %c\n\n", p->map[(int)( ( p->p_y
				// + adj)/ ft_get_tile_size(p->map))][(int)((p->p_x
				// + opp_side) / ft_get_tile_size(p->map))]);
				if (p->map[(int)((p->p_y + adj) / p->tile_size)][(int)((p->p_x
							+ opp_side) / p->tile_size)] == '1')
					break ;
			}
			ft_draw_line(p->p_x, p->p_y, p->p_x + opp_side, p->p_y + adj,
				p->img);
		}
		else
		{
			x_step = ft_find_next_y_tile(p->p_y, p);
			while (x_step < S_WIDTH && x_step > 0)
			{
				adj = fabs(x_step - p->p_x);
				opp_side = tan(ray_angl) * adj;
				x_step += p->tile_size;
				// printf("CASE = %c\n\n", p->map[(int)( ( p->p_y
				// + adj)/ ft_get_tile_size(p->map))][(int)((p->p_x
				// + opp_side) / ft_get_tile_size(p->map))]);
				if (p->map[(int)((p->p_y + adj) / p->tile_size)][(int)((p->p_x
							+ opp_side) / p->tile_size)] == '1')
					break ;
			}
			ft_draw_line(p->p_x, p->p_y, p->p_x + adj, p->p_y + opp_side,
				p->img);
		}
		ray_angl -= ft_norm_angl(FOV) / S_WIDTH;
		i++;
	}
}

void	ft_refresh(t_player *p)
{
	ft_clear_image(p->img, 0x00000000);
	ft_map_render(p, p->map);
	ft_player_render(p);
	ft_cast_rays(p);
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
