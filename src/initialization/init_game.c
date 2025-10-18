/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:10:28 by hfegrach          #+#    #+#             */
/*   Updated: 2025/10/17 20:10:29 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    get_game(t_game *game)
{
    init_config(game);
    init_player(game);
    initialize_mlx(game);
}

t_game	*init_game(void)
{
	t_game *game;

	game = malloc(sizeof(t_game));
	if (!game)
		exit_game(NULL, "malloc failded!");
	ft_bzero(game, sizeof(t_game));
	return (game);
}
