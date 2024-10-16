/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:24:02 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/16 17:09:08 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

long	ft_get_sec_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec);
}

void	ft_print_fps(t_data *data)
{
	if (data->actual_time - data->old_time >= 1)
	{
		// printf("%ld fps\n", data->fps / (data->actual_time - data->old_time));
		data->old_time = data->actual_time;
		data->fps = 0;
	}
}
