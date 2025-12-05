/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 09:44:21 by hfegrach          #+#    #+#             */
/*   Updated: 2025/12/01 09:51:43 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_move(int x, int y, t_game *game)
{
	int	center_x;
	int	delta_x;

	(void)y;
	center_x = WINDOW_WIDTH / 2;
	delta_x = x - center_x;
	if (delta_x == 0)
		return (0);
	game->player.angle = normalize_angle(game->player.angle + delta_x
			* SENSITIVITY);
	mlx_mouse_move(game->mlx, game->win, center_x, WINDOW_HEIGHT / 2);
	return (0);
}

int	close_window(t_game *game)
{
	mlx_loop_end(game->mlx);
	return (0);
}

void	mlx_hooks(t_game *game)
{
	mlx_hook(game->win, 17, 0, close_window, game);
	// mlx_mouse_hide(game->mlx, game->win);
	mlx_mouse_move(game->mlx, game->win, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	mlx_hook(game->win, 6, 1L << 6, mouse_move, game);
	mlx_hook(game->win, 4, 1L << 2, mouse_click, game);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_loop_hook(game->mlx, start_game, game);
	mlx_loop(game->mlx);
}
