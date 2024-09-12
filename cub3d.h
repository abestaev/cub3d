#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "mlx/mlx.h"
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct textures
{
	int			fd;
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	char		*floor;
	char		*ceiling;
	char		*map_str_tmp;
	char		**map_tab_tmp;
}				t_textures;

typedef struct s_image
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_image;

typedef struct s_data
{
	char		**map;
	t_image		img;
	t_textures	textures;
}				t_data;

void			my_pixel_put(t_image *img, int x, int y, int color);

// PARSING FUNCTIONS
int				parsing(int argc, char **argv, t_textures *textures);//t_data *data);
int				arg_valid(int argc, char **argv);
int				read_file(t_textures *textures);
int				parse_line(char *str, t_textures *textures);
int				compare_texture_line(char *s1, char *s2, t_textures *textures);

int				get_map_line(char *str, t_textures *textures);
int				parse_map(t_textures *textures); //, t_data *data);
void			free_tab(char **tab);

// debug functions
void			print_map(char **map);

#endif