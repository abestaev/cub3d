/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:07:23 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/30 14:07:30 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_get_text_index(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x < 0)
			return (WEST);
		else
			return (EAST);
	}
	else
	{
		if (ray->dir_y > 0)
			return (NORTH);
		else
			return (SOUTH);
	}
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

int	ft_is_in_adjacent_cells(t_player *p, int x, int y, char c)
{
	if (p->map[y][x + 1] == c || p->map[y][x - 1] == c || p->map[y + 1][x] == c
		|| p->map[y - 1][x] == c)
		return (1);
	return (0);
}
