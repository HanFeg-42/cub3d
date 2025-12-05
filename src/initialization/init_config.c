/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:10:31 by hfegrach          #+#    #+#             */
/*   Updated: 2025/11/14 14:29:36 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_config(t_game *game)
{
	int	len;

	while (game->map[game->height])
	{
		len = ft_strlen(game->map[game->height]);
		if (game->width < len)
			game->width = len;
		game->height++;
	}
}
