/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 06:21:57 by albestae          #+#    #+#             */
/*   Updated: 2024/10/30 11:39:28 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_top_bottom(t_data *data, t_textures *textures)
{
	int	i;

	i = 0;
	while (data->map[0][i])
	{
		if (data->map[0][i] == '0' || isplayer(data->map[0][i])
			|| data->map[0][i] == 'P') // bonus
			return (printf("Error\nMap is not closed (top)\n"), 1);
		i++;
	}
	i = 0;
	while (data->map[textures->nb_lines - 1][i])
	{
		if (data->map[textures->nb_lines - 1][i] == '0'
			|| isplayer(data->map[textures->nb_lines - 1][i])
			|| data->map[textures->nb_lines - 1][i] == 'P') // bonus
			return (printf("Error\nMap is not closed (bottom)\n"), 1);
		i++;
	}
	return (0);
}

int	check_sides(t_data *data, t_textures *textures)
{
	int	i;

	i = 0;
	while (i < textures->nb_lines)
	{
		if (data->map[i][0] == '0' || data->map[i][0] == 'P') // bonus
		{
			printf("Error\nMap is not closed (left)\n");
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < textures->nb_lines)
	{
		if (data->map[i][textures->col - 2] == '0'
			|| data->map[i][textures->col - 2] == 'P') // bonus
		{
			printf("Error\nMap is not closed (right)\n");
			return (1);
		}
		i++;
	}
	return (0);
}
