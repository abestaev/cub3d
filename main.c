/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:34:01 by melmarti          #+#    #+#             */
/*   Updated: 2024/09/12 19:28:32 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_mlx_init()
{
	void *mlx; 
	void *mlx_win;
	t_image img;
	
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Cub3D");
	mlx_loop(mlx);
	img.addr =  mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
}

int	main(int argc, char **argv)
{
	t_data data;
	//ft_mlx_init();
	if (parsing(argc, argv, &data.textures))
		return (1);
	return (0);
}

