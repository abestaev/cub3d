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
	int			floor_r;
	int			floor_g;
	int			floor_b;
	int			ceiling_r;
	int			ceiling_g;
	int			ceiling_b;
	char		*map_str_tmp;
	char		**map_tab_tmp;
	size_t		longest_line;
	int			nb_lines;
	int			i;
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
int				parsing(int argc, char **argv, t_textures *textures,
					t_data *data);
int				arg_valid(int argc, char **argv);
int				read_file(t_textures *textures);
int				parse_line(char *str, t_textures *textures);
int				compare_texture_line(char *s1, char *s2, t_textures *textures);
int				get_map_line(char *str, t_textures *textures);
int				parse_map(t_textures *textures, t_data *data);
void			free_tab(char **tab);
void			ft_strcpy(char *dest, const char *src);
int				copy_and_check_walls(t_textures *textures, t_data *data);
int				invalid_char(t_textures *textures);
int				map_size(t_textures *textures);
int				is_map_open(t_data *data, t_textures *textures);
int				is_surrounded(int i, int j, t_data *data);
int				check_top_bottom(t_data *data, t_textures *textures);
int				check_sides(t_data *data, t_textures *textures);
int				is_image_png(char *path);
int				missing_textures(t_textures *textures);
int				parse_rgb(t_textures *textures);
int				isplayer(char c);
void			free_parsing(t_textures *textures, t_data *data);

// debug functions
void			print_map(char **map);

#endif