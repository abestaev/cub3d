/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:34:01 by melmarti          #+#    #+#             */
/*   Updated: 2024/11/04 17:24:00 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_player	*p;
	t_data		*data;
	t_textures	*textures;

	p = malloc(sizeof(t_player));
	if (!p)
		return (-1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (-1);
	textures = malloc(sizeof(t_textures));
	if (!textures)
		return (-1);
	ft_memset(p, 0, sizeof(t_player));
	ft_memset(data, 0, sizeof(t_data));
	ft_memset(textures, 0, sizeof(t_textures));
	data->textures = textures;
	if (parsing(argc, argv, data, p))
		ft_escape_parsing(p, data, textures);
	ft_mlx_init(p);
	ft_player_init(p, data);
	ft_init_textures(p);
	ft_init_elements(p);
	ft_mlx_events(p);
	return (0);
}
