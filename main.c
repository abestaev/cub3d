/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:34:01 by melmarti          #+#    #+#             */
/*   Updated: 2024/09/23 16:17:24 by melmarti         ###   ########.fr       */
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

// double	ft_find_vert_tile(double point, t_player *p)
// {
// 	double	i;

// 	i = 0;
// 	while (i <= S_HEIGHT)
// 	{
// 		if (i >= point)
// 		{
// 			if (p->p_angl >= ft_norm_deg_angl(90)
// 				&& p->p_angl <= ft_norm_deg_angl(270))
// 				return (i - p->tile_size);
// 			return (i);
// 		}
// 		i += p->tile_size;
// 	}
// 	return (0);
// }

// double	ft_find_hor_tile(double point, t_player *p)
// {
// 	double	i;

// 	// trouver l'intersection sur les axes x
// 	i = 0;
// 	while (i <= S_WIDTH)
// 	{
// 		if (i >= point)
// 		{
// 			if (p->p_angl >= ft_norm_deg_angl(180)
// 				&& p->p_angl <= ft_norm_deg_angl(360))
// 				return (i - p->tile_size);
// 			return (i);
// 		}
// 		i += p->tile_size;
// 	}
// 	return (0);
// }

// void	ft_horizontal_inter(t_player *p)
// {
// 	double	opp_side;
// 	double	adj;
// 	double	y_step;

// 	if (ft_south(p))
// 	{
// 		y_step = ft_find_hor_tile(p->p_x, p);
// 		printf("south %f\n", y_step);
// 		printf("angl player %f\n", ft_norm_radian_angl(p->p_angl));
// 		ft_draw_line(p->p_x, p->p_y, p->p_dir_x, p->p_dir_y, p->img);
// 		adj = fabs(y_step + p->p_x);
// 		opp_side = tan(p->p_angl) * adj;
// 		printf("coord x = %f, coord y = %f\n", p->p_x + opp_side, y_step);
// 		ft_draw_line(p->p_x, p->p_y, p->p_x + opp_side, y_step, p->img);
// 	}
// 	else if (ft_north(p))
// 	{
// 		y_step = ft_find_hor_tile(p->p_x, p);
// 		printf("north %f\n", y_step);
// 		printf("angl player %f\n", ft_norm_radian_angl(p->p_angl));
// 		ft_draw_line(p->p_x, p->p_y, p->p_dir_x, p->p_dir_y, p->img);
// 		adj = fabs(p->p_x - y_step);
// 		opp_side = tan(p->p_angl) * adj;
// 		if (ft_norm_deg_angl(p->p_angl) > 270)
// 		{
// 		// printf("coord x = %f, coord y = %f\n", p->p_x + opp_side, y_step);

// 			ft_draw_line(p->p_x, p->p_y, p->p_x + opp_side + p->p_dir_x, y_step,
				// p->img);
// 		}
// 		else
// 			ft_draw_line(p->p_x, p->p_y, p->p_x + opp_side + p->p_dir_x, y_step,
				// p->img);
// 	}
// }

// void	ft_vertical_inter(t_player *p)
// {
// 	double	opp_side;
// 	double	adj;
// 	double	x_step;

// 	if (ft_ouest(p))
// 	{
// 		x_step = ft_find_vert_tile(p->p_y, p);
// 		printf("ouest %f\n", x_step);
// 		opp_side = fabs(x_step - p->p_y);
// 		adj = opp_side * tan(p->p_angl);
// 		ft_draw_line(p->p_x, p->p_y, p->p_x + adj, x_step, p->img);
// 	}
// 	else if (ft_est(p))
// 	{
// 		x_step = ft_find_vert_tile(p->p_y, p);
// 		printf("est %f\n", x_step);
// 		opp_side = fabs(x_step - p->p_y);
// 		adj = opp_side * tan(p->p_angl);
// 		ft_draw_line(p->p_x, p->p_y, p->p_x - adj, x_step, p->img);
// 	}
// }

void	ft_cast_ray(t_player *p)
{
	int		i;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double delta_dist_x;
	double delta_dist_y;
	int map_x;
	int map_y;
	int step_x;
	int step_y;
	double side_dist_x;
	double side_dist_y;
	
	i = 0;
	while (i < S_WIDTH)
	{
		camera_x = 2 * i / (double)S_WIDTH - 1;
		ray_dir_x = p->p_dir_x + p->p_x * camera_x;
		ray_dir_y = p->p_dir_y + p->p_y * camera_x;
		delta_dist_x = fabs(1 / ray_dir_x);
		delta_dist_y = fabs(1 / ray_dir_y);
		map_x = (int)p->p_x;
		map_y = (int)p->p_y;
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (p->p_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - p->p_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (p->p_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - p->p_y) * delta_dist_y;
		}
		while (1)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
			}
			if (p->map[(int)(map_y / p->tile_size)][(int)(map_x / p->tile_size)] == '1')
				break;
		}
		ft_draw_line(p->p_x, p->p_y, map_x, map_y, p->img);
		i++;
	}
}

void	ft_refresh(t_player *p)
{
	ft_clear_image(p->img, 0x00000000);
	ft_map_render(p, p->map);
	ft_player_render(p);
	ft_cast_ray(p);
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
