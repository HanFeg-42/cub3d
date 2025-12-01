/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:20:05 by hfegrach          #+#    #+#             */
/*   Updated: 2025/12/01 09:44:09 by hfegrach         ###   ########.fr       */
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
				draw_square(&game->img, j * SCALE * MM_FACTOR, i * SCALE
					* MM_FACTOR, MINIMAP_COLOR);
			if (game->map[i][j] == 'D')
				draw_square(&game->img, j * SCALE * MM_FACTOR, i * SCALE
					* MM_FACTOR, DOOR_COLOR);
			if (game->map[i][j] == 'O')
				draw_square(&game->img, j * SCALE * MM_FACTOR, i * SCALE
					* MM_FACTOR, OPEN_DOOR_COLOR);
			j++;
		}
		i++;
	}
}

void	render_minimap(t_game *game)
{
	t_point	start;
	t_point	end;
	int		i;

	start.x = game->player.x * MM_FACTOR;
	start.y = game->player.y * MM_FACTOR;
	draw_minimap(game);
	i = 0;
	while (i < NUM_RAYS)
	{
		end.x = game->ray[i].wall_hit_x * MM_FACTOR;
		end.y = game->ray[i].wall_hit_y * MM_FACTOR;
		line(&game->img, start, end);
		i++;
	}
	draw_disk(&game->img, start, 2);
}

void	proj_walls(t_game *game)
{
	int		i;
	double	dist_proj_plane;
	double	wall_strip_height;

	dist_proj_plane = (WINDOW_WIDTH / 2) / tan(rad(FOV / 2));
	i = 0;
	while (i < NUM_RAYS)
	{
		game->ray[i].correct_wall_dist = game->ray[i].distance
			* cos(rad(game->ray[i].angle - game->player.angle));
		wall_strip_height = (SCALE / game->ray[i].correct_wall_dist)
			* dist_proj_plane;
		texture_mapping_and_draw(game, game->ray[i], i,
			fabs(wall_strip_height));
		i++;
	}
}

int	start_game(t_game *game)
{
	update_player_bonus(game);
	update_animation(game);
	ft_memset(game->img.addr, 0, game->img.line_length * WINDOW_HEIGHT);
	ray_cast(game);
	proj_walls(game);
	render_minimap(game);
	render_animation(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}
