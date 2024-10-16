/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:42:10 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/15 18:30:11 by melmarti         ###   ########.fr       */
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
		return ;
	}
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	if (!img->addr)
		printf("Error, no address\n");
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
			text_buff[y * TEXTURE_SIZE + x] = *(int *)(img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8)));
			++x;
		}
		y++;
	}
	mlx_destroy_image(p->img->mlx, img->img);
	free(img);
	return (text_buff);
}

void	ft_init_textures(t_player *p)
{
	p->texture = malloc(sizeof(int *) * 5);
	p->texture[0] = ft_get_texture_pxl(p, "./textures/mur.xpm");
	p->texture[1] = ft_get_texture_pxl(p, "./textures/tonneaux.xpm");
	p->texture[2] = ft_get_texture_pxl(p, "./textures/os.xpm");
	p->texture[3] = ft_get_texture_pxl(p, "./textures/red.xpm");
	p->texture[4] = NULL;
}
