/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:34:01 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/01 14:11:04 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_cast_ray(t_player *p)
{
	t_ray	*ray;
	int		x;
	double 	camera_x;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;

	ray = p->ray;
	x = 0;
	while (x < S_WIDTH)
	{
		camera_x = 2 * x / (double)S_WIDTH - 1;
		ray->dir_x = p->p_dir_x + p->plane_x * camera_x;
		ray->dir_y = p->p_dir_y + p->plane_y * camera_x;
		ray->delta_dist_x = fabs(1 / ray->dir_x);
		ray->delta_dist_y = fabs(1 / ray->dir_y);
		map_x = (int)p->p_x;
		map_y = (int)p->p_y;
		if (ray->dir_x < 0)
		{
			step_x = -1;
			ray->side_dist_x = (p->p_x - map_x) * ray->delta_dist_x;
		}
		else
		{
			step_x = 1;
			ray->side_dist_x = (map_x + 1.0 - p->p_x) * ray->delta_dist_x;
		}
		if (ray->dir_y < 0)
		{
			step_y = -1;
			ray->side_dist_y = (p->p_y - map_y) * ray->delta_dist_y;
		}
		else
		{
			step_y = 1;
			ray->side_dist_y = (map_y + 1.0 - p->p_y) * ray->delta_dist_y;
		}
		while (1)
		{
			if (ray->side_dist_x < ray->side_dist_y)
			{
				ray->side_dist_x += ray->delta_dist_x;
				map_x += step_x;
				ray->side = 0;
			}
			else
			{
				ray->side_dist_y += ray->delta_dist_y;
				map_y += step_y;
				ray->side = 1;
			}
			if (ft_inside_wall(p, map_x, map_y))
				break ;
		}
		ft_get_wall_size(p, x);
		x++;
	}
}

/* We will take the distance from the camera plane to avoid the fish eyes effect */
/* If we get the sizeonly throuht the coordinate of the player we'll have the distortion,
if we increment some points along the camera vectore the distance will always have good proportion according to the distance from the wall to the camera vector */

void	ft_get_wall_size(t_player *p, int x)
{
	int		wall_height;
	double	wall_dist;
	int	start;
	int	end;
	t_ray	*ray;
	
	ray = p->ray;
	if (ray->side == 0)
		wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	if(wall_dist == 0)
		wall_height = S_HEIGHT;
	else 
		wall_height = (int)(S_HEIGHT / wall_dist);
	start = -wall_height / 2 + S_HEIGHT / 2;
	if (start < 0)
		start = 0;
	end = wall_height / 2 + S_HEIGHT / 2;
	if (end >= S_HEIGHT)
		end = S_HEIGHT - 1;
	if (ray->side == 0)
		ray->wall_x = p->p_x + wall_dist * ray->dir_y;
	else
		ray->wall_x = p->p_x + wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
	if(ray->side == 1)
		ft_draw_vertical_line(x, start, end, p->img, COLOR_MAGENTA);
	else 
		ft_draw_vertical_line(x, start, end, p->img, COLOR_BLUE);
}

void	ft_refresh(t_player *p)
{
	ft_clear_image(p->img, COLOR_RED);
	ft_cast_ray(p);
	ft_minimap_render(p, p->map);
	// ft_player_render(p);
	mlx_put_image_to_window(p->img->mlx, p->img->win_ptr, p->img->img, 0, 0);
}

int	ft_escape(t_player *p)
{
	mlx_destroy_window(p->img->mlx, p->img->win_ptr);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_player	*p;
	t_data		data;

	p = malloc(sizeof(t_player));
	if(!p)
		return (-1);
	data.textures.p = p;
	if (parsing(argc, argv, &data.textures, &data))
		return (1);
	ft_player_init(p, &data);
	p->img = ft_mlx_init();
	ft_cub_render(p);
	free(p->img);
	free(p);
	free_parsing(&data.textures, &data);
	return (0);
}
