/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:46:41 by hfegrach          #+#    #+#             */
/*   Updated: 2025/10/29 09:06:48 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(char m, t_game *data)
{
	if (m == 'U')
		data->player.y -= MOVE_SPEED;
	if (m == 'D')
		data->player.y += MOVE_SPEED;
	if (m == 'L')
		data->player.x -= MOVE_SPEED;
	if (m == 'R')
		data->player.x += MOVE_SPEED;
}

void	rotate_player(char r, t_game *data)
{
	if (r == 'L')
		data->player.angle -= 1;
	if (r == 'R')
		data->player.angle += 1;
}

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
