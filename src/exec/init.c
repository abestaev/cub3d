/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:24:51 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/15 12:46:34 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_ray(t_player *p, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)S_WIDTH - 1;
	p->ray->dir_x = p->p_dir_x + p->plane_x * camera_x;
	p->ray->dir_y = p->p_dir_y + p->plane_y * camera_x;
	p->ray->delta_dist_x = fabs(1 / p->ray->dir_x);
	p->ray->delta_dist_y = fabs(1 / p->ray->dir_y);
	p->ray->map_x = (int)p->pos.x;
	p->ray->map_y = (int)p->pos.y;
}

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

void	ft_init_player_orientation_01(char c, t_player *p)
{
	if (c == 'E')
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

void	ft_init_player_orientation_00(char c, t_player *p)
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
	ft_init_player_orientation_01(c, p);
}

void	ft_init_player_pos(t_player *p)
{
	int	i;
	int	j;

	i = 0;
	while (p->map[i])
	{
		j = 0;
		while (p->map[i][j])
		{
			if (isplayer(p->map[i][j]))
			{
				p->pos.x = j + 0.2;
				p->pos.y = i + 0.2;
				ft_init_player_orientation(p->map[i][j], p);
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
	p->map = data->map;
	ft_init_player_pos(p);
	p->tile_size = ft_get_tile_size(p->map);
	p->ray = ray;
	p->plr_speed = SPEED;
	p->speed_rot = ROT_SPEED;
	p->data = data;
	p->mini->p_x = p->pos.x;
	p->mini->p_y = p->pos.y;
}
