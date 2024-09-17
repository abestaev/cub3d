/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:02:59 by melmarti          #+#    #+#             */
/*   Updated: 2024/09/17 13:21:28 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_go_up(t_player *p)
{
	if (p->p_y >= 0 && p->p_y < S_HEIGHT)
		p->p_y -= 10;
}
void	ft_go_down(t_player *p)
{
	if (p->p_y >= 0 && p->p_y < S_HEIGHT)
		p->p_y += 10;
}

void	ft_go_right(t_player *p)
{
	if (p->p_x >= 0 && p->p_x < S_WIDTH)
		p->p_x += 10;
}

void	ft_go_left(t_player *p)
{
	if (p->p_x >= 0 && p->p_x < S_WIDTH)
		p->p_x -= 10;
}

void	ft_turn_right(t_player *p)
{
	p->p_angl += 0.1;
	if (p->p_angl > PI * 2)
		p->p_angl = 0;
	p->p_dir_x = p->p_x + 50 * cos(p->p_angl);
	p->p_dir_y = p->p_y + 50 * sin(p->p_angl);
}

void	ft_turn_left(t_player *p)
{
	p->p_angl -= 0.1;
	if (p->p_angl < 0)
		p->p_angl = PI * 2;
	p->p_dir_x = p->p_x + 50 * cos(p->p_angl);
	p->p_dir_y = p->p_y + 50 * sin(p->p_angl);
}

int	ft_handle_hook(int keycode, t_player *p)
{
	printf("%d\n", keycode);
	if (keycode == K_Left)
		ft_go_left(p);
	if (keycode == K_Right)
		ft_go_right(p);
	if (keycode == K_Down)
		ft_go_down(p);
	if (keycode == K_Up)
		ft_go_up(p);
	if (keycode == 114)
		ft_turn_right(p);
	if (keycode == 108)
	ft_turn_left(p);
	ft_refresh(p);
	return (0);
}