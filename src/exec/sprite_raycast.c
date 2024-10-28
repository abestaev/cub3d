/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_raycast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmarti <melmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:09:18 by melmarti          #+#    #+#             */
/*   Updated: 2024/10/28 20:01:41 by melmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_calcul_sprite(t_player *p, t_spriteray *sprite_ray, t_sprite *sprite)
{
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
	//printf("sprite_trans.y=%f\n", sprite_ray->trans.y);
	sprite_ray->sprite_height = fabs((S_HEIGHT / (sprite_ray->trans.y))) / 4;
	sprite_ray->draw_start.y = -sprite_ray->sprite_height / 2 + S_HEIGHT / 2;
	if (sprite_ray->draw_start.y < 0)
		sprite_ray->draw_start.y = 0;
	sprite_ray->draw_end.y = sprite_ray->sprite_height / 2 + S_HEIGHT / 2;
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

void	ft_draw_sprites(t_player *p, t_spriteray *sprite_ray)
{
	int x;
	int d;
	int y;

	x = sprite_ray->draw_start.x - 1;
	//printf("start = %f\n", sprite_ray->draw_start.x);
	//printf("end = %f\n", sprite_ray->draw_end.x);
	while (++x < sprite_ray->draw_end.x)
	{
		y = sprite_ray->draw_start.y - 1;
		sprite_ray->tex.x = (int)(256 * (x - (-sprite_ray->sprite_width / 2
						+ sprite_ray->screen_x)) * SPRITE_TEXT_SIZE
				/ sprite_ray->sprite_width) / 256;
		if (sprite_ray->trans.y > 0 && x > 0 && x < S_WIDTH
			&&  sprite_ray->trans.y < p->ray->dist_buffer[x])
		{
			while (++y < sprite_ray->draw_end.y)
			{
				d = y * 256 - S_HEIGHT * 128 + sprite_ray->sprite_height * 128;
				sprite_ray->tex.y = ((d * SPRITE_TEXT_SIZE) / sprite_ray->sprite_height) / 256;
				int color = p->sprite_text[0][(int)(SPRITE_TEXT_SIZE * sprite_ray->tex.y + sprite_ray->tex.x)];
				if ((color & 0x00FFFFFF) != 0)
					my_pixel_put(p->img, x, y, color);
			}
		}
	}
}