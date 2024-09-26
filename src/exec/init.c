/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:24:51 by melmarti          #+#    #+#             */
/*   Updated: 2024/09/26 18:07:05 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_image	*ft_mlx_init(void)
{
	t_image	*img;

	img = malloc(sizeof(t_image));
	img->mlx = mlx_init();
	img->win_ptr = mlx_new_window(img->mlx, S_WIDTH, S_HEIGHT, "Cub3D");
	img->img = mlx_new_image(img->mlx, S_WIDTH, S_HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	return (img);
}

void	ft_player_init(t_player *p, t_data *data)
{
	t_ray *ray;

	ray = malloc(sizeof(t_ray));
	ft_memset(ray, 0, sizeof(t_ray));
	p->ray = ray;
	p->p_x = (S_WIDTH / 2);
	p->p_y = (S_HEIGHT / 2);
	p->p_dir_x = 0;
	p->p_dir_y = 1;
	p->map = data->map;
	p->plr_speed = SPEED;
	p->speed_rot = ROT_SPEED;
	p->tile_size = ft_get_tile_size(p->map);
	p->plane_x = 0.66;
	p->plane_y = 0;
	p->data = data;

}
