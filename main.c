/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:34:01 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/17 15:08:10 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_refresh(t_player *p)
{
	if (!p->data->old_time)
		p->data->old_time = ft_get_sec_time();
	p->data->actual_time = ft_get_sec_time();
	ft_color_background(p->img);
	ft_cast_ray(p);
	ft_minimap(p);
	mlx_put_image_to_window(p->img->mlx, p->img->win_ptr, p->img->img, 0, 0);
	ft_print_fps(p->data);
	p->data->fps++;
}

void	ft_free_all_struct(t_player *p)
{
	free(p->img);
	free(p->ray);
	free(p);
}

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
	ft_memset(textures, 0, sizeof(t_textures));
	data->textures = textures;
	if (parsing(argc, argv, data))
		return (1);
	ft_player_init(p, data);
	ft_mlx_init(p);
	ft_init_textures(p);
	ft_init_minimap(p);
	ft_refresh(p);
	ft_print_fps(data);
	mlx_loop(p->img->mlx);
	ft_free_all_struct(p);
	free_parsing(data->textures, data);
	return (0);
}
