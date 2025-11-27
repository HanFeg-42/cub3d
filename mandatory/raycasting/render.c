/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:20:05 by hfegrach          #+#    #+#             */
/*   Updated: 2025/11/27 15:39:51 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length
			+ x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	proj_walls(t_game *game)
{
    int i;
    double  dist_proj_plane;
    double  wall_strip_height;

	dist_proj_plane = (WINDOW_WIDTH / 2) / tan(RAD(FOV / 2));
    i = 0;
    while (i < NUM_RAYS)
    {
        game->ray[i].correct_wall_dist = game->ray[i].distance
            * cos(RAD(game->ray[i].angle - game->player.angle));
        wall_strip_height = (SCALE / game->ray[i].correct_wall_dist) * dist_proj_plane;
        texture_mapping_and_draw(game, game->ray[i], i,fabs(wall_strip_height));
        i++;
    }
}

int	render_game(t_game *game)
{
	update_player(game);
	ft_memset(game->img.addr, 0, game->img.line_length * WINDOW_HEIGHT);
	ray_cast(game);
	proj_walls(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}
