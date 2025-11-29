/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 15:38:21 by hfegrach          #+#    #+#             */
/*   Updated: 2025/11/29 15:54:56 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "types.h"

/* ===== Core Game Functions ===== */
t_game	*init_game(void);
void	initialize_mlx(t_game *game);
void	get_game(t_game *game);
void	exit_game(t_game *game, char *msg, int status);

/* ===== Initialization ===== */
void	init_config(t_game *game);
void	init_player(t_game *game);
void	init_wall_textures(t_game *game);
void	init_anim_textures(t_game *game);

/* ===== Rendering ===== */
int		render_game(t_game *game);
void	render_minimap(t_game *game);
void	render_animation(t_game *game);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

/* ===== Raycasting ===== */
void	ray_cast(t_game *game);
t_ray	vert_wall_intersection(t_game *game, double angle);
t_ray	horz_wall_intersection(t_game *game, double angle);
void	init_ray(t_ray *ray, double angle, int is_horz);
void	init_hit(t_game *game, t_ray *r, double next_x, double next_y);

/* ===== Texture Mapping ===== */
void	texture_mapping_and_draw(t_game *game, t_ray ray, int i, double line_h);
void	calculate_horz_map(t_ray ray, t_tex *tex_math);
void	calculate_vert_map(t_tex *tex, double wall_height);
void	draw_textured_column(t_game *g, t_tex *tex, int i);
t_img	*get_correct_texture(t_game *g, t_ray ray);
int		get_texture_pixel_color(t_img *tex_img, int tex_x, int tex_y);
int		shade_color(int color, double factor);

/* ===== Drawing Utilities ===== */
void	draw_square(t_img *img, double x, double y, int color);
void	draw_disk(t_img *img, t_point c, double r);
void	draw_rect(t_game *game, double x, double y, double len);
void	line(t_img *img, t_point start, t_point end);

/* ===== Player & Input ===== */
void	update_player(t_game *game);
void	update_player_bonus(t_game *game);
void	update_animation(t_game *game);
int		key_press(int key, t_game *data);
int		key_release(int key, t_game *data);
int		mouse_move(int x, int y, t_game *game);
int		mouse_click(int button, int x, int y, t_game *game);

/* ===== Door System ===== */
void	check_door_interaction(t_game *game);

/* ===== Parsing ===== */
void	parse_input(t_game *game, int ac, char **av);
char	*get_next_line(int fd);

/* ===== Math Utilities ===== */
double	normalize_angle(double angle);
double	max(double a, double b);
double	rad(double deg);

#endif