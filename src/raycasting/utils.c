/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:57:42 by hfegrach          #+#    #+#             */
/*   Updated: 2025/11/18 15:15:02 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	normalize_angle(double angle)
{
	while (angle < 0)
	{
		angle += 360.0;
	}
	while (angle >= 360)
	{
		angle -= 360.0;
	}
	return (angle);
}

double	get_ray_distance(t_player player, t_ray ray)
{
	if (ray.wall_hit_x && ray.wall_hit_y)
		return (sqrt((ray.wall_hit_x - player.x) * (ray.wall_hit_x - player.x)
				+ (ray.wall_hit_y - player.y) * (ray.wall_hit_y - player.y)));
	return (INT_MAX);
}

static int	has_wall_at(t_game *game, t_ray *ray, double next_x, double next_y)
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
	return (game->map[map_y][map_x] == '1');
}

void	init_ray(t_ray *ray, double angle, int is_horz)
{
	ft_bzero(ray, sizeof(t_ray));
	ray->angle = angle;
	ray->is_horz = is_horz;
	if (angle > 180)
		ray->is_facing_up = 1;
	if (angle > 90 && angle < 270)
		ray->is_facing_left = 1;
}

void	init_hit_intersect(t_game *game, t_ray *r, double next_x, double next_y)
{
	while (next_x / SCALE >= 0 && next_x / SCALE < game->width
		&& next_y / SCALE >= 0 && next_y / SCALE < game->height)
	{
		if (has_wall_at(game, r, next_x, next_y))
		{
			r->wall_hit_x = next_x;
			r->wall_hit_y = next_y;
			break ;
		}
		else
		{
			next_x += r->x_step;
			next_y += r->y_step;
		}
	}
	r->distance = get_ray_distance(game->player, *r);
}
