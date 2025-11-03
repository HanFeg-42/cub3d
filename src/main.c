/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:10:13 by hfegrach          #+#    #+#             */
/*   Updated: 2025/11/03 13:54:58 by hfegrach         ###   ########.fr       */
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
	get_map(game, ac, av);
	get_game(game);
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_hook(game->win, 2, (1L << 0), key_press, game);
	mlx_hook(game->win, 3, (1L << 1), key_release, game);
	mlx_loop_hook(game->mlx, render_game, game);
	mlx_loop(game->mlx);
	exit_game(game, NULL);
	return (0);
}
