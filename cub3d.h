#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "mlx/mlx.h"
# include <math.h>
# include <X11/Xlib.h>
# include <X11/Xutil.h>
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define PI 3.1415926535897
# define S_WIDTH 1000
# define S_HEIGHT 600
# define FOV 60
# define K_Left 65361  /* Move left, left arrow */
# define K_Up 65362    /* Move up, up arrow */
# define K_Right 65363 /* Move right, right arrow */
# define K_Down 65364  /* Move down, down arrow */

typedef struct s_player
{
	double			p_x;
	double			p_y;
	double			p_angl;
	double			p_dir_x;
	double			p_dir_y;
	struct s_image	*img;

}					t_player;

typedef struct s_ray
{
	float			ray_angle;
}					t_ray;

typedef struct textures
{
	int				fd;
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	int				floor;
	int				ceiling;
}					t_textures;

typedef struct s_image
{
	void			*mlx;
	void			*img;
	void			*win_ptr;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	t_player		*p;
}					t_image;

typedef struct s_data
{
	t_image			img;
	t_textures		textures;
}					t_data;

// EXEC FUNCTIONS
void				my_pixel_put(t_image *img, int x, int y, int color);
int					ft_handle_hook(int keycode, t_player *p);
// int					ft_exit(void *param);
int					ft_count_columns(char **map);
int					ft_count_lines(char **map);
int					ft_resize_tiles(char **map);
void				ft_draw_tile(t_image *img, int start_x, int start_y,
						int size, int color);
void				ft_cub_render(t_player *p);
void				ft_clear_image(t_image *img, int color);

// PARSING FUNCTIONS
int					parsing(int argc, char **argv, t_textures *textures);
int					arg_valid(int argc, char **argv);

#endif