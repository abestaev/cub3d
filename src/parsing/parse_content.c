/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 05:34:18 by albestae          #+#    #+#             */
/*   Updated: 2024/10/23 11:56:44 by melmarti         ###   ########.fr       */
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

int	check_rgb_values(t_textures *textures)
{
	char	**tmp1;
	char	**tmp2;

	tmp1 = ft_split(textures->ceiling, ",");
	tmp2 = ft_split(textures->floor, ",");
	textures->ceiling_r = ft_atoi(tmp1[0]);
	textures->ceiling_g = ft_atoi(tmp1[1]);
	textures->ceiling_b = ft_atoi(tmp1[2]);
	textures->floor_r = ft_atoi(tmp2[0]);
	textures->floor_g = ft_atoi(tmp2[1]);
	textures->floor_b = ft_atoi(tmp2[2]);
	if (textures->ceiling_r < 0 || textures->ceiling_r > 255
		|| textures->ceiling_g < 0 || textures->ceiling_g > 255
		|| textures->ceiling_b < 0 || textures->ceiling_b > 255
		|| textures->floor_r < 0 || textures->floor_r > 255
		|| textures->floor_g < 0 || textures->floor_g > 255
		|| textures->floor_b < 0 || textures->floor_b > 255)
	{
		return (1);
	}
	textures->ceiling_col = get_hexa_color(textures->ceiling_r,
			textures->ceiling_g, textures->ceiling_b);
	textures->floor_col = get_hexa_color(textures->floor_r, textures->floor_g,
			textures->floor_b);
	free_tab(tmp1);
	free_tab(tmp2);
	return (0);
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
	if (ft_strlen(tmp1[0]) > 4 || ft_strlen(tmp2[0]) > 4
		|| ft_strlen(tmp1[1]) > 4 || ft_strlen(tmp2[1]) > 4
		|| ft_strlen(tmp1[2]) > 4 || ft_strlen(tmp2[2]) > 4)
	{
		printf("%s %s %zu %zu %zu %zu\n", tmp1[0], tmp2[0], ft_strlen(tmp1[1]),
			ft_strlen(tmp2[1]), ft_strlen(tmp1[2]), ft_strlen(tmp2[2]));
		printf("Error\nInvalid RGB format\n");
		return (1);
	}
	if (check_rgb_values(textures))
	{
		printf("Error\nInvalid RGB values\n");
		return (1);
	}
	free_tab((void *)tmp1);
	free_tab((void *)tmp2);
	return (0);
}

int	is_image_xpm(char *path)
{
	int	i;

	i = ft_strlen(path) - 4;
	if (i > 0 && ft_strncmp(path + i, ".xpm", 5))
		return (1);
	return (0);
}

int	isplayer(char c)
{
	if (c == 'W' || c == 'E' || c == 'S' || c == 'N')
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
			&& t->map_str_tmp[i] != 'W' && t->map_str_tmp[i] != 'E'
			&& t->map_str_tmp[i] != 'P' && t->map_str_tmp[i] != 'V') // bonus
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
