/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_doors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 02:41:29 by albestae          #+#    #+#             */
/*   Updated: 2024/10/21 17:24:46 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_door_valid(t_textures *textures, t_data *data)
{
	int		i;
	int		doors_nb;
	size_t	j;
	t_doors	doors;

	doors_nb = 0;
	i = 0;
	data->doors = &doors;
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
			else
				doors_nb++;
			j++;
		}
		i++;
	}
	data->doors->doors_tab = malloc(sizeof(int) * doors_nb) + 1;
	return (0);
}
