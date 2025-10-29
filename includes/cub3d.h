/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 23:40:45 by kali              #+#    #+#             */
/*   Updated: 2025/10/29 15:33:09 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <stdbool.h>
# include <math.h>

# define WINDOW_WIDTH 320
# define WINDOW_HEIGHT 600
# define SCALE 64
# define FOV 60
# define NUM_RAYS 320
# define BUFFER_SIZE 32

# define MOVE_SPEED 0.5
# define ROTATION_SPEED 0.25

# define _USE_MATH_DEFINES
# define MAX(a, b) ((a) > (b) ? (a) : (b))


typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

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
	int		fd;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		f_rgb;
	int		c_rgb;
	char	*map_path;
	char	*join;
}       t_config;

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
}			t_game;

typedef struct s_ray
{
	double	wall_hit_x;
	double	wall_hit_y;
	double	xintercept;
	double	yintercept;
	double	x_step;
	double	y_step;
	double	distance;
}		t_ray;


char	*get_next_line(int fd);
void    get_map(t_game *game, int ac, char **av);
void	exit_game(t_game *game, char *msg);
void    initialize_mlx(t_game *game);
void    get_game(t_game *game);
t_game	*init_game(void);
void    init_config(t_game *game);
void    init_player(t_game *game);
void	move_player(char m, t_game *data);
void	rotate_player(char r, t_game *data);
int	key_press(int key, t_game *data);
int	key_release(int key, t_game *data);
int	render_map(t_game *game);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
double rad(double deg);
void	draw_line(t_img *img, double x, double y, double deg, int color);
void	ray_cast(t_game *game);
#endif
