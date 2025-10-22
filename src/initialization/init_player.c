/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:10:23 by hfegrach          #+#    #+#             */
/*   Updated: 2025/10/17 20:44:35 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int player_angle(int c)
{
	if (c == 'N')
                return (270);
	else if (c == 'S')
                return (90);
	else if (c == 'E')
                return (0);
	else
                return (180);
}

void    init_player(t_game *game)
{
    int x;
    int y;

    ft_bzero(&game->player, sizeof(t_player));
    y = 0;
    while (game->map[y])
    {
        x = 0;
        while (game->map[y][x])
        {
                if (ft_strchr("NWSE", game->map[y][x]))
                {
                        game->player.x = x * SCALE + SCALE / 2;
                        game->player.y = y * SCALE + SCALE / 2;
                        game->player.angle = player_angle(game->map[y][x]);
                }
                x++;
        }
        y++;
    }
}
