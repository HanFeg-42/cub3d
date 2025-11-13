/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghita <ghita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:10:28 by hfegrach          #+#    #+#             */
/*   Updated: 2025/11/10 12:00:21 by ghita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_one_texture(t_game *game, t_img *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(game->mlx, path,
			&texture->width, &texture->height);
	if (texture->img == NULL)
	{
		printf("Error\nFailed to load texture: %s\n", path);
		clean_and_exit(game, "Texture loading failed.");
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	if (texture->addr == NULL)
	{
		printf("Error\nFailed to get data addr for: %s\n", path);
		clean_and_exit(game, "mlx_get_data_addr failed.");
	}
}


void    get_game(t_game *game)
{
    init_config(game);
    init_player(game);
    initialize_mlx(game);
	load_one_texture(game, &game->texture[NORTH], game->config.no_path);
	load_one_texture(game, &game->texture[SOUTH], game->config.so_path);
	load_one_texture(game, &game->texture[EAST], game->config.ea_path);
	load_one_texture(game, &game->texture[WEST], game->config.we_path);
}

t_game	*init_game(void)
{
	t_game *game;

	game = malloc(sizeof(t_game));
	if (!game)
		clean_and_exit(NULL, "malloc failded!");
	ft_bzero(game, sizeof(t_game));
	return (game);
}
