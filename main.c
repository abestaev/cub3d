/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:34:01 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/29 19:19:32 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_find_closest_door(t_player *p, t_sprite *all_elem)
{
	int	i;

	i = p->nb_door + p->nb_sprite - 1;
	while (i >= 0)
	{
		if (all_elem[i].type == DOOR)
			return (i);
		i--;
	}
	return (0);
}

/* The sprites are sorted from farthest to closest,
	so the last is always the closest to the player */
void	ft_handle_doors(t_player *p, t_sprite *all_elem)
{
	double			curr_time;
	static double	old_time = 0;
	int				i;

	i = ft_find_closest_door(p, all_elem);
	if (all_elem[i].door_state == IS_OPENING)
	{
		if (all_elem[i].animation_index < 5)
		{
			curr_time = ft_get_usec_time();
			if (curr_time - old_time > 100)
			{
				all_elem[i].animation_index++;
				old_time = curr_time;
			}
		}
		if (all_elem[i].animation_index == 5)
		{
			all_elem[i].door_state = OPEN;
			all_elem[i].animation_index = 0;
			old_time = 0;
		}
	}
}

int	ft_refresh(t_player *p)
{
	update_position(p);
	ft_sort_elem_by_dist(p, p->all_elem, p->nb_door + p->nb_sprite);
	ft_handle_doors(p, p->all_elem);
	ft_color_background(p->img);
	ft_raycast_walls(p);
	ft_raycast_elem(p);
	ft_minimap(p);
	mlx_put_image_to_window(p->img->mlx, p->img->win_ptr, p->img->img, 0, 0);
	return (0);
}

void	ft_free_all_struct(t_player *p)
{
	free(p->img);
	free(p->texture);
	free(p->data);
	// free_tab((void *)p->data->textures->doors);
	// free_tab((void *)p->texture);
	free(p);
}

void	update_position(t_player *p)
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

int	mouse_move(int w, int h, t_player *p)
{
	double	x;
	double	y;
	double	angle;

	x = h;
	x = p->p_dir_x;
	y = p->p_dir_y;
	angle = (ROT_SPEED / MOUSE_SPEED * (S_WIDTH / 2 - w)) * -1;
	p->p_dir_x = (x * cos(angle) - y * sin(angle));
	p->p_dir_y = (x * sin(angle) + y * cos(angle));
	x = p->plane_x;
	y = p->plane_y;
	p->plane_x = (x * cos(angle) - y * sin(angle));
	p->plane_y = (x * sin(angle) + y * cos(angle));
	mlx_mouse_move(p->img->mlx, p->img->win_ptr, S_WIDTH / 2, S_HEIGHT / 2);
	return (0);
}

int	ft_count_door(char **map)
{
	int	y;
	int	x;
	int	size;

	size = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P')
				size++;
			x++;
		}
		y++;
	}
	return (size);
}

int	ft_count_sprite(char **map)
{
	int	y;
	int	x;
	int	size;

	size = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'V')
				size++;
			x++;
		}
		y++;
	}
	return (size);
}

void	ft_init_maps_door(t_player *p)
{
	t_sprite	*door;
	int			y;
	int			x;
	int			i;

	door = calloc(sizeof(t_sprite), ft_count_door(p->map));
	p->door = door;
	p->nb_door = ft_count_door(p->map);
	i = 0;
	y = 0;
	while (p->map[y])
	{
		x = 0;
		while (p->map[y][x])
		{
			if (p->map[y][x] == 'P')
			{
				p->door[i].type = DOOR;
				p->door[i].door_state = CLOSE;
				p->door[i].pos.x = x;
				p->door[i].pos.y = y;
				i++;
			}
			x++;
		}
		y++;
	}
}

void	ft_init_maps_sprite(t_player *p)
{
	int	y;
	int	x;
	int	i;

	p->sprite = calloc(sizeof(t_sprite), ft_count_sprite(p->map));
	p->nb_sprite = ft_count_sprite(p->map);
	i = 0;
	y = 0;
	while (p->map[y])
	{
		x = 0;
		while (p->map[y][x])
		{
			if (p->map[y][x] == 'V')
			{
				p->sprite[i].type = SPRITE;
				p->sprite[i].pos.x = x + 0.5;
				p->sprite[i].pos.y = y + 0.5;
				i++;
			}
			x++;
		}
		y++;
	}
}

void	ft_init_elements(t_player *p)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	ft_init_maps_door(p);
	ft_init_maps_sprite(p);
	p->all_elem = ft_calloc(p->nb_sprite + p->nb_door + 1, sizeof(t_sprite));
	while (j < p->nb_door)
	{
		p->all_elem[i] = p->door[j];
		j++;
		i++;
	}
	j = 0;
	while (j < p->nb_sprite)
	{
		p->all_elem[i] = p->sprite[j];
		j++;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_player	*p;
	t_data		*data;
	t_textures	*textures;

	p = malloc(sizeof(t_player));
	if (!p)
		return (-1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (-1);
	textures = malloc(sizeof(t_textures));
	if (!textures)
		return (-1);
	ft_memset(p, 0, sizeof(t_player));
	ft_memset(textures, 0, sizeof(t_textures));
	data->textures = textures;
	if (parsing(argc, argv, data))
		return (1);
	ft_player_init(p, data);
	ft_mlx_init(p);
	ft_init_elements(p);
	ft_init_textures(p);
	mlx_mouse_hide(p->img->mlx, p->img->win_ptr);
	mlx_hook(p->img->win_ptr, 2, 1L << 0, key_press, p);
	mlx_hook(p->img->win_ptr, 3, 1L << 1, key_release, p);
	mlx_hook(p->img->win_ptr, 6, 1L << 6, mouse_move, p);
	mlx_loop_hook(p->img->mlx, ft_refresh, p); // Appelle en boucle main_loop
	mlx_loop(p->img->mlx);
	mlx_destroy_display(p->img->mlx);
	return (0);
}
