/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_raycast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:09:18 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/30 11:48:42 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
void	ft_calcul_sprite(t_player *p, t_spriteray *sprite_ray, t_sprite *sprite, int i)
{
	ft_hanle_sprite_animation(sprite, i * 20);
	sprite_ray->vMove = 400;
	sprite_ray->ray.x = sprite->pos.x - p->pos.x;
	sprite_ray->ray.y = sprite->pos.y - p->pos.y;
	sprite_ray->inv_det = 1.0 / (p->plane_x * p->p_dir_y - p->p_dir_x
			* p->plane_y);
	sprite_ray->trans.x = sprite_ray->inv_det * (p->p_dir_y * sprite_ray->ray.x
			- p->p_dir_x * sprite_ray->ray.y);
	sprite_ray->trans.y = sprite_ray->inv_det * (-p->plane_y * sprite_ray->ray.x
			+ p->plane_x * sprite_ray->ray.y);
	sprite_ray->screen_x = (int)((S_WIDTH / 2) * (1 + sprite_ray->trans.x
				/ sprite_ray->trans.y));
}

void	ft_calc_sprite_hight(t_spriteray *sprite_ray)
{
	sprite_ray->sprite_height = fabs((S_HEIGHT / (sprite_ray->trans.y))) / 4;
	sprite_ray->draw_start.y = -sprite_ray->sprite_height / 2 + S_HEIGHT / 2
		+ sprite_ray->vMovescreen;
	if (sprite_ray->draw_start.y < 0)
		sprite_ray->draw_start.y = 0;
	sprite_ray->draw_end.y = sprite_ray->sprite_height / 2 + S_HEIGHT / 2
		+ sprite_ray->vMovescreen;
	if (sprite_ray->draw_end.y >= S_HEIGHT)
		sprite_ray->draw_end.y = S_HEIGHT - 1;
	sprite_ray->sprite_width = fabs((S_HEIGHT / (sprite_ray->trans.y))) / 4;
	sprite_ray->draw_start.x = -sprite_ray->sprite_width / 2
		+ sprite_ray->screen_x;
	if (sprite_ray->draw_start.x < 0)
		sprite_ray->draw_start.x = 0;
	sprite_ray->draw_end.x = sprite_ray->sprite_width / 2
		+ sprite_ray->screen_x;
	if (sprite_ray->draw_end.x >= S_WIDTH)
		sprite_ray->draw_end.x = S_WIDTH - 1;
}

void	ft_draw_sprite_pxl(t_player *p, t_sprite *sprite,
		t_spriteray *sprite_ray, int y, int x)
{
	int	color;
	int	d;

	while (++y < sprite_ray->draw_end.y)
	{
		d = (y - sprite_ray->vMovescreen) * 256 - S_HEIGHT * 128
			+ sprite_ray->sprite_height * 128;
		sprite_ray->tex.y = ((d * SPRITE_TEXT_SIZE) / sprite_ray->sprite_height)
			/ 256;
		color = p->sprite_text[sprite->animation_index][(int)(SPRITE_TEXT_SIZE
				* sprite_ray->tex.y + sprite_ray->tex.x)];
		if (color > 0)
			my_pixel_put(p->img, x, y, color);
	}
}

void	ft_hanle_sprite_animation(t_sprite *sprite, int i)
{
	double			curr_time;

	curr_time = ft_get_usec_time();
	if (curr_time - sprite->old_time > 70 + i)
	{
		sprite->animation_index++;
		sprite->old_time = curr_time;
	}
	if (sprite->animation_index == 6)
		sprite->animation_index = 0;
}

void	ft_draw_sprites(t_player *p, t_spriteray *sprite_ray, t_sprite *sprite)
{
	int	x;
	int	y;

	sprite_ray->vMovescreen = (int)(sprite_ray->vMove / sprite_ray->trans.y);
	x = sprite_ray->draw_start.x + 5;
	while (++x < sprite_ray->draw_end.x)
	{
		y = sprite_ray->draw_start.y + 5;
		sprite_ray->tex.x = (int)(256 * (x - (-sprite_ray->sprite_width / 2
						+ sprite_ray->screen_x)) * SPRITE_TEXT_SIZE
				/ sprite_ray->sprite_width) / 256;
		if (sprite_ray->trans.y > 0 && x > 0 && x < S_WIDTH
			&& sprite_ray->trans.y < p->ray->dist_buffer[x])
			ft_draw_sprite_pxl(p, sprite, sprite_ray, y, x);
	}
}
