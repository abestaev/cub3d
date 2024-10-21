/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:24:02 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/21 16:21:46 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

long	ft_get_usec_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_print_fps(t_data *data)
{
	if (data->actual_time - data->old_time >= 1)
	{
		printf("%ld fps\n", data->fps / (data->actual_time - data->old_time));
		data->old_time = data->actual_time;
		data->fps = 0;
	}
}
