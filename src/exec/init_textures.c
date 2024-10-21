/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:42:10 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/21 07:33:42 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_init_xpm(t_player *p, t_image *img, char *text_name)
{
	int	text_size;

	text_size = TEXTURE_SIZE;
	ft_memset(img, 0, sizeof(t_image));
	img->img = mlx_xpm_file_to_image(p->img->mlx, text_name, &text_size,
			&text_size);
	if (!img->img)
	{
		printf("Error, impossible to load texture.\n");
		exit(0);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	if (!img->addr)
	{
		printf("Error, no address\n");
		exit(0);
	}
}

int	*ft_get_texture_pxl(t_player *p, char *text_name)
{
	int		x;
	int		y;
	int		*text_buff;
	t_image	*img;

	img = malloc(sizeof(t_image));
	ft_init_xpm(p, img, text_name);
	text_buff = malloc(sizeof(int) * TEXTURE_SIZE * TEXTURE_SIZE);
	if (!text_buff)
		return (NULL);
	y = 0;
	while (y < TEXTURE_SIZE)
	{
		x = 0;
		while (x < TEXTURE_SIZE)
		{
			text_buff[y * TEXTURE_SIZE + x] = *(int *)(img->addr + (y
						* img->line_length + x * (img->bits_per_pixel / 8)));
			++x;
		}
		y++;
	}
	mlx_destroy_image(p->img->mlx, img->img);
	free(img);
	return (text_buff);
}

void	ft_init_doors_text(t_player *p)
{
	t_doors *doors = malloc(sizeof(t_doors));
	ft_memset(doors, 0, sizeof(t_doors));

	p->doors = doors;
	p->doors->text_doors = malloc(sizeof(int *) * 10);
	p->doors->text_doors[0] = ft_get_texture_pxl(p, "./textures/openning_gate_00.xpm");
	p->doors->text_doors[1] = ft_get_texture_pxl(p, "./textures/openning_gate_01.xpm");
	p->doors->text_doors[2] = ft_get_texture_pxl(p, "./textures/openning_gate_02.xpm");
	p->doors->text_doors[3] = ft_get_texture_pxl(p, "./textures/openning_gate_03.xpm");
	p->doors->text_doors[4] = ft_get_texture_pxl(p, "./textures/openning_gate_04.xpm");
	p->doors->text_doors[5] = ft_get_texture_pxl(p, "./textures/openning_gate_05.xpm");
	p->doors->text_doors[6] = ft_get_texture_pxl(p, "./textures/openning_gate_06.xpm");
	p->doors->text_doors[7] = ft_get_texture_pxl(p, "./textures/openning_gate_07.xpm");
	p->doors->text_doors[8] = ft_get_texture_pxl(p, "./textures/openning_gate_08.xpm");
	p->doors->text_doors[9] = NULL;
}

void	ft_init_wall_textures(t_player *p)
{
	p->texture = malloc(sizeof(int *) * 5);
	p->texture[0] = ft_get_texture_pxl(p, p->data->textures->north);
	p->texture[1] = ft_get_texture_pxl(p, p->data->textures->south);
	p->texture[2] = ft_get_texture_pxl(p, p->data->textures->east);
	p->texture[3] = ft_get_texture_pxl(p, p->data->textures->west);
	p->texture[4] = NULL;
}

void ft_init_textures(t_player *p)
{
	ft_init_wall_textures(p);
	ft_init_doors_text(p);
}
