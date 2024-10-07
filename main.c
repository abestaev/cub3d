/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:34:01 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/07 19:06:09 by melmarti         ###   ########.fr       */
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
int	**ft_init_screen_pixels()
{
	int	i;
	int	**text_pixels;

	text_pixels = malloc(sizeof(int *) * (S_HEIGHT + 1));
	if (!text_pixels)
		return (NULL); // Gérer l'erreur

	i = 0;
	while (i < S_HEIGHT)
	{
		text_pixels[i] = ft_calloc(S_WIDTH + 1, sizeof(int));
		if (!text_pixels[i])
		{
			// Libération de la mémoire en cas d'échec d'allocation
			while (i > 0)
				free(text_pixels[--i]);
			free(text_pixels);
			return (NULL);
		}
		i++;
	}
	return (text_pixels);
}


void	ft_calcul_wall_text(t_player *p, int start, int x, int end)
{
	int	y;
	int	color;
	int text_index = ft_get_text_index(p->ray);
	int text_x;
	int text_y;
	int text_step;
	int pos;

	int **text_buff = ft_init_screen_pixels();

	text_x = (int)(p->ray->wall_x * TEXTURE_SIZE);
	if ((p->ray->side == 0 && p->ray->dir_x < 0) || (p->ray->side == 1
			&& p->ray->dir_y > 0))
		text_x = TEXTURE_SIZE - text_x - 1;
	text_step = 1.0 * TEXTURE_SIZE / p->ray->wall_height;
	pos = (start - S_HEIGHT / 2 + p->ray->wall_dist / 2)
		* text_step;
	y = start;
	while (y < end)
	{
		text_y = pos & (TEXTURE_SIZE - 1);
		pos += text_step;
		color = p->texture[text_index][TEXTURE_SIZE * text_y + text_x];
		if (text_index == 0 || text_index == 1)
			color = (color >> 1) & 8355711;
		if (color > 0)
			text_buff[y][x] = color;
		y++;
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
	// if (ray->side == 1)
	// 	ft_draw_vertical_line(x, start, end, p->img, COLOR_MAGENTA);
	// else
	// 	ft_draw_vertical_line(x, start, end, p->img, COLOR_BLUE);
	ft_calcul_wall_text(p, start, x, end);
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
	ft_init_textures(p);
	ft_cub_render(p);
	free(p->img);
	free(p);
	free_parsing(&data.textures, &data);
	return (0);
}
