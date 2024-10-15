/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:07:37 by albestae          #+#    #+#             */
/*   Updated: 2024/10/15 16:53:34 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	arg_valid(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Error\nInvalid number of arguments\n");
		return (1);
	}
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
	{
		printf("Error\nInvalid file extension\n");
		return (1);
	}
	return (0);
}

int	compare_texture_line(char *s1, char *s2, t_textures *textures)
{
	if (textures->north == NULL && ft_strncmp(s1, "NO", 2) == 0)
		textures->north = s2;
	else if (textures->south == NULL && ft_strncmp(s1, "SO", 2) == 0)
		textures->south = s2;
	else if (textures->west == NULL && ft_strncmp(s1, "WE", 2) == 0)
		textures->west = s2;
	else if (textures->east == NULL && ft_strncmp(s1, "EA", 2) == 0)
		textures->east = s2;
	else if (textures->floor == NULL && ft_strncmp(s1, "F", 1) == 0)
		textures->floor = s2;
	else if (textures->ceiling == NULL && ft_strncmp(s1, "C", 1) == 0)
		textures->ceiling = s2;
	else
	{
		printf("Error\nInvalid texture line\n");
		return (1);
	}
	return (0);
}

int	init_parsing(t_textures *textures, char *str)
{
	textures->fd = open(str, O_RDONLY);
	textures->north = NULL;
	textures->south = NULL;
	textures->west = NULL;
	textures->east = NULL;
	textures->floor = NULL;
	textures->ceiling = NULL;
	textures->map_str_tmp = NULL;
	textures->map_tab_tmp = NULL;
	textures->longest_line = 0;
	textures->nb_lines = 0;
	textures->i = 0;
	return (0);
}

int	missing_textures(t_textures *textures)
{
	if (textures->north == NULL || textures->south == NULL
		|| textures->west == NULL || textures->east == NULL
		|| textures->floor == NULL || textures->ceiling == NULL)
	{
		printf("Error\nMissing texture\n");
		return (1);
	}
	if (is_image_png(textures->north) || is_image_png(textures->south)
		|| is_image_png(textures->west) || is_image_png(textures->east))
	{
		printf("Error\nInvalid texture file extension\n");
		return (1);
	}
	if (parse_rgb(textures))
		return (1);
	return (0);
}

int	parsing(int argc, char **argv, t_data *data)
{
	if (arg_valid(argc, argv))
		return (1);
	init_parsing(data->textures, argv[1]);
	if (data->textures->fd == -1)
	{
		printf("Error\nCould not open file\n");
		return (1);
	}
	if (read_file(data->textures))
		return (1);
	if (missing_textures(data->textures))
		return (1);
	if (invalid_char(data->textures))
		return (1);
	if (parse_map(data->textures, data))
		return (1);
	return (0);
}
