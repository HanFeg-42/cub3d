/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vert_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:54:43 by hfegrach          #+#    #+#             */
/*   Updated: 2025/11/03 15:54:44 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void    init_first_vert_intercept(t_game *game, t_ray *ray, double angle)
{
	ray->xintercept = (int)(game->player.x / SCALE) * SCALE;
	if (cos(RAD(angle)) > 0)
		ray->xintercept += SCALE;
	ray->yintercept = game->player.y
		+ (ray->xintercept - game->player.x) * tan(RAD(angle));
}

void    init_vert_step(t_ray *ray, double angle)
{
    ray->x_step = SCALE;
    if (cos(RAD(angle)) < 0)
        ray->x_step *= -1;
    ray->y_step = SCALE * tan(RAD(angle));
    if (sin(RAD(angle)) < 0 && ray->y_step > 0)
        ray->y_step *= -1;
    if (sin(RAD(angle)) > 0 && ray->y_step < 0)
        ray->y_step *= -1;
}

t_ray   vert_wall_intersection(t_game *game, double angle)
{
    t_ray   ray;
    double	next_vert_x;
	double	next_vert_y;

    init_ray(&ray, angle, VERT);
    init_first_vert_intercept(game, &ray, angle);
    init_vert_step(&ray, angle);
    next_vert_x = ray.xintercept;
    next_vert_y = ray.yintercept;
    init_wall_hit_intersection(game, &ray, next_vert_x, next_vert_y);
    return (ray);
}
