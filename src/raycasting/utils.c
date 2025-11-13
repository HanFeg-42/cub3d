/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:57:42 by hfegrach          #+#    #+#             */
/*   Updated: 2025/11/12 14:50:20 by gstitou          ###   ########.fr       */
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
double  get_ray_distance(t_player player, t_ray ray)
{
    if (ray.wall_hit_x && ray.wall_hit_y)
        return (sqrt((ray.wall_hit_x - player.x) * (ray.wall_hit_x - player.x)
            + (ray.wall_hit_y - player.y) * (ray.wall_hit_y - player.y)));
    return (INT_MAX);
}

int has_wall_at(t_game *game, t_ray *ray, double next_x, double next_y)
{
    int map_x;
    int map_y;

    if (ray->is_horz && ray->is_facing_up)
        map_y = (int)((next_y - 1) / SCALE);
    else
        map_y = (int)(next_y / SCALE);
    if (!ray->is_horz && ray->is_facing_left)
        map_x = (int)((next_x - 1) / SCALE);
    else
        map_x = (int)(next_x / SCALE);
    if (map_x < 0 || map_x > game->width || map_y < 0 || map_y > game->height)
        return (1);
    return (game->map[map_y][map_x] == '1');
}

void    init_ray(t_ray *ray, double angle, int is_horz)
{
    ft_bzero(ray, sizeof(t_ray));
    ray->angle = angle;
    ray->is_horz = is_horz;
    if (angle > 180)
    ray->is_facing_up = 1;
    if (angle > 90 && angle < 270)
    ray->is_facing_left = 1;
}

void    init_wall_hit_intersection(t_game *game, t_ray *ray, double next_x, double next_y)
{
    while (next_x / SCALE  >= 0 && (next_x / SCALE) < game->width
        && next_y / SCALE >= 0 && (next_y / SCALE)  < game->height)
    {
        if (has_wall_at(game, ray, next_x, next_y))
        {
            ray->wall_hit_x = next_x;
            ray->wall_hit_y = next_y;
            break;
        }
        else
        {
            next_x += ray->x_step;
            next_y += ray->y_step;
        }
    }
    ray->distance = get_ray_distance(game->player, *ray);
}
