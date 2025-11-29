/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 15:36:14 by hfegrach          #+#    #+#             */
/*   Updated: 2025/11/29 15:36:46 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "constants.h"
# include <stdbool.h>

/* Image structure for MLX rendering */
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

/* Texture mapping calculations */
typedef struct s_tex
{
	t_img	*tex_img;
	int		tex_x;
	double	step;
	double	tex_pos;
	int		draw_start;
	int		draw_end;
}	t_tex;

/* 2D point coordinates */
typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

/* Player state and position */
typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
	int		turn_dir;
	double	x_dir;
	double	y_dir;
	bool	is_moving;
	bool	is_shooting;
}	t_player;

/* Map configuration from .cub file */
typedef struct s_config
{
	char	*no; /* North texture path */
	char	*so; /* South texture path */
	char	*we; /* West texture path */
	char	*ea; /* East texture path */
	int		f_rgb; /* Floor color */
	int		c_rgb; /* Ceiling color */
}	t_config;

/* Raycasting data for single ray */
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
	double	correct_wall_dist;
}	t_ray;

/* Gun animation frames */
typedef struct s_gun
{
	t_img	shot[NUM_FRAME_SHOT];
	t_img	move[NUM_FRAME_MOVE];
	t_img	idle;
	int		current_frame;
}	t_gun;

/* Door state and animation */
typedef struct s_door
{
	int		x;
	int		y;
	int		is_open;
	double	open_progress;
}	t_door;

/* Main game structure */
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
	t_img		texture[NUM_TEXTURES];
	t_img		door;
	t_gun		gun;
}	t_game;

#endif