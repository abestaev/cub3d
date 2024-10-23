/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:07:23 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/23 16:57:05 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_get_text_index(t_player *p, t_ray *ray)
{
	(void)p;
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
int	ft_inside_doors(t_player *p, int x, int y)
{
	if (x > 0 && x < p->nb_col && y > 0 && y < p->nb_line)
	{
		if (p->map[y][x] == 'P' || p->map[y][x] == 'O')
			return(1);
			
	}
	return (0);
}

int	ft_inside_wall(t_player *p, int x, int y)
{
	if (p->map[y][x] == '1')
		return (1);
	return (0);
}

int	ft_count_lines(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	ft_count_columns(char **map)
{
	return (ft_strlen(map[0]));
}

double	ft_divide(double i, double j)
{
	return (i / j);
}

// double	ft_get_tile_size(char **map)
// {
// 	int	col;

// 	if (ft_divide(p->nb_col,
// 			p->nb_line) >= ft_divide(S_WIDTH, S_HEIGHT))
// 	{
// 		col = p->nb_col;
// 		return (S_WIDTH / col);
// 	}
// 	else
// 	{
// 		col = ft_count_lines(map);
// 		return (S_HEIGHT / col);
// 	}
// }

void	ft_draw_tile(t_image *img, int start_x, int start_y, int size,
		int color)
{
	int	x;
	int	y;

	x = start_x;
	while (x < start_x - 1 + size && x < 20 * img->p->mini->tile_size)
	{
		y = start_y;
		while (y < start_y - 1 + size && y < (S_HEIGHT * 5 / 6) + 10
			* img->p->mini->tile_size && start_y > S_HEIGHT * 5 / 6 - 10
			* img->p->mini->tile_size)
		{
			if (x > 0 && x < S_WIDTH && y > 0 && y < S_HEIGHT)
				my_pixel_put(img, x, y, color);
			y++;
		}
		x++;
	}
}
void	ft_draw_alpha_tile(t_image *img, int start_x, int start_y, int size,
		int color)
{
	int	x;
	int	y;

	x = start_x;
	while (x < start_x - 1 + size)
	{
		y = start_y;
		while (y < start_y - 1 + size)
		{
			if (x > 0 && x < S_WIDTH && y > 0 && y < (S_HEIGHT * 5 / 6) + 10
				* img->p->mini->tile_size)
				my_pixel_put(img, x, y, color);
			y += 2;
		}
		x += 2;
	}
}
int	get_hexa_color(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	ft_color_background(t_image *img)
{
	t_textures		*textures;
	int				total_pixels;
	char			*dst;
	unsigned int	color;
	int				i;

	textures = img->p->data->textures;
	total_pixels = S_WIDTH * S_HEIGHT;
	dst = img->addr;
	i = 0;
	while (i < total_pixels)
	{
		if (i < total_pixels / 2)
		{
			color = textures->ceiling_col;
		}
		else
			color = textures->floor_col;
		*(unsigned int *)(dst + i * (img->bits_per_pixel / 8)) = color;
		i++;
	}
}

int	ft_escape(t_player *p)
{
	free_parsing(p->data->textures, p->data);
	free_tab((char **)p->texture);
	free(p->ray);
	mlx_loop_end(p->img->mlx);
	mlx_destroy_window(p->img->mlx, p->img->win_ptr);
	mlx_destroy_image(p->img->mlx, p->img->img);
	mlx_destroy_display(p->img->mlx);	
	free(p->img->mlx);
	free(p->img);
	free(p->data->textures);
	free(p->data);
	free(p->mini);
	free(p);
	exit(0);
}

void	ft_draw_vertical_line(int x_val, int start, int end, t_image *img,
		long color)
{
	int	y;

	y = start;
	if (start < 0)
		start = 0;
	if (end >= S_HEIGHT)
		end = S_HEIGHT - 1;
	while (y <= end)
	{
		my_pixel_put(img, x_val, y, color);
		y++;
	}
}
void	ft_draw_horizontal_line(int y_val, int start, int end, t_image *img,
		long color)
{
	int	x;

	x = start;
	if (start < 0)
		start = 0;
	if (end >= S_WIDTH)
		end = S_WIDTH - 1;
	while (x <= end)
	{
		my_pixel_put(img, x, y_val, color);
		x++;
	}
}

void	ft_draw_line(int x_start, int y_start, int x_end, int y_end,
		t_image *img)
{
	int	delta_x;
	int	delta_y;
	int	d;
	int	temp;
	int	y;
	int	x;
	int	y_inc;
	int	x_inc;

	delta_x = abs(x_end - x_start);
	delta_y = abs(y_end - y_start);
	// Si l'axe X domine
	if (delta_x > delta_y)
	{
		// Inverser les points si nécessaire
		if (x_start > x_end)
		{
			temp = x_start;
			x_start = x_end;
			x_end = temp;
			temp = y_start;
			y_start = y_end;
			y_end = temp;
		}
		y_inc = -1;
		if (y_end >= y_start)
			y_inc = 1;
		y = y_start;
		x = x_start;
		d = 2 * delta_y - delta_x;
		while (x <= x_end)
		{
			if (x >= 0 && x < S_WIDTH && y >= 0 && y < S_HEIGHT)
				my_pixel_put(img, x, y, COLOR_BLUE);
			if (d > 0)
			{
				y += y_inc;
				d -= 2 * delta_x;
			}
			d += 2 * delta_y;
			x++;
		}
	}
	// Si l'axe Y domine
	else
	{
		// Inverser les points si nécessaire
		if (y_start > y_end)
		{
			temp = x_start;
			x_start = x_end;
			x_end = temp;
			temp = y_start;
			y_start = y_end;
			y_end = temp;
		}
		x_inc = -1;
		if (x_end >= x_start)
			x_inc = 1;
		x = x_start;
		y = y_start;
		d = 2 * delta_x - delta_y;
		while (y <= y_end)
		{
			if (x >= 0 && x < S_WIDTH && y >= 0 && y < S_HEIGHT)
				my_pixel_put(img, x, y, COLOR_BLUE);
			if (d > 0)
			{
				x += x_inc;
				d -= 2 * delta_y;
			}
			d += 2 * delta_x;
			y++;
		}
	}
}

// int	*ft_exit(void *param)
// {
// 	t_image *img;

// 	img = (t_image *)img;
// 	mlx_destroy_image(img->win_ptr, img->img);
// 	mlx_destroy_window(img->win_ptr, img->img);
// 	mlx_loop_end(img->win_ptr);
// 	return (NULL);
// }