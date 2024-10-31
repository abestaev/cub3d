/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 05:32:07 by albestae          #+#    #+#             */
/*   Updated: 2024/10/31 12:03:24 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_open(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nCouldn't open [ %s ]\n", str);
		return (1);
	}
	else
		close(fd);
	return (0);
}

int	check_file_valid(t_textures *t)
{
	if (check_open(t->north) || check_open(t->east) || check_open(t->south)
		|| check_open(t->west) || check_open("./textures/candle_1.xpm")
		|| check_open("./textures/candle_2.xpm")
		|| check_open("./textures/candle_3.xpm")
		|| check_open("./textures/candle_4.xpm")
		|| check_open("./textures/candle_5.xpm")
		|| check_open("./textures/candle_6.xpm")
		|| check_open("./textures/doorframe_1.xpm")
		|| check_open("./textures/doorframe_2.xpm")
		|| check_open("./textures/doorframe_3.xpm")
		|| check_open("./textures/doorframe_4.xpm")
		|| check_open("./textures/doorframe_5.xpm")
		|| check_open("./textures/doorframe_6.xpm"))
	{
		return (1);
	}
	return (0);
}

int	parse_line(char *str, t_textures *textures)
{
	char	**tab;

	tab = ft_split(str, " \n");
	{
		if (ft_count_tab(tab) != 2)
		{
			printf("Error\nInvalid line content number\n");
			read_until_end(textures);
			free_tab(tab);
			return (1);
		}
		if (compare_texture_line(tab[0], tab[1], textures) == 1)
		{
			read_until_end(textures);
			free_tab(tab);
			return (1);
		}
	}
	free_tab(tab);
	return (0);
}

static int	empty_line(t_textures *textures, char *line)
{
	if (!line)
	{
		printf("Error\nEmpty file\n");
		close(textures->fd);
		return (1);
	}
	return (0);
}

int	read_file(t_textures *textures)
{
	char	*line;

	line = get_next_line(textures->fd);
	if (empty_line(textures, line))
		return (free(line), 1);
	while (line)
	{
		if (line[0] == '\n')
			free(line);
		else
		{
			if (textures->i++ < 6)
			{
				if (parse_line(line, textures))
					return (free(line), close(textures->fd), 1);
			}
			else
				get_map_line(line, textures);
			free(line);
		}
		line = get_next_line(textures->fd);
	}
	close(textures->fd);
	return (0);
}
