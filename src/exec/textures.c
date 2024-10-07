/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renard <renard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:42:10 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/05 13:51:01 by renard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	*ft_get_north_textures(t_player *p)
{
	int		*text;
	int		text_height;
	int		text_width;
	void	*img;
	char	*img_addr;
	int		i;

	text = malloc(sizeof(int) * TEXTURE_WIDTH * TEXTURE_HEIGHT);
	if (!text)
		return (NULL);
	text_height = TEXTURE_HEIGHT;
	text_width = TEXTURE_WIDTH;
	img = mlx_xpm_file_to_image(p->img->mlx, "textures/red.xpm", &text_width,
			&text_height);
	if (!img)
	{
		printf("Erreur : impossible de charger la texture.\n");
		free(text);
		return (NULL);
	}
	img_addr = mlx_get_data_addr(img, &p->img->bits_per_pixel,
			&p->img->line_length, &p->img->endian);
	i = 0;
	while (i < TEXTURE_SIZE)
	{
		text[i] = *(int *)&img_addr[i * (p->img->bits_per_pixel / 8)];
		i++;
	}
	mlx_destroy_image(p->img->mlx, img);
	return (text);
}

int	*ft_get_south_textures(t_player *p)
{
	int		*text;
	int		text_height;
	int		text_width;
	void	*img;
	char	*img_addr;
	int		i;

	text = malloc(sizeof(int) * TEXTURE_WIDTH * TEXTURE_HEIGHT);
	if (!text)
		return (NULL);
	text_height = TEXTURE_HEIGHT;
	text_width = TEXTURE_WIDTH;
	img = mlx_xpm_file_to_image(p->img->mlx, "textures/purplestone.xpm",
			&text_width, &text_height);
	if (!img)
	{
		printf("Erreur : impossible de charger la texture.\n");
		free(text);
		return (NULL);
	}
	img_addr = mlx_get_data_addr(img, &p->img->bits_per_pixel,
			&p->img->line_length, &p->img->endian);
	i = 0;
	while (i < TEXTURE_SIZE)
	{
		text[i] = *(int *)&img_addr[i * (p->img->bits_per_pixel / 8)];
		i++;
	}
	mlx_destroy_image(p->img->mlx, img);
	return (text);
}

int	*ft_get_west_textures(t_player *p)
{
	int		*text;
	int		text_height;
	int		text_width;
	void	*img;
	char	*img_addr;
	int		i;

	text = malloc(sizeof(int) * TEXTURE_WIDTH * TEXTURE_HEIGHT);
	if (!text)
		return (NULL);
	text_height = TEXTURE_HEIGHT;
	text_width = TEXTURE_WIDTH;
	img = mlx_xpm_file_to_image(p->img->mlx, "textures/eagle.xpm", &text_width,
			&text_height);
	if (!img)
	{
		free(text);
		printf("Erreur : impossible de charger la texture.\n");
		return (NULL);
	}
	img_addr = mlx_get_data_addr(img, &p->img->bits_per_pixel,
			&p->img->line_length, &p->img->endian);
	i = 0;
	while (i < TEXTURE_SIZE)
	{
		text[i] = *(int *)&img_addr[i * (p->img->bits_per_pixel / 8)];
		i++;
	}
	mlx_destroy_image(p->img->mlx, img);
	return (text);
}

int	*ft_get_east_textures(t_player *p)
{
	int		*text;
	int		text_height;
	int		text_width;
	void	*img;
	char	*img_addr;
	int		i;

	text = malloc(sizeof(int) * TEXTURE_WIDTH * TEXTURE_HEIGHT);
	if (!text)
		return (NULL);
	text_height = TEXTURE_HEIGHT;
	text_width = TEXTURE_WIDTH;
	img = mlx_xpm_file_to_image(p->img->mlx, "textures/greystone.xpm",
			&text_width, &text_height);
	if (!img)
	{
		printf("Erreur : impossible de charger la texture.\n");
		free(text);
		return (NULL);
	}
	img_addr = mlx_get_data_addr(img, &p->img->bits_per_pixel,
			&p->img->line_length, &p->img->endian);
	i = 0;
	while (i < TEXTURE_SIZE)
	{
		text[i] = *(int *)&img_addr[i * (p->img->bits_per_pixel / 8)];
		i++;
	}
	mlx_destroy_image(p->img->mlx, img);
	return (text);
}

void	ft_init_textures(t_player *p)
{
	int	**texture;

	texture = malloc(sizeof(int *) * 5);
	// int	i;
	// int	j;
	texture[0] = ft_get_north_textures(p);
	texture[1] = ft_get_south_textures(p);
	texture[2] = ft_get_west_textures(p);
	texture[3] = ft_get_east_textures(p);
	texture[4] = NULL;
	p->text_buff = texture;
	// i = 0;
	// while (i < 4)
	// {
	// 	j = 0;
	// 	while (texture[i][j])
	// 	{
	// 		printf("num = %d\n", texture[i][j]);
	// 		j++;
	// 	}
	// 	i++;
	// }
}
