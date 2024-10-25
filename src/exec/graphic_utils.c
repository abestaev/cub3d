/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:16:09 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/25 18:05:56 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_calc_dark(int color, double factor)
{
	return ((int)((color >> 16 & 0xFF) * factor) << 16)
		+ ((int)((color >> 8 & 0xFF) * factor) << 8) + (int)((color & 0xFF)
		* factor);
}
