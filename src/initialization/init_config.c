/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:10:31 by hfegrach          #+#    #+#             */
/*   Updated: 2025/11/13 23:10:40 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    init_config(t_game *game)
{
    int  len;

    while (game->map[game->height])
    {
        len = ft_strlen(game->map[game->height]);
        if (game->width < len)
            game->width = len;
        game->height++;
    }

    game->config.no_path =strdup("/home/gstitou/cube/textures/Bricks.xpm");
    game->config.so_path = strdup("/home/gstitou/cube/textures/Bricks2.xpm");
    game->config.we_path = strdup("/home/gstitou/cube/textures/Bricks3.xpm");
    game->config.ea_path = strdup("/home/gstitou/cube/textures/Bricks4.xpm");
    // game->config.c_rgb =
    // game->config.f_rgb = 
}
