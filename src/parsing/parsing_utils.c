/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 05:29:56 by albestae          #+#    #+#             */
/*   Updated: 2024/10/30 16:22:29 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	print_map(char **map)
{
	int	i;

	i = 0;
	if (map == NULL)
		return ;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
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

int	ft_arrlen(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return (0);
	while (array[i])
		i++;
	return (i);
}
