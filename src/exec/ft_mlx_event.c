
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:02:59 by melmarti          #+#    #+#             */
/*   Updated: 2024/09/30 12:03:26 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_go_down(t_player *p)
{
	if (ft_inside_wall(p, p->p_x - p->p_dir_x * p->plr_speed, p->p_y
			- p->p_dir_y * p->plr_speed))
	{
		p->p_x += p->p_dir_x * p->plr_speed + 0.01;
		p->p_y += p->p_dir_y * p->plr_speed + 0.01;
	}
	else
	{
		p->p_x -= p->p_dir_x * p->plr_speed;
		p->p_y -= p->p_dir_y * p->plr_speed;
	}
}

void	ft_go_up(t_player *p)
{
	if (ft_inside_wall(p, p->p_x + p->p_dir_x * p->plr_speed, p->p_y
			+ p->p_dir_y * p->plr_speed))
	{
		p->p_x -= p->p_dir_x * p->plr_speed + 0.01;
		p->p_y -= p->p_dir_y * p->plr_speed + 0.01;
	}
	else
	{
		p->p_x += p->p_dir_x * p->plr_speed;
		p->p_y += p->p_dir_y * p->plr_speed;
	}
}

void	ft_go_right(t_player *p)
{
	double	perp_dir_x;
	double	perp_dir_y;

	perp_dir_x = p->p_dir_y;
	perp_dir_y = -p->p_dir_x;
	if (ft_inside_wall(p, p->p_x + perp_dir_x * p->plr_speed, p->p_y
			+ perp_dir_y * p->plr_speed))
	{
		p->p_x -= perp_dir_x * p->plr_speed + 0.01;
		p->p_y -= perp_dir_y * p->plr_speed + 0.01;
	}
	else
	{
		p->p_x += perp_dir_x * p->plr_speed;
		p->p_y += perp_dir_y * p->plr_speed;
	}
}

void	ft_go_left(t_player *p)
{
	double	perp_dir_x;
	double	perp_dir_y;

	perp_dir_x = -p->p_dir_y;
	perp_dir_y = p->p_dir_x;
	if (ft_inside_wall(p, p->p_x + perp_dir_x * p->plr_speed, p->p_y
			+ perp_dir_y * p->plr_speed))
	{
		p->p_x -= perp_dir_x * p->plr_speed + 0.01;
		p->p_y -= perp_dir_y * p->plr_speed + 0.01;
	}
	else
	{
		p->p_x += perp_dir_x * p->plr_speed;
		p->p_y += perp_dir_y * p->plr_speed;
	}
}

void	ft_turn_right(t_player *p)
{
	double	tmp_dir_x;

	tmp_dir_x = p->p_dir_x;
	p->p_dir_x = p->p_dir_x * cos(-p->speed_rot) - p->p_dir_y
		* sin(-p->speed_rot);
	p->p_dir_y = tmp_dir_x * sin(-p->speed_rot) + p->p_dir_y
		* cos(-p->speed_rot);
	tmp_dir_x = p->plane_x;
	p->plane_x = p->plane_x * cos(-p->speed_rot) - p->plane_y
		* sin(-p->speed_rot);
	p->plane_y = tmp_dir_x * sin(-p->speed_rot) + p->plane_y
		* cos(-p->speed_rot);
}

void	ft_turn_left(t_player *p)
{
	double	tmp_dir_x;

	tmp_dir_x = p->p_dir_x;
	p->p_dir_x = p->p_dir_x * cos(p->speed_rot) - p->p_dir_y
		* sin(p->speed_rot);
	p->p_dir_y = tmp_dir_x * sin(p->speed_rot) + p->p_dir_y * cos(p->speed_rot);
	tmp_dir_x = p->plane_x;
	p->plane_x = p->plane_x * cos(p->speed_rot) - p->plane_y
		* sin(p->speed_rot);
	p->plane_y = tmp_dir_x * sin(p->speed_rot) + p->plane_y * cos(p->speed_rot);
}

int	ft_handle_hook(int keycode, t_player *p)
{
	if (keycode == 65361)
		ft_go_right(p);
	if (keycode == 65363)
		ft_go_left(p);
	if (keycode == 65364)
		ft_go_down(p);
	if (keycode == 65362)
		ft_go_up(p);
	if (keycode == 108)
		ft_turn_right(p);
	if (keycode == 114)
		ft_turn_left(p);
	if (keycode == K_ESC)
		exit(0);
	ft_refresh(p);
	return (0);
}
