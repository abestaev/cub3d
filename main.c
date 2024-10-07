/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:34:01 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/07 16:00:17 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_get_color(t_player *p, int wall_height, int start, int map_x,
		int map_y, int x)
{
	(void)x;
	int	tex_x;
	int	step;
	int	pos;  
	int	tex_nb;
	int	*texture;
	int *text_map = malloc(sizeof(int) * 64 * 64);
	int y;

	tex_x = 0;
	// printf("p->map %d\n",p->map[map_x][map_y] - 1 );
	(void)map_x;
	(void)map_y;
	tex_nb = p->map[5][5] - 1;
	if ((p->ray->side == 0 && p->ray->dir_x < 0) || (p->ray->side == 1
			&& p->ray->dir_y > 0))
		tex_x = TEXTURE_SIZE - tex_x - 1;
	step = 1.0 * TEXTURE_SIZE / wall_height;
	pos = (start - S_HEIGHT / 2 + wall_height / 2) * step;
	texture = p->text_buff[tex_nb];
	for (y = start; y < start + wall_height; y++)
	{
		int tex_y = (int)pos & (TEXTURE_SIZE - 1);  // Get the y texture coordinate
		pos += step;  // Increment the texture position

		int color = texture[TEXTURE_SIZE * tex_y + tex_x];  // Get the texture color

		// Darken the color for y-sides
		if (p->ray->side == 1) color = (color >> 1) & 8355711;

		// Store the color in the text_map (1D array)
		if (y < TEXTURE_SIZE && tex_x < TEXTURE_SIZE) {
			text_map[TEXTURE_SIZE * tex_y + tex_x] = color;
		}
	}
	mlx_put_image_to_window(p->img->mlx, p->img->win_ptr, p->img->img,0,0 );
	free(text_map);

}
void	ft_cast_ray(t_player *p)
{
	t_ray	*ray;
	int		x;
	int		step_x;
	int		step_y;

	ray = p->ray;
	x = 0;
	while (x < S_WIDTH)
	{
		ft_init_ray(p, x);
		if (ray->dir_x < 0)
		{
			step_x = -1;
			ray->side_dist_x = (p->pos.x - ray->map_x) * ray->delta_dist_x;
		}
		else
		{
			step_x = 1;
			ray->side_dist_x = (ray->map_x + 1.0 - p->pos.x) * ray->delta_dist_x;
		}
		if (ray->dir_y < 0)
		{
			step_y = -1;
			ray->side_dist_y = (p->pos.y - ray->map_y) * ray->delta_dist_y;
		}
		else
		{
			step_y = 1;
			ray->side_dist_y = (ray->map_y + 1.0 - p->pos.y) * ray->delta_dist_y;
		}
		while (1)
		{
			if (ray->side_dist_x < ray->side_dist_y)
			{
				ray->side_dist_x += ray->delta_dist_x;
				ray->map_x += step_x;
				ray->side = 0;
			}
			else
			{
				ray->side_dist_y += ray->delta_dist_y;
				ray->map_y += step_y;
				ray->side = 1;
			}
			if (ft_inside_wall(p, ray->map_x, ray->map_y))
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
	int		start;
	int		end;
	t_ray	*ray;

	ray = p->ray;
	if (ray->side == 0)
		wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	if (wall_dist == 0)
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
		ray->wall_x = p->pos.x + wall_dist * ray->dir_y;
	else
		ray->wall_x = p->pos.x + wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
	if (ray->side == 1)
		ft_draw_vertical_line(x, start, end, p->img, COLOR_MAGENTA);
	else
		ft_draw_vertical_line(x, start, end, p->img, COLOR_BLUE);
	// ft_get_color(p, wall_height, start, map_x, map_y, x);
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
	if (!p)
		return (-1);
	ft_memset(p, 0, sizeof(t_player));
	if (parsing(argc, argv, &data.textures, &data))
		return (1);
	ft_player_init(p, &data);
	ft_mlx_init(&(p->img));

	// ft_init_textures(p);
	ft_cub_render(p);
	free(p->img);
	free(p);
	free_parsing(&data.textures, &data);
	return (0);
}
