/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 20:28:21 by gstitou           #+#    #+#             */
/*   Updated: 2025/11/29 15:31:42 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void check_door_interaction(t_game *game)
{
	double check_x;
	double check_y;
	int map_x;
	int map_y;

	check_x = game->player.x + cos(rad(game->player.angle)) *SCALE * DOOR_DIST;
	check_y = game->player.y + sin(rad(game->player.angle)) *SCALE * DOOR_DIST;
	map_x = (int) check_x / SCALE;
	map_y = (int) check_y / SCALE;
	if(map_x < 0 || map_x >= game->width || map_y < 0 || map_y >= game->height)
		return;
	if(game->map[map_y][map_x] == 'D')
	{
		game->map[map_y][map_x] = 'O';
	}
	else if(game->map[map_y][map_x] == 'O')
	{
		// if((int)(game->player.x / SCALE) != map_x && (int)(game->player.y / SCALE) != map_y)
		game->map[map_y][map_x] = 'D';
	}
}