/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 05:34:18 by albestae          #+#    #+#             */
/*   Updated: 2024/09/24 12:54:13 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_arrlen(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return (0);
	while (array[i])
		i++;
	return (i);
}

int	parse_rgb(t_textures *textures)
{
	char	**tmp1;
	char	**tmp2;

	tmp1 = ft_split(textures->ceiling, ",");
	tmp2 = ft_split(textures->floor, ",");
	if (ft_arrlen(tmp1) != 3 || ft_arrlen(tmp2) != 3)
	{
		printf("Error\nInvalid RGB format\n");
		return (1);
	}
	free_tab(tmp1);
	free_tab(tmp2);
	return (0);
}

int	is_image_png(char *path)
{
	int	i;

	i = ft_strlen(path) - 5;
	if (ft_strncmp(path + i, ".png", 4))
		return (1);
	return (0);
}

int	isplayer(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
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
		if (isplayer(t->map_str_tmp[i]))
			count++;
		if (count > 1)
		{
			printf("Error\nToo many player positions\n");
			return (1);
		}
	}
	return (0);
}
