/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:47:50 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/30 14:09:19 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_calcul_elem_dist(t_player *p, t_sprite *elem, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		elem[i].dist = pow(p->pos.x - elem[i].pos.x, 2) + pow(p->pos.y
				- elem[i].pos.y, 2);
		i++;
	}
}

void	ft_sort_elem_by_dist(t_player *p, t_sprite *elem, int nb)
{
	int			i;
	int			j;
	t_sprite	tmp;

	ft_calcul_elem_dist(p, elem, nb);
	i = 0;
	while (i < nb)
	{
		j = 0;
		while (j < nb - 1)
		{
			if (elem[j].dist < elem[j + 1].dist)
			{
				tmp = elem[j];
				elem[j] = elem[j + 1];
				elem[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}
