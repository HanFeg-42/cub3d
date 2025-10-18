/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:46:41 by hfegrach          #+#    #+#             */
/*   Updated: 2025/10/17 21:30:58 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(char m, t_game *data)
{
	if (m == 'U')
		data->player.y -= SPEED;
	if (m == 'D')
		data->player.y += SPEED;
	if (m == 'L')
		data->player.x -= SPEED;
	if (m == 'R')
		data->player.x += SPEED;
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
		move_player('U', data);
	else if (key == XK_s)
		move_player('D', data);
	else if (key == XK_d)
		move_player('R', data);
	else if (key == XK_a)
		move_player('L', data);
	else if (key == XK_Left)
		rotate_player('L', data);
	else if (key == XK_Right)
		rotate_player('R', data);
	else if (key == XK_Escape)
		mlx_loop_end(data->mlx);
	return (0);
}
