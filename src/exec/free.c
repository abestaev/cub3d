/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:51:52 by melmarti          #+#    #+#             */
/*   Updated: 2024/11/04 14:33:44 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_escape_parsing(t_player *p, t_data *data, t_textures *textures)
{
	if (textures->north)
		free(textures->north);
	if (textures->south)
		free(textures->south);
	if (textures->west)
		free(textures->west);
	if (textures->east)
		free(textures->east);
	if (textures->floor)
		free(textures->floor);
	if (textures->ceiling)
		free(textures->ceiling);
	if (textures->map_str_tmp)
		free(textures->map_str_tmp);
	if (data->map)
		free_tab(data->map);
	if (textures->map_tab_tmp)
		free_tab(textures->map_tab_tmp);
	if (data)
		free(data);
	if (textures)
		free(textures);
	free(p);
	exit(1);
}

static void	ft_escape_mlx(t_player *p)
{
	if (p->door_text)
		free_tab((char **)(p->door_text));
	if (p->sprite_text)
		free_tab((char **)(p->sprite_text));
	if (p->all_elem)
		free(p->all_elem);
	if (p->door)
		free(p->door);
	if (p->img && p->img->mlx_ptr)
		mlx_loop_end(p->img->mlx_ptr);
	if (p->img && p->img->mlx_ptr && p->img->win_ptr)
		mlx_destroy_window(p->img->mlx_ptr, p->img->win_ptr);
	if (p->img && p->img->mlx_ptr && p->img->img_ptr)
		mlx_destroy_image(p->img->mlx_ptr, p->img->img_ptr);
	if (p->img && p->img->mlx_ptr && p->img->mlx_ptr)
		mlx_destroy_display(p->img->mlx_ptr);
	if (p->img && p->img->mlx_ptr)
		free(p->img->mlx_ptr);
	if (p->img)
		free(p->img);
	free(p);
}

int	ft_escape(t_player *p)
{
	if (p->data)
		free_parsing(p->data->textures, p->data);
	if (p->texture)
		free_tab((char **)p->texture);
	if (p->ray)
		free(p->ray);
	if (p->sprite)
		free(p->sprite);
	if (p->data && p->data->textures)
		free(p->data->textures);
	if (p->data)
		free(p->data);
	if (p->mini)
		free(p->mini);
	if (p->ray_doors)
		free(p->ray_doors);
	ft_escape_mlx(p);
	exit(0);
}
