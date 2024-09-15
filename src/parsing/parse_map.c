/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:10:14 by albestae          #+#    #+#             */
/*   Updated: 2024/09/15 05:37:56 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_map(t_textures *textures, t_data *data)
{
	int	i;

	data->map = malloc(sizeof(char *) * data->textures.nb_lines + 1);
	if (data->map == NULL)
		return (1);
	i = 0;
	while (i < textures->nb_lines)
	{
		data->map[i] = malloc(sizeof(char) * (textures->longest_line));
		if (data->map[i] == NULL)
			return (1);
		ft_memset(data->map[i], ' ', textures->longest_line);
		data->map[i][textures->longest_line - 1] = '\0';
		i++;
	}
	data->map[i] = NULL;
	textures->map_tab_tmp = ft_split(textures->map_str_tmp, "\n");
	free(textures->map_str_tmp);
	if (copy_and_check_walls(textures, data))
		return (1);
	return (0);
}

int	is_surrounded(int i, int j, t_textures *t)
{
	if (t->map_tab_tmp[i - 1][j] == ' ')
		return (1);
	else if (t->map_tab_tmp[i + 1][j] == ' ')
		return (1);
	else if (t->map_tab_tmp[i][j - 1] == ' ')
		return (1);
	else if (t->map_tab_tmp[i][j + 1] == ' ')
		return (1);
	return (0);
}

int	is_map_open(t_data *data, t_textures *textures)
{
	int		i;
	size_t	j;

	if (check_top_bottom(data, textures) || check_sides(data, textures))
		return (1);
	i = 1;
	while (i < (textures->nb_lines - 1))
	{
		j = 1;
		while (j < (textures->longest_line - 1))
		{
			if (data->map[i][j] == '0')
			{
				if (is_surrounded(i, j, textures))
				{
					printf("Error\nMap is not closed\n");
					return (1);
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	map_size(t_textures *textures)
{
	if (textures->nb_lines <= 3)
	{
		printf("Error\nMap is too small\n");
		return (1);
	}
	if (textures->longest_line <= 3)
	{
		printf("Error\nMap is too small\n");
		return (1);
	}
	return (0);
}

int	copy_and_check_walls(t_textures *textures, t_data *data)
{
	int	i;

	i = 0;
	while (textures->map_tab_tmp[i])
	{
		ft_strcpy(data->map[i], textures->map_tab_tmp[i]);
		i++;
	}
	if (map_size(textures))
		return (1);
	if (is_map_open(data, textures))
		return (1);
	return (0);
}
