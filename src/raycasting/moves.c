/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:46:41 by hfegrach          #+#    #+#             */
/*   Updated: 2025/11/03 14:17:32 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int key, t_game *data)
{
	if (key == XK_w)
		data->player.y_dir = 1;// -1
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
	else if (key ==XK_d)
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

void check_move_valid(t_game *game, double new_x, double new_y)
{
    int map_x = (int)(new_x / SCALE);
    int map_y = (int)(new_y / SCALE);
    if (game->map[map_y][map_x] != '1')
    {
        game->player.x = new_x;
        game->player.y = new_y;
    }
}

void    update_player(t_game *game)
{
    double new_x;
    double new_y;
    double y_step;

    update_angle(game);
    y_step = game->player.y_dir * MOVE_SPEED;

    if (game->player.y_dir !=  0)
    {
        new_x = game->player.x + y_step * cos(RAD(game->player.angle));
        new_y = game->player.y + y_step * sin(RAD(game->player.angle));
    }
    else if (game->player.x_dir != 0)
    {
        new_x = game->player.x + cos(RAD(game->player.angle +
            game->player.x_dir * 90)) * MOVE_SPEED;
        new_y = game->player.y + sin(RAD(game->player.angle +
            game->player.x_dir * 90)) * MOVE_SPEED;
    }
    else
        return;
    check_move_valid(game, new_x, new_y);
}
