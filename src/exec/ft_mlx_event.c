
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


int	ft_is_in_adjacent_cells(t_player *p, int x, int y, char c)
{
	if (p->map[y][x + 1] == c || p->map[y][x - 1] == c || p->map[y + 1][x] == c
		|| p->map[y - 1][x] == c)
		return (1);
	return (0);
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
		i = ft_find_closest_door(p, p->all_elem);
		if (p->all_elem[i].door_state == CLOSE)
			p->all_elem[i].door_state = IS_OPENING;
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

int	mouse_move(int w, int h, t_player *p)
{
	double	x;
	double	y;
	double	angle;

	x = h;
	x = p->p_dir_x;
	y = p->p_dir_y;
	angle = (ROT_SPEED / MOUSE_SPEED * (S_WIDTH / 2 - w)) * -1;
	p->p_dir_x = (x * cos(angle) - y * sin(angle));
	p->p_dir_y = (x * sin(angle) + y * cos(angle));
	x = p->plane_x;
	y = p->plane_y;
	p->plane_x = (x * cos(angle) - y * sin(angle));
	p->plane_y = (x * sin(angle) + y * cos(angle));
	mlx_mouse_move(p->img->mlx, p->img->win_ptr, S_WIDTH / 2, S_HEIGHT / 2);
	return (0);
}
void	ft_mlx_events(t_player *p)
{
	mlx_hook(p->img->win_ptr, 33, 1L << 17, &ft_escape, p);
	// mlx_mouse_hide(p->img->mlx, p->img->win_ptr);
	mlx_hook(p->img->win_ptr, 2, 1L << 0, key_press, p);
	mlx_hook(p->img->win_ptr, 3, 1L << 1, key_release, p);
	mlx_hook(p->img->win_ptr, 6, 1L << 6, mouse_move, p);
	mlx_loop_hook(p->img->mlx, ft_refresh, p); // Appelle en boucle main_loop
	mlx_loop(p->img->mlx);
}
