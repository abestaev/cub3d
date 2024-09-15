/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 05:34:18 by albestae          #+#    #+#             */
/*   Updated: 2024/09/15 06:46:29 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int parse_rgb(t_textures *textures)
{
    char **tmp;

    tmp = ft_split(textures->ceiling, ",");
    return (0);
}

int	is_image_png(char *path)
{
	int	i;

	i = ft_strlen(path) - 4;
	if (ft_strncmp(path + i, ".png", 4))
		return (1);
	return (0);
}

int	invalid_char(t_textures *t)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (t->map_str_tmp[++i])
	{
		if (t->map_str_tmp[i] != ' ' && t->map_str_tmp[i] != '1'
			&& t->map_str_tmp[i] != '0' && t->map_str_tmp[i] != '\n'
			&& t->map_str_tmp[i] != 'N' && t->map_str_tmp[i] != 'S'
			&& t->map_str_tmp[i] != 'W' && t->map_str_tmp[i] != 'E')
		{
			printf("Error\nInvalid character '%c' in map\n", t->map_str_tmp[i]);
			return (1);
		}
		if ((t->map_str_tmp[i] == 'N' || t->map_str_tmp[i] == 'S'
				|| t->map_str_tmp[i] == 'W' || t->map_str_tmp[i] == 'E')
			&& count == 1)
		{
			printf("Error\nToo many player positions\n");
			return (1);
		}
	}
	return (0);
}
