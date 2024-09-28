#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "mlx/mlx.h"
# include <X11/Xlib.h>
# include <X11/Xutil.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define COLOR_BLACK 0x000000
# define COLOR_WHITE 0xFFFFFF
# define COLOR_RED 0xFF0000
# define COLOR_GREEN 0x00FF00
# define COLOR_BLUE 0x0000FF
# define COLOR_YELLOW 0xFFFF00
# define COLOR_CYAN 0x00FFFF
# define COLOR_MAGENTA 0xFF00FF05
# define COLOR_ORANGE 0xFFA500
# define COLOR_PURPLE 0x800080
# define COLOR_BROWN 0xA52A2A
# define COLOR_GRAY 0x808080
# define COLOR_LIGHT_GRAY 0xD3D3D3
# define COLOR_DARK_GRAY 0xA9A9A9
# define COLOR_PINK 0xFFC0CB
# define COLOR_LIME 0x00FF00

# define PI 3.1415926535897
# define S_WIDTH 1000
# define S_HEIGHT 1000
# define FOV 60
# define SPEED 0.15
# define K_Left 65361  /* Move left, left arrow */
# define K_Up 65362    /* Move up, up arrow */
# define K_Right 65363 /* Move right, right arrow */
# define K_Down 65364  /* Move down, down arrow */
# define ROT_SPEED 0.05

typedef struct s_rgba
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;

}					t_rgba;

typedef struct s_player
{
	double			p_x;
	double			p_y;
	double			p_angl;
	double			p_dir_x;
	double			p_dir_y;
	double			plane_x;
	double			plane_y;
	double			tile_size;
	double			plr_offset;
	double			plr_speed;
	double			speed_rot;
	char			**map;
	struct s_image	*img;
	struct s_data	*data;
	struct s_ray	*ray;

}					t_player;
typedef struct s_ray
{
	double			dir_x;
	double			dir_y;
	int				side;
	double			delta_dist_x;
	double			delta_dist_y;
	double			side_dist_x;
	double			side_dist_y;
	double			wall_x;
}					t_ray;

typedef struct s_minimap
{
	double			p_x;
	double			p_y;
	double			p_angl;
	double			p_dir_x;
	double			p_dir_y;
	double			plane_x;
	double			plane_y;
	double			tile_size;
	double			plr_offset;
	double			plr_speed;
	double			speed_rot;
	char			**map;

}					t_minimap;

typedef struct textures
{
	double			plyr_pos_x;
	double			plyr_pos_y;
	int				fd;
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			*floor;
	char			*ceiling;
	int				floor_r;
	int				floor_g;
	int				floor_b;
	int				ceiling_r;
	int				ceiling_g;
	int				ceiling_b;
	char			*map_str_tmp;
	char			**map_tab_tmp;
	size_t			longest_line;
	int				nb_lines;
	int				i;
	struct s_player	*p;
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
	char			**map;
	t_image			img;
	t_textures		textures;
}					t_data;

// EXEC FUNCTIONS

// init

void				ft_player_render(t_player *p);
void				ft_map_render(t_player *p, char **map);
double				ft_norm_radian_angl(double radian);
double				ft_norm_deg_angl(double degrees);
void				ft_player_init(t_player *p, t_data *data);
t_image				*ft_mlx_init(void);
int					ft_inside_wall(t_player *p, int x, int y);
void				my_pixel_put(t_image *img, int x, int y, int color);
int					ft_handle_hook(int keycode, t_player *p);
// int					ft_exit(void *param);
void				ft_draw_line(int x_start, int y_start, int x_end, int y_end,
						t_image *img);
int					ft_count_columns(char **map);
int					ft_count_lines(char **map);
double				ft_get_tile_size(char **map);
void				ft_draw_tile(t_image *img, int start_x, int start_y,
						int size, int color);
void				ft_cub_render(t_player *p);
void				ft_clear_image(t_image *img, unsigned int color);
void				ft_refresh(t_player *p);
int					ft_est(t_player *p);
int					ft_ouest(t_player *p);
int					ft_north(t_player *p);
int					ft_south(t_player *p);
void				ft_get_wall_size(t_player *p, int x);
void				ft_draw_vertical_line(int x_val, int start, int end,
						t_image *img, long color);

// PARSING FUNCTIONS
int					parsing(int argc, char **argv, t_textures *textures,
						t_data *data);
int					arg_valid(int argc, char **argv);
int					read_file(t_textures *textures);
int					parse_line(char *str, t_textures *textures);
int					compare_texture_line(char *s1, char *s2,
						t_textures *textures);
int					get_map_line(char *str, t_textures *textures);
int					parse_map(t_textures *textures, t_data *data);
void				free_tab(char **tab);
void				ft_strcpy(char *dest, const char *src);
int					copy_and_check_walls(t_textures *textures, t_data *data);
int					invalid_char(t_textures *textures);
int					map_size(t_textures *textures);
int					is_map_open(t_data *data, t_textures *textures);
int					is_surrounded(int i, int j, t_data *data);
int					check_top_bottom(t_data *data, t_textures *textures);
int					check_sides(t_data *data, t_textures *textures);
int					is_image_png(char *path);
int					missing_textures(t_textures *textures);
int					parse_rgb(t_textures *textures);
int					isplayer(char c);
void				ft_init_player_orientation(char c, t_player *p);
void				free_parsing(t_textures *textures, t_data *data);

// debug functions
void				print_map(char **map);

#endif