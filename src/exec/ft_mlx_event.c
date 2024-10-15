
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
	if (!ft_inside_wall(p, p->p_x - p->p_dir_x * p->plr_speed, p->p_y))
		p->p_x -= p->p_dir_x * p->plr_speed;
	if (!ft_inside_wall(p, p->p_x, p->p_y - p->p_dir_y * p->plr_speed))
		p->p_y -= p->p_dir_y * p->plr_speed;
}

void	ft_go_up(t_player *p)
{
	if (!ft_inside_wall(p, p->p_x + p->p_dir_x * p->plr_speed, p->p_y))
		p->p_x += p->p_dir_x * p->plr_speed;
	if (!ft_inside_wall(p, p->p_x, p->p_y + p->p_dir_y * p->plr_speed))
		p->p_y += p->p_dir_y * p->plr_speed;
}

void	ft_go_right(t_player *p)
{
	double	perp_dir_x;
	double	perp_dir_y;

	perp_dir_x = p->p_dir_y;
	perp_dir_y = -p->p_dir_x;
	if (!ft_inside_wall(p, p->p_x + perp_dir_x * p->plr_speed, p->p_y))
		p->p_x += perp_dir_x * p->plr_speed;
	if (!ft_inside_wall(p, p->p_x, p->p_y + perp_dir_y * p->plr_speed))
		p->p_y += perp_dir_y * p->plr_speed;
}

void	ft_go_left(t_player *p)
{
	double	perp_dir_x;
	double	perp_dir_y;

	perp_dir_x = -p->p_dir_y;
	perp_dir_y = p->p_dir_x;
	if (!ft_inside_wall(p, p->p_x + perp_dir_x * p->plr_speed, p->p_y))
		p->p_x += perp_dir_x * p->plr_speed;
	if (!ft_inside_wall(p, p->p_x, p->p_y + perp_dir_y * p->plr_speed))
		p->p_y += perp_dir_y * p->plr_speed;
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

int key_press(int keycode, t_player *p)
{
	if (keycode == K_ESC)
		exit(0);
    if (keycode == K_UP)
        p->move_forward = 1;
    if (keycode == K_DOWN)
        p->move_backward = 1;
    if (keycode == K_LEFT)
        p->move_left = 1;
    if (keycode == K_RIGHT)
        p->move_right = 1;
    if (keycode == K_LOOK_LEFT)
        p->rotate_left = 1;
    if (keycode == K_LOOK_RIGHT)
        p->rotate_right = 1;
    return (0);
}

int key_release(int keycode, t_player *p)
{
    if (keycode == K_UP)
        p->move_forward = 0;
    if (keycode == K_DOWN)
        p->move_backward = 0;
    if (keycode == K_LEFT)
        p->move_left = 0;
    if (keycode == K_RIGHT)
        p->move_right = 0;
    if (keycode == K_LOOK_LEFT)
        p->rotate_left = 0;
    if (keycode == K_LOOK_RIGHT)
        p->rotate_right = 0;
    return (0);
}
