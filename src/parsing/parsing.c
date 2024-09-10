/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:07:37 by albestae          #+#    #+#             */
/*   Updated: 2024/09/10 18:41:21 by albestae         ###   ########.fr       */
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
    // if (read_textures(textures))
    //     return (1);
    return (0);
}