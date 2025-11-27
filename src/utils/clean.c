/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:10:16 by hfegrach          #+#    #+#             */
/*   Updated: 2025/11/27 14:13:36 by gstitou          ###   ########.fr       */
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

void clean_anim_textures(t_game *game)
{
	int	i;

	i = 0;
	while(i < NUM_FRAME_SHOT)
	{
		if(game->gun.shot[i].img)
			mlx_destroy_image(game->mlx, game->gun.shot[i].img);
		i++;
	}
	i = 0;
	while(i < NUM_FRAME_MOVE)
	{
		if(game->gun.move[i].img)
			mlx_destroy_image(game->mlx, game->gun.move[i].img);
		i++;
	}
	if(game->gun.idle.img)
			mlx_destroy_image(game->mlx, game->gun.idle.img);
}

void	clean_textures(t_game *game)
{
	int	i;

	i = 0;

	while (i < NUM_TEXTURES)
	{
		if (game->texture[i].img)
			mlx_destroy_image(game->mlx, game->texture[i].img);
		i++;
	}
	clean_anim_textures(game);
	
	if(game->door.img)
			mlx_destroy_image(game->mlx, game->door.img);
}

void	destroy_game(t_game *game)
{
	if (game->map)
		free_2d_table(game->map);
	if (game->config.no)
		free(game->config.no);
	if (game->config.so)
		free(game->config.so);
	if (game->config.we)
		free(game->config.we);
	if (game->config.ea)
		free(game->config.ea);
}

void	exit_game(t_game *game, char *msg, int status)
{
	if (msg)
		ft_putendl_fd(msg, 2);
	if (game)
	{
		if (game->mlx)
		{
			clean_textures(game);
			if( game->img.img)
				mlx_destroy_image(game->mlx, game->img.img);
			mlx_destroy_window(game->mlx, game->win);
			mlx_destroy_display(game->mlx);
			free(game->mlx);
		}
		destroy_game(game);
		free(game);
	}
	free_all();
	exit(status);
}
