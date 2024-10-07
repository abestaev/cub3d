/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:42:10 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/07 18:38:14 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_get_texture_img(t_player *p, t_image *img, char *text_name)
{
	int	text_size;

	text_size = TEXTURE_SIZE;
	ft_memset(img, 0, sizeof(t_image));
	img->img = mlx_xpm_file_to_image(p->img->mlx, text_name, &text_size,
			&text_size);
	if (!img->img)
	{
		printf("Erreur : impossible de charger la texture.\n");
		return ;
	}
	printf("image->pixel_bits %d\n", img->bits_per_pixel);
	printf("&image->size_line %ls\n", &img->line_length);
	printf("image->pixel_bits %ls\n", &img->endian);
	printf("image->endia %p\n\n", img->img);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	printf("img->addr %s\n", img->addr);
	if (!img->addr)
	{
		printf("no address\n");
	}
}
int	*ft_get_texture_pxl(t_player *p, char *text_name)
{
	int		x;
	int		y;
	int		*text_buff;
	t_image	*img;
	int		color;

	img = malloc(sizeof(t_image));
	ft_get_texture_img(p, img, text_name);
	text_buff = malloc(sizeof(int) * TEXTURE_SIZE * TEXTURE_SIZE);
	if (!text_buff || !img->addr)
		return (NULL);
	y = 0;
	while (y < TEXTURE_SIZE)
	{
		x = 0;
		while (x < TEXTURE_SIZE)
		{
			color = *(int *)(img->addr + (y * img->line_length + x
						* (img->bits_per_pixel / 8)));
			text_buff[y * TEXTURE_SIZE + x] = color;
			x++;
		}
		y++;
	}
	mlx_destroy_image(p->img->mlx, img->img);
	free(img);
	return (text_buff);
}

void	ft_init_textures(t_player *p)
{
	int	**texture;
	int	i;
	int	j;

	texture = malloc(sizeof(int *) * 5);
	p->data->textures.text_size = TEXTURE_SIZE;
	texture[0] = ft_get_texture_pxl(p, "./textures/eagle.xpm");
	texture[1] = ft_get_texture_pxl(p, "./textures/greystone.xpm");
	texture[2] = ft_get_texture_pxl(p, "./textures/purplestone.xpm");
	texture[3] = ft_get_texture_pxl(p, "./textures/red.xpm");
	texture[4] = NULL;
	p->texture = texture;
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (texture[i][j])
		{
			printf("num = %d\n", texture[i][j]);
			j++;
		}
		i++;
	}
}
