/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orientation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:50:23 by melmarti          #+#    #+#             */
/*   Updated: 2024/09/23 14:58:22 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_south(t_player *p)
{
	if(p->p_angl >= ft_norm_deg_angl(45) && p->p_angl < ft_norm_deg_angl(135) && p->p_angl != ft_norm_deg_angl(90))
		return(1);
	return(0);
}

int ft_north(t_player *p)
{
	if(p->p_angl >= ft_norm_deg_angl(225) && p->p_angl < ft_norm_deg_angl(315))
		return(1);
	return(0);
}

int ft_est(t_player *p)
{
	if((p->p_angl >= ft_norm_deg_angl(0) && p->p_angl < ft_norm_deg_angl(45)) || (p->p_angl >= ft_norm_deg_angl(315) && p->p_angl < ft_norm_deg_angl(360)))
		return(1);
	return(0);
}

int ft_ouest(t_player *p)
{
	if(p->p_angl >= ft_norm_deg_angl(135) && p->p_angl < ft_norm_deg_angl(225))
		return(1);
	return(0);
}