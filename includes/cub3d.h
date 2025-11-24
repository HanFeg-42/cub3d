/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:33:16 by gstitou           #+#    #+#             */
/*   Updated: 2025/11/24 21:02:01 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <stdbool.h>
# include <math.h>
# include "gc.h"

//---MAC----
// # define WINDOW_WIDTH 3000
// # define WINDOW_HEIGHT 2000
//---LINUX---
# define WINDOW_WIDTH 1500
# define WINDOW_HEIGHT 1000
# define SCALE 32
# define FOV 60
# define NUM_RAYS WINDOW_WIDTH
# define BUFFER_SIZE 32
# define SENSITIVITY 0.008
# define RED     0xFF0000
# define GREEN   0x00FF00
# define BLUE    0x0000FF
# define WHITE   0xFFFFFF
# define BLACK   0x000000
# define GRAY	 0x505050
# define MAGIC_PINK	0xFF00FF
# define MINIMAP_COLOR 0xC8C8C8
# define PLAYER_COLOR 0x64FF64
# define DOOR_COLOR BLUE


// #define CEILING_COLOR  0x87CEEB  // light sky blue
// #define FLOOR_COLOR    0x3E2C1C  // dark brown
// #define CEILING_COLOR  0xC0E8FF  // pale blue
// #define FLOOR_COLOR    0x705438  // medium brown
// #define CEILING_COLOR  0xA9A9A9  // gray ceiling
// #define FLOOR_COLOR    0x444444  // dark gray floor

# define MOVE_SPEED 5
# define ROTATION_SPEED 1
# define RAD(x) ((x) * M_PI / 180)
# define _USE_MATH_DEFINES
# define HORZ 1
# define VERT 0
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define  WEST 3
# define MINIMAP_SCALE_FACTOR 0.2
# define WALLSTRIP_SCALE_FACTOR 0.5
# define WALL_STRIP_WIDTH 1
#define NUM_TEXTURES 4
#define NUM_FRAME_SHOT 10
#define NUM_FRAME_MOVE 22
#define ANIM_SPEED 2
#define GUN_SCALE 1
# define DIST 10
# define MARGIN 10

# define EXIST 1

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int 	width;
	int		height;
}				t_img;

typedef struct s_tex
{
	t_img	*tex_img;
	int		tex_x;
	double	step;
	double	tex_pos;
	int		draw_start;
	int		draw_end;
}	t_tex;

typedef struct s_point
{
	double x;
	double y;
}	t_point;


typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
	int	turn_dir;
	double	x_dir;
	double	y_dir;
	bool is_moving;
	bool is_shooting;
}	t_player;

typedef struct s_config
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f_rgb;
	int		c_rgb;
}       t_config;

typedef struct s_ray
{
	double	angle;
	double	wall_hit_x;
	double	wall_hit_y;
	double	xintercept;
	double	yintercept;
	double	x_step;
	double	y_step;
	double	distance;
	int		is_horz;
	int		is_facing_up;
	int		is_facing_left;
	double  correct_wall_dist;
}		t_ray;

typedef struct s_gun
{
    t_img   shot[NUM_FRAME_SHOT];
    t_img   move[NUM_FRAME_MOVE];
    t_img   idle;
    int     current_frame;
}   t_gun;


typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	int			width;
	int			height;
	t_img		img;
	t_player	player;
	t_config	config;
	t_ray		ray[NUM_RAYS];
	t_img texture[NUM_TEXTURES];
	t_img door;
	t_gun gun;
}			t_game;

char	*get_next_line(int fd);
void    get_map(t_game *game, int ac, char **av);
void	clean_and_exit(t_game *game, char *msg);
void	exit_game(t_game *game, char *msg, int status);
void    initialize_mlx(t_game *game);
void    get_game(t_game *game);
t_game	*init_game(void);
void    init_config(t_game *game);
void    init_player(t_game *game);
int		key_press(int key, t_game *data);
int		key_release(int key, t_game *data);
int		render_game(t_game *game);
void	render_minimap(t_game *game);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	ray_cast(t_game *game);
double	normalize_angle(double angle);
void    init_hit_intersect(t_game *game, t_ray *ray, double next_x, double next_y);
void    init_ray(t_ray *ray, double angle, int is_horz);
void	draw_square(t_img *img, double x, double y, int color);
void	draw_line(t_img *img, double x, double y, t_ray *ray);
void	draw_disk(t_img *img, t_point c, double r);
void	draw_rect(t_game *game, double x, double y, double len);
double	max(double a, double b);
void	update_angle(t_game *game);
void    update_player(t_game *game);
t_ray   vert_wall_intersection(t_game *game, double angle);
t_ray   horz_wall_intersection(t_game *game, double angle);
void	line(t_img *img, t_point start, t_point end);
void    parse_input(t_game *game, int ac, char **av);

void			texture_mapping_and_draw(t_game *game, t_ray ray,int i, double line_h);
void			calculate_horz_map(t_ray ray, t_tex *tex_math);
void			calculate_vert_map(t_tex *tex, double wall_height);
void			draw_textured_column(t_game *g, t_tex *tex,int i);
t_img			*get_correct_texture(t_game *g, t_ray ray);
int				get_texture_pixel_color(t_img *tex_img, int tex_x, int tex_y);
int 			mouse_move(int x, int y ,t_game *game);
int 			shade_color(int color, double factor);
void			init_wall_textures(t_game *game);
void			init_anim_textures(t_game *game);
void 			render_animation(t_game *game);
void update_animation(t_game *game);
#endif
