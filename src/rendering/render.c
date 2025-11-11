/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:20:05 by hfegrach          #+#    #+#             */
/*   Updated: 2025/11/10 20:50:34 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == '1')
				draw_square(&game->img,
					j * SCALE * MINIMAP_SCALE_FACTOR,
					i * SCALE * MINIMAP_SCALE_FACTOR,
					BLACK);
			// else
			// 	draw_square(&game->img,
			// 		j * SCALE * MINIMAP_SCALE_FACTOR,
			// 		i * SCALE * MINIMAP_SCALE_FACTOR,
			// 		0xFFFFFF);
			j++;
		}
		i++;
	}
}

void    render_minimap(t_game *game)
{
    int i;

    i = 0;
    draw_minimap(game);
	draw_disk(&game->img,
        game->player.x * MINIMAP_SCALE_FACTOR,
        game->player.y * MINIMAP_SCALE_FACTOR, 3);
    while (i < NUM_RAYS)
    {
        // draw_line(
        //     &game->img,
        //     game->player.x * MINIMAP_SCALE_FACTOR,
        //     game->player.y * MINIMAP_SCALE_FACTOR,
        //     &game->ray[i]
        // );
        line(
            &game->img,
            game->player.x * MINIMAP_SCALE_FACTOR,
            game->player.y * MINIMAP_SCALE_FACTOR,
            game->ray[i].wall_hit_x * MINIMAP_SCALE_FACTOR,
            game->ray[i].wall_hit_y * MINIMAP_SCALE_FACTOR
        );
        i++;
    }
}

void    render_proj_wall(t_game *game, double wall_height, int i)
{
    double  x;
    double  y;
    double  len;

    x = i * WALL_STRIP_WIDTH;
    if (wall_height > WINDOW_HEIGHT)
        wall_height = WINDOW_HEIGHT;
    y = (WINDOW_HEIGHT / 2) - (wall_height / 2);
    if (y < 0)
        y = 0;
    draw_rect(game, x, y, wall_height);
    len = (WINDOW_HEIGHT - wall_height) / 2;
    draw_rect(game, x, 0, len); // ceiling color
    draw_rect(game, x, y + wall_height, len); //  floor color
}

void    proj_walls(t_game *game)
{
    int i;
    double  dist_proj_plane;
    double  wall_strip_height;
    double  correct_wall_dist;

    i = 0;
    while (i < NUM_RAYS)
    {
        correct_wall_dist = game->ray[i].distance
            * cos(RAD(game->ray[i].angle - game->player.angle));
        dist_proj_plane = (WINDOW_WIDTH / 2) / tan(RAD(FOV / 2));
        wall_strip_height = (SCALE / correct_wall_dist) * dist_proj_plane;
        render_proj_wall(game, fabs(wall_strip_height), i);
        i++;
    }
}

int	render_game(t_game *game)
{
    update_player(game);
	ft_memset(game->img.addr, 0, game->img.line_length * WINDOW_HEIGHT);
	ray_cast(game);
    proj_walls(game);
    render_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}
