/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:08:44 by gstitou           #+#    #+#             */
/*   Updated: 2025/11/26 23:11:38 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_texture_pixel_color(t_img *tex_img, int tex_x, int tex_y)
{
	char	*pixel_address;

	pixel_address = tex_img->addr + (int)((tex_y * tex_img->line_length) + tex_x
			* (tex_img->bits_per_pixel / 8));
	return (*(int *)pixel_address);
}

int	has_door_at(t_game *game, t_ray *ray, double next_x, double next_y)
{
	int	map_x;
	int	map_y;

	if (ray->is_horz && ray->is_facing_up)
		map_y = (int)((next_y - 1) / SCALE);
	else
		map_y = (int)(next_y / SCALE);
	if (!ray->is_horz && ray->is_facing_left)
		map_x = (int)((next_x - 1) / SCALE);
	else
	{
		map_x = (int)(next_x / SCALE);
	}
	if (!game->map[map_y] || map_x >= (int)ft_strlen(game->map[map_y]))
	{
		return (1);
	}
	return (game->map[map_y][map_x] == 'D');
}


t_img	*get_correct_texture(t_game *game, t_ray ray)
{
	if(has_door_at(game, &ray, ray.wall_hit_x,ray.wall_hit_y))
	{
		return (&game->door);
	}
	if (ray.is_horz)
	{
		if (ray.is_facing_up)
			return (&game->texture[NORTH]);
		return (&game->texture[SOUTH]);
	}
	if (ray.is_facing_left)
		return (&game->texture[WEST]);
	return (&game->texture[EAST]);
}
