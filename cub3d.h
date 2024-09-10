#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft/libft.h"

typedef struct textures
{
	int	    fd;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		floor;
	int		ceiling;

}			t_textures;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_img;

typedef	struct s_data
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_textures	textures;
}				t_data;

void		my_pixel_put(t_img *img, int x, int y, int color);


// PARSING FUNCTIONS
int     parsing(int argc, char **argv, t_textures *textures);
int     arg_valid(int argc, char **argv);

#endif