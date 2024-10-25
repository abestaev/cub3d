
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

int	is_in_wall(t_player *p, double x, double y)
{
	return (ft_colision(p, x - HITBOX_SIZE, y - HITBOX_SIZE) || ft_colision(p, x
			+ HITBOX_SIZE, y - HITBOX_SIZE) || ft_colision(p, x - HITBOX_SIZE, y
			+ HITBOX_SIZE) || ft_colision(p, x + HITBOX_SIZE, y + HITBOX_SIZE));
}

void	ft_go_down(t_player *p)
{
	double	new_x;
	double	new_y;

	new_x = p->pos.x - p->p_dir_x * p->plr_speed;
	new_y = p->pos.y - p->p_dir_y * p->plr_speed;
	if (!is_in_wall(p, new_x, p->pos.y))
		p->pos.x = new_x;
	if (!is_in_wall(p, p->pos.x, new_y))
		p->pos.y = new_y;
}

void	ft_go_up(t_player *p)
{
	double	new_x;
	double	new_y;

	new_x = p->pos.x + p->p_dir_x * p->plr_speed;
	new_y = p->pos.y + p->p_dir_y * p->plr_speed;
	if (!is_in_wall(p, new_x, p->pos.y))
		p->pos.x = new_x;
	if (!is_in_wall(p, p->pos.x, new_y))
		p->pos.y = new_y;
}

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
	if (!is_in_wall(p, new_x, p->pos.y))
		p->pos.x = new_x;
	if (!is_in_wall(p, p->pos.x, new_y))
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
	if (!is_in_wall(p, new_x, p->pos.y))
		p->pos.x = new_x;
	if (!is_in_wall(p, p->pos.x, new_y))
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

int	ft_is_in_adjacent_cells(t_player *p, int x, int y, char c)
{
	if (p->map[y][x + 1] == c || p->map[y][x - 1] == c || p->map[y + 1][x] == c
		|| p->map[y - 1][x] == c)
		return (1);
	return (0);
}
int	ft_get_door_id(t_player *p, int y, int x)
{
	int	i;

	i = 0;
	while (i < p->nb_sprite)
	{
		if (p->sprite[i].pos.x == x && p->sprite[i].pos.y == y)
			return (i);
		i++;
	}
	return (0);
}
// the flag allow me to find a door or a sprite whenever I start from the hit rays or from the relative position of the player,
// the 2 possibilities
int	ft_which_doors(t_player *p, int x, int y, char c, int flag)
{
	int	i;

	i = 0;
	if (flag)
		i = 1;
	if (p->map[y][x + i] == c)
		return (ft_get_door_id(p, y, x + i));
	if (p->map[y][x - i] == c)
		return (ft_get_door_id(p, y, x - i));
	if (p->map[y + i][x] == c)
		return (ft_get_door_id(p, y + i, x));
	if (p->map[y - i][x] == c)
		return (ft_get_door_id(p, y - i, x));
	return (ft_get_door_id(p, y, x));
}

int	key_press(int keycode, t_player *p)
{
	int	i;

	if (keycode == K_ESC)
		ft_escape(p);
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
	if (keycode == K_O && ft_is_in_adjacent_cells(p, p->pos.x, p->pos.y, 'P'))
	{
		i = ft_which_doors(p, p->pos.x, p->pos.y, 'P', 1);
		if (p->sprite[i].door_state == CLOSE)
			p->sprite[i].door_state = IS_OPENING;
	}
	return (0);
}

int	key_release(int keycode, t_player *p)
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
