/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:34:01 by melmarti          #+#    #+#             */
/*   Updated: 2024/09/26 13:11:21 by melmarti         ###   ########.fr       */
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

void	ft_cast_ray(t_player *p)
{
	int		x;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;

	// ft_draw_line(p->p_x, p->p_y, p->p_dir_x, p->p_dir_y, p->img);
	x = 0;
	while (x < S_WIDTH)
	{
		camera_x = 2 * x / (double)S_WIDTH - 1;
		ray_dir_x = p->p_dir_x + p->plane_x * camera_x;
		ray_dir_y = p->p_dir_y + p->plane_y * camera_x;
		delta_dist_x = fabs(1 / ray_dir_x);
		delta_dist_y = fabs(1 / ray_dir_y);
		map_x = (int)p->p_x;
		map_y = (int)p->p_y;
		printf("player plane x = %f, player plane y %f\n",p->plane_x, p->plane_y);
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
			if (p->map[(int)(map_y / p->tile_size)][(int)(map_x
					/ p->tile_size)] == '1')
				break ;
		}
		ft_draw_line(p->p_x, p->p_y, map_x, map_y, p->img);
		x++;
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
