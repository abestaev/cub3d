#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

void		my_pixel_put(t_data *data, int x, int y, int color);

#endif