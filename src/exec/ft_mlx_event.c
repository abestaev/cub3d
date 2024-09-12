/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:02:59 by melmarti          #+#    #+#             */
/*   Updated: 2024/09/12 19:10:49 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_go_up(t_player *p)
{
	p->p_y -= 10;
}
void	ft_go_down(t_player *p)
{
	p->p_y += 10;
}

void	ft_go_right(t_player *p)
{
	p->p_x += 10;
}

void	ft_go_left(t_player *p)
{
	p->p_x -= 10;
}

void	ft_turn_right(t_player *p)
{
	p->p_angl -= 0.1;
	if (p->p_angl < 0)
		p->p_angl = 0;
	p->p_dir_x = cos(p->p_angl * 5);
	p->p_dir_y = sin(p->p_angl * 5);
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
	if (keycode == 115)
		ft_turn_right(p);
	// if (keycode == 110)
	// 	ft_turn_left(p);
	ft_cub_render(p);
	return (0);
}