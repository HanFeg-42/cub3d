/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:10:16 by hfegrach          #+#    #+#             */
/*   Updated: 2025/11/09 12:41:25 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_2d_table(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	free(arr);
}

void	destroy_game(t_game *game)
{
	if (game->map)
		free_2d_table(game->map);
	if (game->config.no_path)
		free(game->config.no_path);
	if (game->config.so_path)
		free(game->config.so_path);
	if (game->config.we_path)
		free(game->config.we_path);
	if (game->config.ea_path)
		free(game->config.ea_path);
}

void exit_game(t_game *game, char *msg, int status)
{
	if (msg)
		ft_putendl_fd(msg, 2);
    if (game)
    {
		{
			if (game->mlx)
			{
				mlx_destroy_window(game->mlx, game->win);
				//destroy textures
				mlx_destroy_image(game->mlx, game->img.img);
				mlx_destroy_display(game->mlx);
				free(game->mlx);
			}

		}
		destroy_game(game);
		free(game);
    }
	free_all();
	exit(status);
}
