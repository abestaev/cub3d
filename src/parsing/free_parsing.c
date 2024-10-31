/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 00:41:29 by albestae          #+#    #+#             */
/*   Updated: 2024/10/31 12:04:55 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_parsing(t_textures *textures, t_data *data)
{
	free(textures->north);
	free(textures->south);
	free(textures->west);
	free(textures->east);
	free(textures->floor);
	free(textures->ceiling);
	free_tab(textures->map_tab_tmp);
	free(textures->map_str_tmp);
	free_tab((void *)data->map);
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
	if (tmp && ft_strlen(tmp) > textures->col)
		textures->col = ft_strlen(tmp);
	if (textures->map_str_tmp == NULL)
		textures->map_str_tmp = ft_strdup(tmp);
	else if (textures->map_str_tmp)
		textures->map_str_tmp = ft_strjoin_free(textures->map_str_tmp, tmp);
	free(tmp);
	return (0);
}

void	read_until_end(t_textures *textures)
{
	char	*str;

	str = get_next_line(textures->fd);
	while (str)
	{
		free(str);
		str = get_next_line(textures->fd);
	}
}
