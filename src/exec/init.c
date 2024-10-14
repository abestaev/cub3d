/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:24:51 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/14 16:18:56 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_mlx_init(t_player *p)
{
	p->img = malloc(sizeof(t_image));
	p->img->mlx = mlx_init();
	p->img->win_ptr = mlx_new_window(p->img->mlx, S_WIDTH, S_HEIGHT, "Cub3D");
	p->img->img = mlx_new_image(p->img->mlx, S_WIDTH, S_HEIGHT);
	if (!p->img->img)
		return;
	p->img->addr = mlx_get_data_addr(p->img->img, &p->img->bits_per_pixel,
			&p->img->line_length, &p->img->endian);
	mlx_hook(p->img->win_ptr, KeyPress, KeyPressMask, ft_handle_hook, p);
	mlx_hook(p->img->win_ptr, 33, 1L << 17, &ft_escape, p);
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
				p->pos.x = j;
				p->pos.y = i;
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
	t_minimap *mini;

	ray = malloc(sizeof(t_ray));
	mini = malloc(sizeof(t_minimap));
	ft_memset(ray, 0, sizeof(t_ray));
	ft_memset(mini, 0, sizeof(t_minimap));
	p->mini = mini;
	ft_init_player_pos(p, data->textures);
	p->map = data->map;
	p->tile_size = ft_get_tile_size(p->map);
	p->ray = ray;
	p->plr_speed = SPEED;
	p->speed_rot = ROT_SPEED;
	p->data = data;
	p->mini->p_x = p->pos.x;
	p->mini->p_y = p->pos.y;
}
