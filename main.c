/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:34:01 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/14 20:09:06 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_get_text_index(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x < 0)
			return (0);
		else
			return (1);
	}
	else
	{
		if (ray->dir_y > 0)
			return (2);
		else
			return (3);
	}
}
void ft_calcul_wall_text(t_player *p, int x, int start, int end)
{
    int     y;
    int     color;
    int     text_index;
    int     text_x;
    int     text_y;
    double  text_step;
    double  pos;

    text_index = ft_get_text_index(p->ray);
    text_x = (int)(p->ray->wall_x * TEXTURE_SIZE);
    if ((p->ray->side == 0 && p->ray->dir_x < 0) || (p->ray->side == 1 && p->ray->dir_y > 0))
        text_x = TEXTURE_SIZE - text_x - 1;
    text_step = (double)TEXTURE_SIZE / p->ray->wall_height;
    pos = (start - S_HEIGHT / 2 + p->ray->wall_height / 2) * text_step;
    y = start;
    while (y < end)
    {
        text_y = (int)pos & (TEXTURE_SIZE - 1);
        pos += text_step;
        color = p->texture[text_index][TEXTURE_SIZE * text_y + text_x];
		if (text_index == 0 || text_index == 1)
			color = (color >> 1) & 8355711;
        if (color > 0)
            my_pixel_put(p->img, x, y, color);
        y++;
    }
}

/* We will take the distance from the camera plane to avoid the fish eyes effect */
/* If we get the sizeonly throuht the coordinate of the player we'll have the distortion,
if we increment some points along the camera vectore the distance will always have good proportion according to the distance from the wall to the camera vector */
void ft_get_wall_size(t_player *p, int x)
{
    double wall_dist;
    int start;
    int end;
    t_ray *ray;

    ray = p->ray;
    
  	if (ray->side == 0)
        wall_dist = (ray->side_dist_x - ray->delta_dist_x);
    else
        wall_dist = (ray->side_dist_y - ray->delta_dist_y);
    ray->wall_height = (int)(S_HEIGHT / wall_dist);
    start = -ray->wall_height / 2 + S_HEIGHT / 2;
    if (start < 0)
        start = 0;
    end = ray->wall_height / 2 + S_HEIGHT / 2;
    if (end >= S_HEIGHT)
        end = S_HEIGHT - 1;
    if (ray->side == 0)
        ray->wall_x = p->pos.y + wall_dist * ray->dir_y;
    else
        ray->wall_x = p->pos.x + wall_dist * ray->dir_x;
    ray->wall_x -= floor(ray->wall_x);
    ft_calcul_wall_text(p, x, start,  end);
}

void	ft_refresh_frame(t_player *p)
{
	ft_clear_image(p->img, COLOR_DARK_GRAY);
	ft_cast_ray(p);
	mlx_put_image_to_window(p->img->mlx, p->img->win_ptr, p->img->img, 0, 0);
	// ft_minimap_render(p, p->map);
	// ft_player_render(p);
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
	ft_mlx_init(p);
	ft_init_textures(p);
	ft_refresh_frame(p);
	mlx_loop(p->img->mlx);
	free(p->img);
	free(p);
	free_parsing(&data.textures, &data);
	return (0);
}
