/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 23:40:45 by kali              #+#    #+#             */
/*   Updated: 2025/11/12 17:17:56 by hfegrach         ###   ########.fr       */
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

# define RED     0xFF0000
# define GREEN   0x00FF00
# define BLUE    0x0000FF
# define WHITE   0xFFFFFF
# define BLACK   0x000000
# define GRAY	 0x505050

// #define CEILING_COLOR  0x87CEEB  // light sky blue
// #define FLOOR_COLOR    0x3E2C1C  // dark brown
// #define CEILING_COLOR  0xC0E8FF  // pale blue
// #define FLOOR_COLOR    0x705438  // medium brown
// #define CEILING_COLOR  0xA9A9A9  // gray ceiling
// #define FLOOR_COLOR    0x444444  // dark gray floor

# define MOVE_SPEED 1
# define ROTATION_SPEED 2

# define _USE_MATH_DEFINES
# define MAX(a, b) ((a) > (b) ? (a) : (b))
# define RAD(x) ((x) * M_PI / 180)
# define HORZ 1
# define VERT 0
# define MINIMAP_SCALE_FACTOR 0.2
# define WALLSTRIP_SCALE_FACTOR 0.5
# define WALL_STRIP_WIDTH 1

# define EXIST 1

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

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
}		t_ray;

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
}			t_game;

char	*get_next_line(int fd);
void    get_map(t_game *game, int ac, char **av);
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
void	line(t_img *img, double x1, double y1, double x2, double y2);
double	normalize_angle(double angle);
void    init_hit_intersect(t_game *game, t_ray *ray, double next_x, double next_y);
void    init_ray(t_ray *ray, double angle, int is_horz);
void	draw_square(t_img *img, double x, double y, int color);
void	draw_line(t_img *img, double x, double y, t_ray *ray);
void	draw_disk(t_img *img, double xc, double yc, double r);
void	draw_rect(t_game *game, double x, double y, double len);
double	max(double a, double b);
void	update_angle(t_game *game);
void    update_player(t_game *game);
t_ray   vert_wall_intersection(t_game *game, double angle);
t_ray   horz_wall_intersection(t_game *game, double angle);
void	line(t_img *img, double x1, double y1, double x2, double y2);
void    parse_input(t_game *game, int ac, char **av);

#endif
