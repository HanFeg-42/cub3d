/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:29:38 by gstitou           #+#    #+#             */
/*   Updated: 2025/11/28 09:49:08 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_game *game)
{
	mlx_loop_end(game->mlx);
	return (0);
}

int main(int ac, char **av)
{
	t_game	*game;

	game = init_game();
	parse_input(game, ac, av);
	get_game(game);
	render_game(game);
	mlx_hook(game->win, 17, 0,close_window, game);
	// mlx_mouse_hide(game->mlx, game->win);
	mlx_mouse_move(game->mlx, game->win, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	mlx_hook(game->win, 6, 1L << 6,mouse_move, game);
	mlx_hook(game->win, 4,1L << 2, mouse_click, game);
	mlx_hook(game->win, 2, 1L << 0,key_press, game);
	mlx_hook(game->win, 3, 1L << 1,key_release, game);
	mlx_loop_hook(game->mlx, render_game, game);
	mlx_loop(game->mlx);
	exit_game(game, NULL, EXIT_SUCCESS);
	return (0);
}
