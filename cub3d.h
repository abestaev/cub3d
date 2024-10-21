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
# include <sys/time.h>
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

# define TEXTURE_SIZE 64
# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64

# define S_WIDTH 1920
# define S_HEIGHT 1040
# define SPEED 0.10
# define ROT_SPEED 0.03
# define MOUSE_SPEED 20
# define HITBOX_SIZE 0.1
# define K_LEFT 0x61  // 'a' key
# define K_UP 0x77    // 'w' key
# define K_RIGHT 0x64 // 'd' key
# define K_DOWN 0x73  // 's' key
# define K_ESC 0xFF1B // ESC key
# define K_O 0x6F     // 'o' key

# define K_LOOK_LEFT 0xFF51  // Left arrow key
# define K_LOOK_RIGHT 0xFF53 // Right arrow key

typedef struct s_rgba
{
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;
	unsigned char		a;

}						t_rgba;
typedef struct s_point
{
	double				x;
	double				y;
}						t_point;

typedef struct s_minimap
{
	t_point				pos;
	int					x_offset;
	int					y_offset;
	int					nb_tile;
	int					tile_size;

}						t_minimap;

typedef struct s_doors
{
	int					**text_doors;
	int					doors;
	int					hit_flag;
	int					index;
}						t_doors;

typedef struct s_player
{
	int					**texture;
	int					**text_buff;
	double				p_angl;
	double				p_dir_x;
	double				p_dir_y;
	int					p_y;
	int					p_x;
	double				plane_x;
	double				plane_y;
	double				tile_size;
	double				plr_offset;
	double				plr_speed;
	double				speed_rot;
	char				**map;
	t_point				pos;
	t_doors				*doors;
	struct s_image		*img;
	struct s_data		*data;
	struct s_ray		*ray;
	struct s_minimap	*mini;
	int					move_forward;
	int					move_backward;
	int					move_left;
	int					move_right;
	int					rotate_left;
	int					rotate_right;
	int					mouse_x;

}						t_player;

typedef struct s_ray
{
	double				dir_x;
	double				dir_y;
	int					map_x;
	int					map_y;
	int					step_x;
	int					step_y;
	int					wall_height;
	double				wall_dist;
	int					side;
	double				delta_dist_x;
	double				delta_dist_y;
	double				side_dist_x;
	double				side_dist_y;
	int					start_pxl;
	int					end_pxl;
	double				wall_x;
}						t_ray;

typedef struct textures
{
	double				plyr_pos_x;
	double				plyr_pos_y;
	int					fd;
	char				*north;
	char				*south;
	char				*west;
	char				*east;
	char				*floor;
	char				*ceiling;
	unsigned int		floor_col;
	unsigned int		ceiling_col;
	int					floor_r;
	int					floor_g;
	int					floor_b;
	int					ceiling_r;
	int					ceiling_g;
	int					ceiling_b;
	char				*map_str_tmp;
	char				**map_tab_tmp;
	size_t				longest_line;
	int					nb_lines;
	int					i;
	int					**doors;
	struct s_player		*p;
	int					text_size;
}						t_textures;

typedef struct s_image
{
	void				*mlx;
	void				*img;
	void				*win_ptr;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	t_player			*p;
}						t_image;

typedef struct s_data
{
	char				**map;
	long				fps;
	int					fps_flag;
	long				old_time;
	long				actual_time;
	t_image				img;
	t_textures			*textures;
}						t_data;

// EXEC FUNCTIONS

// init

void					ft_player_init(t_player *p, t_data *data);
void					ft_mlx_init(t_player *p);
int						ft_inside_wall(t_player *p, int x, int y);
void					my_pixel_put(t_image *img, int x, int y, int color);
// movement
int						ft_handle_hook(int keycode, t_player *p);
int						key_press(int keycode, t_player *p);
int						key_release(int keycode, t_player *p);
void					update_position(t_player *p);
void					ft_go_down(t_player *p);
void					ft_go_up(t_player *p);
void					ft_go_left(t_player *p);
void					ft_go_right(t_player *p);
void					ft_turn_left(t_player *p);
void					ft_turn_right(t_player *p);

void					ft_draw_line(int x_start, int y_start, int x_end,
							int y_end, t_image *img);
int						ft_count_columns(char **map);
int						ft_count_lines(char **map);
double					ft_get_tile_size(char **map);
void					ft_draw_tile(t_image *img, int start_x, int start_y,
							int size, int color);
int						ft_refresh(t_player *p);
void					ft_draw_vertical_line(int x_val, int start, int end,
							t_image *img, long color);
void					ft_get_wall_size(t_player *p);
void					ft_cast_ray(t_player *p);
void					ft_calcul_dda(t_player *p);
void					ft_find_walls(t_player *p);
int						ft_get_text_index(t_player *p, t_ray *ray);

// MINIMAP
int						ft_count_columns(char **map);
int						ft_count_lines(char **map);
void					ft_minimap(t_player *p);
void					ft_draw_mini_background(t_image *img, int x_start,
							int x_end, int y_start, int y_end);
void					ft_player_render(t_player *p);
void					ft_minimap_render(t_player *p, char **map);
void					ft_init_minimap(t_player *p);
void					ft_countouring_render_00(t_player *p);

// TEXTURES
void					ft_init_textures(t_player *p);
void					ft_calcul_wall_text(t_player *p, int x);
void					ft_calcul_doors_text(t_player *p, int x,
							int doors_index);
void					ft_color_background(t_image *img);
int						ft_calcul_darkness(int color, double factor);
void					ft_cast_ray_doors(t_player *p);
int						ft_inside_doors(t_player *p, int x, int y);
void					ft_find_walls_doors(t_player *p);
// PARSING FUNCTIONS
int						is_door_valid(t_textures *textures, t_data *data);
int						parsing(int argc, char **argv, t_data *data);
int						arg_valid(int argc, char **argv);
int						read_file(t_textures *textures);
int						parse_line(char *str, t_textures *textures);
int						compare_texture_line(char *s1, char *s2,
							t_textures *textures);
int						get_map_line(char *str, t_textures *textures);
int						parse_map(t_textures *textures, t_data *data);
void					free_tab(char **tab);
void					ft_strcpy(char *dest, const char *src);
int						copy_and_check_walls(t_textures *textures,
							t_data *data);
int						invalid_char(t_textures *textures);
int						map_size(t_textures *textures);
int						is_map_open(t_data *data, t_textures *textures);
int						is_surrounded(int i, int j, t_data *data);
int						check_top_bottom(t_data *data, t_textures *textures);
int						check_sides(t_data *data, t_textures *textures);
int						is_image_xpm(char *path);
int						missing_textures(t_textures *textures);
int						parse_rgb(t_textures *textures);
int						isplayer(char c);
void					free_parsing(t_textures *textures, t_data *data);
int	check_rgb_values(t_textures *textures);


void					ft_init_ray(t_player *p, int x);
void					ft_draw_horizontal_line(int y_val, int start, int end,
							t_image *img, long color);
void					ft_draw_alpha_tile(t_image *img, int start_x,
							int start_y, int size, int color);

// debug functions
void					print_map(char **map);

// TIME_UTILS
long					ft_get_sec_time(void);
void					ft_print_fps(t_data *data);
int						get_hexa_color(int r, int g, int b);

// testing
int						ft_escape(t_player *p);

void					ft_free_all_struct(t_player *p);

#endif