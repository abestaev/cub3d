#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

#define PI 3.1415926535897
#define TILE_SIZE 1

typedef struct s_player
{
	double p_x;
	double p_y;

}			t_player;

typedef struct s_ray
{
	float	ray_angle;
}			t_ray;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_image;

void		my_pixel_put(t_data *data, int x, int y, int color);

#endif