/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_doors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 02:41:29 by albestae          #+#    #+#             */
/*   Updated: 2024/10/29 12:05:12 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_door_valid(t_textures *textures, t_data *data)
{
	int		i;
	size_t	j;

	i = 0;
	while (i < (textures->nb_lines - 1))
	{
		j = 1;
		while (j < (textures->longest_line - 1))
		{
			if (data->map[i][j] == 'P' && (!(data->map[i - 1][j] == '0'
						&& data->map[i + 1][j] == '0' && data->map[i][j
						- 1] == '1' && data->map[i][j + 1] == '1')
					&& !(data->map[i - 1][j] == '1' && data->map[i
						+ 1][j] == '1' && data->map[i][j - 1] == '0'
						&& data->map[i][j + 1] == '0')))
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
