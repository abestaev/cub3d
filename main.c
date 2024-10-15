/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albestae <albestae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:34:01 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/15 13:32:21 by albestae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_refresh(t_player *p)
{
	ft_clear_image(p->img, COLOR_DARK_GRAY);
	ft_cast_ray(p);
	mlx_put_image_to_window(p->img->mlx, p->img->win_ptr, p->img->img, 0, 0);
	// ft_minimap_render(p, p->map);
	// ft_player_render(p);
}

void	ft_free_all_struct(t_player *p)
{
	free(p->img);
	free(p->ray);
	free(p->mini);
	free(p);
}

void update_position(t_player *p)
{
    if (p->move_forward)
        ft_go_up(p);
    if (p->move_backward)
        ft_go_down(p);
    if (p->move_left)
        ft_go_right(p);
    if (p->move_right)
		ft_go_left(p);
    if (p->rotate_left)
		ft_turn_right(p);
    if (p->rotate_right)
       ft_turn_left(p);
}

int	ft_cub_render(t_player *p)
{
	update_position(p);
	ft_refresh(p);
	return (0);
}

int	main(int argc, char **argv)
{
	t_player	*p;
	t_data		data;

	p = malloc(sizeof(t_player));
	if (!p)
		return (-1);
	ft_memset(p, 0, sizeof(t_player));
	if (parsing(argc, argv, &data.textures, &data))
		return (1);
	ft_player_init(p, &data);
	ft_mlx_init(p);
	ft_init_textures(p);
	// ft_refresh(p);
	mlx_hook(p->img->win_ptr, 2, 1L << 0, key_press, p);
	mlx_hook(p->img->win_ptr, 3, 1L << 1, key_release, p);
	mlx_hook(p->img->win_ptr, 33, 1L << 17, &ft_escape, p);
	mlx_loop_hook(p->img->mlx, ft_cub_render, p);  // Appelle en boucle main_loop
    mlx_loop(p->img->mlx);
	ft_free_all_struct(p);
	free_parsing(&data.textures, &data);
	return (0);
}
