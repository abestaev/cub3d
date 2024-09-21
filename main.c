/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renard <renard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:34:01 by melmarti          #+#    #+#             */
/*   Updated: 2024/09/22 01:06:42 by renard           ###   ########.fr       */
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

double	ft_norm_deg_angl(double degrees)
{
	double	angl;

	angl = degrees * (PI / 180);
	return (angl);
}
double	ft_norm_radian_angl(double radian)
{
	double	angl;

	angl = radian * (180 / PI);
	return (angl);
}

double	ft_find_next_y_tile(double point, t_player *p)
{
	double	i;

	i = 0;
	while (i <= S_HEIGHT)
	{
		if (i >= point)
		{
			if (p->p_angl >= PI && p->p_angl <= 2 * PI)
				return (i - p->tile_size);
			return (i);
		}
		i += p->tile_size;
	}
	return (0);
}

double	ft_find_next_x_tile(double point, t_player *p)
{
	double	i;

	// trouver l'intersection sur les axes x
	i = 0;
	while (i <= S_WIDTH)
	{
		if (i >= point)
		{
			if (p->p_angl >= PI / 2 && p->p_angl <= 3 * PI / 2)
				return (i - p->tile_size);
			return (i);
		}
		i += p->tile_size;
	}
	return (0);
}

void	ft_draw_x(t_player *p)
{
	double	opp_side;
	double	adj;
	double	x_inter;

	if (p->p_angl > PI / 2 && p->p_angl < 3 * PI / 2)
	{
		x_inter = ft_find_next_x_tile(p->p_x, p);
		adj = fabs(x_inter - p->p_x);
		opp_side = tan(p->p_angl) * adj;
		ft_draw_line(p->p_x, p->p_y, x_inter, p->p_y - opp_side, p->img);
	}
	else
	{
		x_inter = ft_find_next_x_tile(p->p_x, p);
		adj = fabs(x_inter - p->p_x);
		opp_side = tan(p->p_angl) * adj;
		ft_draw_line(p->p_x, p->p_y, x_inter, p->p_y + opp_side, p->img);
	}
}

void	ft_draw_y(t_player *p)
{
	double	opp_side;
	double	adj;
	double	y_inter;

	if (p->p_angl > 0 && p->p_angl < PI && p->p_angl != PI /2)
	{
		y_inter = ft_find_next_y_tile(p->p_y, p);
		opp_side = fabs(y_inter - p->p_y);
		adj = opp_side / tan(p->p_angl);
		ft_draw_line(p->p_x, p->p_y, p->p_x + adj, y_inter, p->img);
	}
	if (p->p_angl > PI && p->p_angl < 2 * PI && p->p_angl != 3 * PI /2)
	{
		y_inter = ft_find_next_y_tile(p->p_y, p);
		opp_side = fabs(y_inter - p->p_y);
		adj = opp_side / tan(p->p_angl);
		ft_draw_line(p->p_x, p->p_y, p->p_x - adj, y_inter, p->img);
	}
}

void	ft_cast_rays(t_player *p)
{
	//double	opp_side;
	//double	adj;
	//double	y_inter;
	//double	x_inter;

	// int		i;
	// double	ray_angl;
	// double	ray_x;
	// double	ray_y;
	/// i = 0;
	// ray_angl = p->p_angl + (ft_norm_deg_angl(FOV) / 2);
	//ft_draw_x(p);
	//ft_draw_y(p);
	// while (i < S_WIDTH)
	// {
	// 	x_step = ft_find_next_x_tile(p->p_x, p);
	// 	if (((p->p_angl > PI / 4 && p->p_angl < 3 * PI / 4)) || ((p->p_angl > 5* PI / 4 && p->p_angl < 7 * PI / 4)))
	// 	{
	// 		y_step = ft_find_next_y_tile(p->p_y, p);
	// 		while (y_step > 0 && y_step < S_HEIGHT)
	// 		{
	// 			adj = fabs(x_step - p->p_y);
	// 			opp_side = tan(ray_angl) * adj;
	// 			if((p->p_x + opp_side < 0 || p->p_x + opp_side > S_WIDTH))
					// si le cote opp sort de l ecran
	// 				break ;
	// 			if (p->map[(int)(y_step / p->tile_size)][(int)((p->p_x+ opp_side) / p->tile_size)] == '1')
	// 				break ;
	// 			x_step = ft_find_next_y_tile(x_step, p);
	// 		}
	// 		// ft_draw_line(p->p_x, p->p_y, p->p_x + opp_side, y_step, p->img);
	// 		ray_angl += ft_norm_deg_angl(FOV) / S_WIDTH;
	// 	}
	// 	else
	// 	{
	// 		while (x_step > 0 && x_step < S_WIDTH)
	// 		{
	// 			adj = fabs(x_step - p->p_x);
	// 			opp_side = tan(ray_angl) * adj;
	// 			if((p->p_x + opp_side < 0 || p->p_x + opp_side > S_HEIGHT))
					// si le cote opp sort de l ecran
	// 				break ;
	// 			if (p->map[(int)((p->p_y + opp_side)/ p->tile_size)][(int)((x_step) / p->tile_size)] == '1')
	// 				break ;
	// 			x_step += p->tile_size;
	// 		}
	// 		// ft_draw_line(p->p_x, p->p_y, x_step, p->p_y + opp_side, p->img);
	// 		ray_angl -= ft_norm_deg_angl(FOV) / S_HEIGHT;
	// 	}
	// 	// ray_x = cos(ray_angl) * 1000 + p->p_dir_x;
	// 	// ray_y = sin(ray_angl) * 1000 + p->p_dir_y;
	// 	// ft_draw_line(p->p_x, p->p_y, ray_x, ray_y, p->img);
	// 	i++;
	// }
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
