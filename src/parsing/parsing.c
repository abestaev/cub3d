/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:07:37 by albestae          #+#    #+#             */
/*   Updated: 2024/09/12 18:12:22 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Function to check if the number of arguments is valid
int     arg_valid(int argc, char **argv)
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

static void     free_tab(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

// todo check if DOUBLONS
static int compare_texture_line(char *s1, char *s2, t_textures *textures)
{
    if (ft_strncmp(s1, "NO", 2) == 0)
        textures->north = s2;
    else if (ft_strncmp(s1, "SO", 2) == 0)
        textures->south = s2;
    else if (ft_strncmp(s1, "WE", 2) == 0)
        textures->west = s2;
    else if (ft_strncmp(s1, "EA", 2) == 0)
        textures->east = s2;
    // else if (ft_strncmp(s1, "F", 1) == 0)
    //     textures->floor = convert_rgb_to_hex(s2);
    // else if (ft_strncmp(s1, "C", 1) == 0)
    //     textures->ceiling = convert_rgb_to_hex(s2);
    else
    {
        printf("Error\nInvalid texture line\n");
        return (1);
    }
    return (0);
}

int     parse_line(char *str, t_textures *textures)
{
    char **tab;
    int i;
    
    tab = ft_split(str, " ");
    i = 0;
    {
        if (ft_count_tab(tab) != 2)
        {
            printf("Error\nInvalid line\n");
            free_tab(tab);
            return (1);
        }
        if (compare_texture_line(tab[0], tab[1], textures) == 1)
        {
            free_tab(tab);
            return (1);
        }
    }
    free(tab[0]);
    free(tab);
    return (0);
}

// todo check if the file is well formated


// todo check if rbv values are between 0 and 255 + well formated


int     read_file(t_textures *textures)
{
    char    *line;
    int i;
    
    i = 0;
    line = get_next_line(textures->fd);
    while (line)
    {
        if (line[0] == '\n')
            free(line);
        else
        {
            if (i++ < 6)
            {
                if (parse_line(line, textures))
                    break ;
            }
            else
                parse_map(line, textures);
            free(line);
        }
        line = get_next_line(textures->fd);
    }
    free(line);
    close(textures->fd);
    return (0);
}

//todo
// step 1 get map
// trim spaces
// get longest
// copy in new clean tab
// parse flood fill
// fill space with 1
int    parse_map(char *str, t_data *data)
{
    printf("map:%s\n", str);
    return (0);
}

// Function to group all the parsing functions
int     parsing(int argc, char **argv, t_textures *textures)
{
    if (arg_valid(argc, argv))
        return (1);
    if ((textures->fd = open(argv[1], O_RDONLY)) == -1)
    {
        printf("Error\nCould not open file\n");
        return (1);
    }
    if (read_file(textures))
        return (1);
    return (0);
}

// todo Function to convert a string of rgb values to an int



