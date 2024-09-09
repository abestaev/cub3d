/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:34:01 by melmarti          #+#    #+#             */
/*   Updated: 2024/09/09 19:02:44 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_mlx_init()
{
	void *mlx; 
	void *mlx_win;
	t_data img;
	
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Cub3d");
	mlx_loop(mlx);
	img.addr =  mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
}

int	main(void)
{
	ft_mlx_init();
	
}

