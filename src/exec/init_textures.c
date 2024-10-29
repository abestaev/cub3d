/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:42:10 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/29 14:27:45 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_init_xpm(t_player *p, t_image *img, char *text_name)
{
	int	text_size;

	text_size = WALL_TEXT_SIZE;
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

int	*ft_get_texture_pxl(t_player *p, char *text_name, int size)
{
	int		x;
	int		y;
	int		*text_buff;
	t_image	*img;

	img = malloc(sizeof(t_image));
	ft_init_xpm(p, img, text_name);
	text_buff = malloc(sizeof(int) * size * size);
	if (!text_buff)
		return (NULL);
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			text_buff[y * size + x] = *(int *)(img->addr + (y * img->line_length
						+ x * (img->bits_per_pixel / 8)));
			++x;
		}
		y++;
	}
	mlx_destroy_image(p->img->mlx, img->img);
	free(img);
	return (text_buff);
}

int	**ft_init_doors_text(t_player *p)
{
	int	**text;

	text = malloc(sizeof(int *) * 7);
	text[0] = ft_get_texture_pxl(p, "./textures/doorframe_1.xpm",
			DOOR_TEXT_SIZE);
	text[1] = ft_get_texture_pxl(p, "./textures/doorframe_2.xpm",
			DOOR_TEXT_SIZE);
	text[2] = ft_get_texture_pxl(p, "./textures/doorframe_3.xpm",
			DOOR_TEXT_SIZE);
	text[3] = ft_get_texture_pxl(p, "./textures/doorframe_4.xpm",
			DOOR_TEXT_SIZE);
	text[4] = ft_get_texture_pxl(p, "./textures/doorframe_5.xpm",
			DOOR_TEXT_SIZE);
	text[5] = ft_get_texture_pxl(p, "./textures/doorframe_6.xpm",
			DOOR_TEXT_SIZE);
	text[6] = NULL;
	return (text);
}

void	ft_init_wall_textures(t_player *p)
{
	p->texture = malloc(sizeof(int *) * 5);
	p->texture[0] = ft_get_texture_pxl(p, p->data->textures->north,
			WALL_TEXT_SIZE);
	p->texture[1] = ft_get_texture_pxl(p, p->data->textures->south,
			WALL_TEXT_SIZE);
	p->texture[2] = ft_get_texture_pxl(p, p->data->textures->east,
			WALL_TEXT_SIZE);
	p->texture[3] = ft_get_texture_pxl(p, p->data->textures->west,
			WALL_TEXT_SIZE);
	p->texture[4] = NULL;
}

int	**ft_init_sprite_text(t_player *p)
{
	int	**text;

	text = malloc(sizeof(int *) * 7);
	text[0] = ft_get_texture_pxl(p, "./textures/candle_1.xpm",
			SPRITE_TEXT_SIZE);
	text[1] = ft_get_texture_pxl(p, "./textures/candle_2.xpm",
			SPRITE_TEXT_SIZE);
	text[2] = ft_get_texture_pxl(p, "./textures/candle_3.xpm",
			SPRITE_TEXT_SIZE);
	text[3] = ft_get_texture_pxl(p, "./textures/candle_4.xpm",
			SPRITE_TEXT_SIZE);
	text[4] = ft_get_texture_pxl(p, "./textures/candle_5.xpm",
			SPRITE_TEXT_SIZE);
	text[5] = ft_get_texture_pxl(p, "./textures/candle_6.xpm",
			SPRITE_TEXT_SIZE);
	text[6] = NULL;
	return (text);
}

void	ft_init_textures(t_player *p)
{
	ft_init_wall_textures(p);
	p->sprite_text = ft_init_sprite_text(p);
	p->door_text = ft_init_doors_text(p);
}
