/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:29:38 by gstitou           #+#    #+#             */
/*   Updated: 2025/12/01 09:51:02 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game	*game;

	game = init_game();
	parse_input(game, ac, av);
	get_game(game);
	start_game(game);
	mlx_hooks(game);
	exit_game(game, NULL, EXIT_SUCCESS);
	return (0);
}
