/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renard <renard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:24:51 by melmarti          #+#    #+#             */
/*   Updated: 2024/09/28 13:04:05 by renard           ###   ########.fr       */
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
void	ft_init_player_orientation(char c, t_player *p)
{
	if (c == 'N')
	{
		p->p_dir_x = 0;
		p->p_dir_y = -1;
		p->plane_x = 0.66;
		p->plane_y = 0;
	}
	else if (c == 'S')
	{
		p->p_dir_x = 0;
		p->p_dir_y = 1;
		p->plane_x = -0.66;
		p->plane_y = 0;
	}
	else if (c == 'E')
	{
		p->p_dir_x = 1;
		p->p_dir_y = 0;
		p->plane_x = 0;
		p->plane_y = 0.66;
	}
	else if (c == 'W')
	{
		p->p_dir_x = -1;
		p->p_dir_y = 0;
		p->plane_x = 0;
		p->plane_y = -0.66;
	}
}

void	ft_init_player_pos(t_player *p, t_textures t)
{
	int	i;
	int	j;

	i = 0;
	while (t.map_tab_tmp[i])
	{
		j = 0;
		while (t.map_tab_tmp[i][j])
		{
			if (isplayer(t.map_tab_tmp[i][j]))
			{
				p->p_x = j;
				p->p_y = i;
				ft_init_player_orientation(t.map_tab_tmp[i][j], p);
				break ;
			}
			j++;
		}
		i++;
	}
}

void	ft_player_init(t_player *p, t_data *data)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	ft_memset(ray, 0, sizeof(t_ray));
	ft_init_player_pos(p, data->textures);
	p->ray = ray;
	p->map = data->map;
	p->plr_speed = SPEED;
	p->speed_rot = ROT_SPEED;
	p->tile_size = ft_get_tile_size(p->map);
	p->data = data;
}
