/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:10:14 by albestae          #+#    #+#             */
/*   Updated: 2024/09/15 03:01:28 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int     is_map_open(t_data *data, t_textures *textures)
{
    int i;
    size_t j;

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

void	ft_strcpy(char *dest, const char *src)
{
	size_t	i;

	i = 0;
	if (!src || !dest)
		return ;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
}
int map_size(t_textures *textures)
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

void	print_map(char **map)
{
	int i;

	i = 0;
	if (map == NULL)
		return ;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}