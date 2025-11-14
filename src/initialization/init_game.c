/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:10:28 by hfegrach          #+#    #+#             */
/*   Updated: 2025/11/14 16:37:45 by hfegrach         ###   ########.fr       */
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
		exit_game(game, "Texture loading failed.", EXIT_FAILURE);
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	if (texture->addr == NULL)
	{
		printf("Error\nFailed to get data addr for: %s\n", path);
		exit_game(game, "mlx_get_data_addr failed.", EXIT_FAILURE);
	}
}


void    get_game(t_game *game)
{
    init_config(game);
    init_player(game);
    initialize_mlx(game);
	load_one_texture(game, &game->texture[NORTH], game->config.no);
	load_one_texture(game, &game->texture[SOUTH], game->config.so);
	load_one_texture(game, &game->texture[EAST], game->config.ea);
	load_one_texture(game, &game->texture[WEST], game->config.we);
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
