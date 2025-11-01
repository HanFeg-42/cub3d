/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:26:01 by hfegrach          #+#    #+#             */
/*   Updated: 2025/11/01 13:26:22 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    initialize_mlx(t_game *game)
{
    game->mlx = mlx_init();
    // game->win = mlx_new_window(game->mlx, game->width * SCALE,
    //     game->height * SCALE, "cub3d");
    // game->img.img = mlx_new_image(game->mlx, game->width * SCALE,
    //     game->height * SCALE);
    game->win = mlx_new_window(game->mlx, WINDOW_WIDTH,
        WINDOW_HEIGHT, "cub3d");
    game->img.img = mlx_new_image(game->mlx, WINDOW_WIDTH,
        WINDOW_HEIGHT);
    game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
        &game->img.line_length, &game->img.endian);
}
