/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:10:14 by albestae          #+#    #+#             */
/*   Updated: 2024/09/12 19:34:35 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int    get_map_line(char *str, t_textures *textures)
{
    if (textures->map_str_tmp == NULL)
        textures->map_str_tmp = ft_strdup(str);
    else
        textures->map_str_tmp = ft_strjoin_free(textures->map_str_tmp, str);
    return (0);
}

//todo
// step 1 get map
// trim spaces
// get longest
// copy in new clean tab
// parse flood fill
// fill space with 1


int parse_map(t_textures *textures)//, t_data *data)
{
    textures->map_tab_tmp = ft_split(textures->map_str_tmp, "\n");
    printf("textures->map_str_tmp:%s\n", textures->map_str_tmp);    
    if (textures->map_tab_tmp)
        dprintf(2, "map tab:%s\n", textures->map_tab_tmp[0]);
    else
        dprintf(2, "map tab is empty\n");
    //free(textures->map_str_tmp);
    //print_map(textures->map_tab_tmp);
    // todo check invalid character
    // todo check if map is closed
    // todo check if only one player position
    return (0);
}

// void copy_and_fill(t_textures *textures, t_data *data)
// {
    
// }

void print_map(char **map)
{
    int i = 0;
    while (map[i])
    {
        printf("%s\n", map[i]);
        i++;
    }
}