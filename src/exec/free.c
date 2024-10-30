/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:51:52 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/30 17:46:34 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_escape_parsing(t_player *p, t_data *data, t_textures *textures)
{
	free(textures->north);
	free(textures->south);
	free(textures->west);
	free(textures->east);
	free(textures->floor);
	free(textures->ceiling);
	free(textures->map_str_tmp);
	if (data->map)
		free_tab(data->map);
	if (textures->map_tab_tmp)
		free_tab(textures->map_tab_tmp);
	free(data);
	free(textures);
	free(p);
	exit(1);
}

static void	ft_escape_01(t_player *p)
{
	if (p->door_text)
		free_tab((char **)(p->door_text));
	if (p->sprite_text)
		free_tab((char **)(p->sprite_text));
	if (p->all_elem)
		free(p->all_elem);
	if (p->door)
		free(p->door);
	free(p);
}

int	ft_escape(t_player *p)
{
	free_parsing(p->data->textures, p->data);
	if (p->texture)
		free_tab((char **)p->texture);
	if (p->ray)
		free(p->ray);
	if (p->sprite)
		free(p->sprite);
	mlx_loop_end(p->img->mlx);
	mlx_destroy_window(p->img->mlx, p->img->win_ptr);
	mlx_destroy_image(p->img->mlx, p->img->img);
	mlx_destroy_display(p->img->mlx);
	free(p->img->mlx);
	free(p->img);
	if (p->data->textures)
		free(p->data->textures);
	if (p->data)
		free(p->data);
	if (p->mini)
		free(p->mini);
	free(p->ray_doors);
	ft_escape_01(p);
	exit(0);
}
