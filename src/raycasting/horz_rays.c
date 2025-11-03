/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horz_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:54:24 by hfegrach          #+#    #+#             */
/*   Updated: 2025/11/03 15:54:30 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void	init_first_horz_intercept(t_game *game, t_ray *ray, double angle)
{
	ray->yintercept = (int)(game->player.y / SCALE) * SCALE;
	if (angle < 180)
		ray->yintercept += SCALE;
	ray->xintercept = game->player.x
		+ (ray->yintercept - game->player.y) / tan(RAD(angle));
}

void init_horz_step(t_ray *ray, double angle)
{
    ray->y_step = SCALE;
    if (angle >= 180)
        ray->y_step *= -1;
    ray->x_step = SCALE / tan(RAD(angle));
    if (cos(RAD(angle)) < 0 && ray->x_step > 0)
        ray->x_step *= -1;
    if (cos(RAD(angle)) > 0 && ray->x_step < 0)
        ray->x_step *= -1;
}

t_ray   horz_wall_intersection(t_game *game, double angle)
{
    t_ray   ray;
    double	next_horz_x;
	double	next_horz_y;

    init_ray(&ray, angle, HORZ);
    init_first_horz_intercept(game, &ray, angle);
    init_horz_step(&ray, angle);
    next_horz_x = ray.xintercept;
    next_horz_y = ray.yintercept;
    init_wall_hit_intersection(game, &ray, next_horz_x, next_horz_y);
    return (ray);
}
