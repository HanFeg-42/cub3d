/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:46:41 by hfegrach          #+#    #+#             */
/*   Updated: 2025/11/17 21:09:30 by hfegrach         ###   ########.fr       */
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
	else if (key == XK_Escape)
		mlx_loop_end(data->mlx);
	return (0);
}

int	key_release(int key, t_game *data)
{
	if (key == XK_w)
		data->player.y_dir = 0;
	else if (key == XK_s)
		data->player.y_dir = 0;
	else if (key == XK_d)
		data->player.x_dir = 0;
	else if (key == XK_a)
		data->player.x_dir = 0;
	else if (key == XK_Left)
		data->player.turn_dir = 0;
	else if (key == XK_Right)
		data->player.turn_dir = 0;
	else if (key == XK_Escape)
		mlx_loop_end(data->mlx);
	return (0);
}

void	update_angle(t_game *game)
{
	game->player.angle = normalize_angle(
			game->player.angle + game->player.turn_dir * ROTATION_SPEED
			);
}

void	check_move_valid(t_game *game, t_point new, t_point step)
{
	t_point old;
	int	map_x;
	int	map_y;

	map_x = (int)((new.x + (step.x * DIST)) / SCALE);
	map_y = (int)((new.y + (step.y * DIST)) / SCALE);
	old.x = (int)(game->player.x / SCALE);
	old.y = (int)(game->player.y / SCALE);
	if (game->map[map_y][map_x] == '1')
	{
		if (game->map[(int)(old.y)][map_x] == '1' && game->map[map_y][(int)(old.x)] != '1')
			game->player.y = new.y;
		else if (game->map[map_y][(int)(old.x)] == '1' && game->map[(int)(old.y)][map_x] != '1')
			game->player.x = new.x;
	}
	else
	{
		game->player.x = new.x;
		game->player.y = new.y;
	}
}

void	update_player(t_game *game)
{
	t_point new;
	t_point step;

	update_angle(game);
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
		step.y = + sin(RAD(game->player.angle + game->player.x_dir * 90));
		new.x = game->player.x + step.x * MOVE_SPEED;
		new.y = game->player.y + step.y * MOVE_SPEED;
	}
	else
		return ;
	check_move_valid(game, new, step);
}
