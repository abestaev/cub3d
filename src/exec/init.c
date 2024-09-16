/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:24:51 by melmarti          #+#    #+#             */
/*   Updated: 2024/09/16 19:21:36 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <string.h>

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

void	ft_player_init(t_player *p)
{
	p->p_x = (S_WIDTH / 2) + (S_WIDTH % 2);
	p->p_y = (S_HEIGHT / 2) + (S_HEIGHT % 2);
	p->p_angl = 0;
	p->p_dir_x = p->p_x + 150 * cos(p->p_angl);
	p->p_dir_y = p->p_y + 150 * sin(p->p_angl);
}
