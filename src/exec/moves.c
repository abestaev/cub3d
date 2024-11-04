/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:35:17 by melmarti          #+#    #+#             */
/*   Updated: 2024/11/04 15:55:59 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	ft_go_right(t_player *p)
{
	double	perp_dir_x;
	double	perp_dir_y;
	double	new_x;
	double	new_y;

	perp_dir_x = p->p_dir_y;
	perp_dir_y = -p->p_dir_x;
	new_x = p->pos.x + perp_dir_x * p->plr_speed;
	new_y = p->pos.y + perp_dir_y * p->plr_speed;
	if (!hit_box(p, new_x, p->pos.y))
		p->pos.x = new_x;
	if (!hit_box(p, p->pos.x, new_y))
		p->pos.y = new_y;
}

void	ft_go_left(t_player *p)
{
	double	perp_dir_x;
	double	perp_dir_y;
	double	new_x;
	double	new_y;

	perp_dir_x = -p->p_dir_y;
	perp_dir_y = p->p_dir_x;
	new_x = p->pos.x + perp_dir_x * p->plr_speed;
	new_y = p->pos.y + perp_dir_y * p->plr_speed;
	if (!hit_box(p, new_x, p->pos.y))
		p->pos.x = new_x;
	if (!hit_box(p, p->pos.x, new_y))
		p->pos.y = new_y;
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

void	update_position(t_player *p)
{
	if (p->move_forward)
		ft_go_up(p);
	if (p->move_backward)
		ft_go_down(p);
	if (p->move_left)
		ft_go_right(p);
	if (p->move_right)
		ft_go_left(p);
	if (p->rotate_left)
		ft_turn_right(p);
	if (p->rotate_right)
		ft_turn_left(p);
}
