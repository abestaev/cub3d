/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_doors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 02:41:29 by albestae          #+#    #+#             */
/*   Updated: 2024/10/30 11:39:28 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid(char c)
{
	if (c == '0' || c == 'V' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	is_door_valid(t_textures *textures, t_data *data)
{
	int		i;
	size_t	j;

	i = 0;
	while (i < (textures->nb_lines - 1))
	{
		j = 1;
		while (j < (textures->col - 1))
		{
			if (data->map[i][j] == 'P' && (!(is_valid(data->map[i - 1][j])
						&& is_valid(data->map[i + 1][j]) && data->map[i][j
						- 1] == '1' && data->map[i][j + 1] == '1')
					&& !(data->map[i - 1][j] == '1' && data->map[i
						+ 1][j] == '1' && is_valid(data->map[i][j - 1])
						&& is_valid(data->map[i][j + 1]))))
			{
				printf("Error\nInvalid door\n");
				return (1);
			}
				j++;
		}
		i++;
	}
	return (0);
}
