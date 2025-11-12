/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:54:49 by hfegrach          #+#    #+#             */
/*   Updated: 2025/11/12 16:53:59 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_cast(t_game *game)
{
	t_ray	horz_ray;
	t_ray	vert_ray;
	double	angle;
	double	angle_step;
	int		i;

	angle = game->player.angle - FOV / 2;
	angle_step = (double)FOV / NUM_RAYS;
	i = 0;
	while (i < NUM_RAYS)
	{
		angle = normalize_angle(angle);
		horz_ray = horz_wall_intersection(game, angle);
		vert_ray = vert_wall_intersection(game, angle);
		game->ray[i] = vert_ray;
		if (horz_ray.distance < vert_ray.distance)
			game->ray[i] = horz_ray;
		angle += angle_step;
		i++;
	}
}
