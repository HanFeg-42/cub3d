/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:10:28 by hfegrach          #+#    #+#             */
/*   Updated: 2025/11/26 23:40:44 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_game(t_game *game)
{
	init_config(game);
	init_player(game);
	initialize_mlx(game);
	init_wall_textures(game);
	init_anim_textures(game);
}

t_game	*init_game(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		exit_game(NULL, "malloc failded!", EXIT_FAILURE);
	ft_bzero(game, sizeof(t_game));
	ft_bzero(&game->config, sizeof(t_config));
	game->config.c_rgb = -1;
	game->config.f_rgb = -1;
	return (game);
}
