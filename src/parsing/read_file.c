/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 05:32:07 by albestae          #+#    #+#             */
/*   Updated: 2024/09/15 05:43:05 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_line(char *str, t_textures *textures)
{
	char	**tab;
	int		i;

	tab = ft_split(str, " ");
	i = 0;
	{
		if (ft_count_tab(tab) != 2)
		{
			printf("Error\nInvalid line content number\n");
			free(str);
			free_tab(tab);
			return (1);
		}
		if (compare_texture_line(tab[0], tab[1], textures) == 1)
		{
			free(str);
			free_tab(tab);
			return (1);
		}
	}
	free(tab[0]);
	free(tab);
	return (0);
}

int	read_file(t_textures *textures)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(textures->fd);
	if (!line)
	{
		printf("Error\nEmpty file\n");
		close(textures->fd);
		return (1);
	}
	while (line)
	{
		if (line[0] == '\n')
			free(line);
		else
		{
			if (i++ < 6)
			{
				if (parse_line(line, textures))
					return (1);
			}
			else
				get_map_line(line, textures);
			free(line);
		}
		line = get_next_line(textures->fd);
	}
	free(line);
	close(textures->fd);
	return (0);
}

int	get_map_line(char *str, t_textures *textures)
{
	char	*tmp;
	size_t	i;

	textures->nb_lines++;
	i = ft_strlen(str) - 1;
	while (str && (str[i] == ' ' || str[i] == '\n'))
		i--;
	tmp = malloc(sizeof(char) * (i + 3));
	if (tmp == NULL)
		return (1);
	ft_strlcpy(tmp, str, i + 2);
	tmp[i + 1] = '\n';
	tmp[i + 2] = '\0';
	if (tmp && ft_strlen(tmp) > textures->longest_line)
		textures->longest_line = ft_strlen(tmp);
	if (textures->map_str_tmp == NULL)
		textures->map_str_tmp = ft_strdup(tmp);
	else if (textures->map_str_tmp)
		textures->map_str_tmp = ft_strjoin(textures->map_str_tmp, tmp);
	free(tmp);
	return (0);
}
