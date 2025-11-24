/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:46:41 by hfegrach          #+#    #+#             */
/*   Updated: 2025/11/24 20:39:58 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int key, t_game *data)
{
	if (key == XK_w)
		data->player.y_dir = 1;
	else if (key == XK_s)
		data->player.y_dir = -1;
	else if (key == XK_d)
		data->player.x_dir = 1;
	else if (key == XK_a)
		data->player.x_dir = -1;
	else if (key == XK_Left)
		data->player.turn_dir = -1;
	else if (key == XK_Right)
		data->player.turn_dir = 1;
	else if (key == XK_space)
	{
    	if (data->player.is_shooting == false)
    	{
        	data->player.is_shooting = true;
        	data->gun.current_frame = 0;
    	}
	}
	else if (key == XK_Escape)
		mlx_loop_end(data->mlx);
	return (0);
}

int	key_release(int key, t_game *data)
{
	if (key == XK_w || key == XK_s)
		data->player.y_dir = 0;
	else if (key == XK_d || key == XK_a)
		data->player.x_dir = 0;
	else if (key == XK_Left || key == XK_Right)
		data->player.turn_dir = 0;
	if(data->player.y_dir == 0 && data->player.x_dir == 0)
		data->player.is_moving = false;
	return (0);
}

int	is_valid_position(t_game *game, t_point pos)
{
	int	y_plus_mar;
	int	y_minus_mar;
	int	x_plus_mar;
	int	x_minus_mar;

	y_plus_mar = (int)((pos.y + MARGIN) / SCALE);
	y_minus_mar = (int)((pos.y - MARGIN) / SCALE);
	x_plus_mar = (int)((pos.x + MARGIN) / SCALE);
	x_minus_mar = (int)((pos.x - MARGIN) / SCALE);
	if (game->map[y_plus_mar][x_plus_mar] == '1' || game->map[y_plus_mar][x_plus_mar] == 'D')
		return (0);
	if (game->map[y_plus_mar][x_minus_mar] == '1'|| game->map[y_plus_mar][x_plus_mar] == 'D')
		return (0);
	if (game->map[y_minus_mar][x_plus_mar] == '1'|| game->map[y_plus_mar][x_plus_mar] == 'D')
		return (0);
	if (game->map[y_minus_mar][x_minus_mar] == '1'|| game->map[y_plus_mar][x_plus_mar] == 'D')
		return (0);
	return (1);
}

void	check_move_valid(t_game *game, t_point new)
{
	t_point	check_x;
	t_point	check_y;

	check_x.x = new.x;
	check_x.y = game->player.y;
	check_y.x = game->player.x;
	check_y.y = new.y;
	if (is_valid_position(game, check_x))
	{
		game->player.x = new.x;
		game->player.is_moving = true;
	}
	if (is_valid_position(game, check_y))
	{
		game->player.y = new.y;
		game->player.is_moving = true;
	}
}

void	update_player(t_game *game)
{
	t_point	new;
	t_point	step;

	game->player.angle = normalize_angle(
			game->player.angle + game->player.turn_dir * ROTATION_SPEED);
	if (game->player.y_dir != 0)
	{
		step.x = game->player.y_dir * cos(RAD(game->player.angle));
		step.y = game->player.y_dir * sin(RAD(game->player.angle));
		new.x = game->player.x + step.x * MOVE_SPEED;
		new.y = game->player.y + step.y * MOVE_SPEED;
	}
	else if (game->player.x_dir != 0)
	{
		step.x = cos(RAD(game->player.angle + game->player.x_dir * 90));
		step.y = sin(RAD(game->player.angle + game->player.x_dir * 90));
		new.x = game->player.x + step.x * MOVE_SPEED;
		new.y = game->player.y + step.y * MOVE_SPEED;
	}
	else
		return ;
	check_move_valid(game, new);
}
