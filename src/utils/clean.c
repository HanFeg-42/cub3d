/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:10:16 by hfegrach          #+#    #+#             */
/*   Updated: 2025/11/07 16:22:49 by hfegrach         ###   ########.fr       */
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

void exit_game(t_game *game, char *msg)
{
	if (msg)
		ft_putendl_fd(msg, 2);
    if (game)
    {
		if (game->mlx)
		{
			mlx_destroy_window(game->mlx, game->win);
			//clean_up(game->map);
			//destroy textures
			mlx_destroy_image(game->mlx, game->img.img);
			mlx_destroy_display(game->mlx);
			free(game->mlx);
		}

		free_2d_table(game->map);
		free(game);
    }
	exit(1);
}
