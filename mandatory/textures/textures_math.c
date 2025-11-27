/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_math.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:08:47 by gstitou           #+#    #+#             */
/*   Updated: 2025/11/14 16:37:21 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void calculate_horz_map(t_ray ray, t_tex *tex)
{
    double wall_x_percent;
    double remainder;

    if (ray.is_horz)
        remainder = fmod(ray.wall_hit_x, SCALE);
    else
        remainder = fmod(ray.wall_hit_y, SCALE);
    if (remainder < 0)
        remainder += SCALE;
    wall_x_percent = remainder / SCALE;
    tex->tex_x = (int)(wall_x_percent * (double)tex->tex_img->width);
    if (tex->tex_x < 0)
        tex->tex_x = 0;
    if (tex->tex_x >= tex->tex_img->width)
        tex->tex_x = tex->tex_img->width - 1;
    if ((ray.is_horz && ray.is_facing_up) ||
        (!ray.is_horz && ray.is_facing_left))
        tex->tex_x = tex->tex_img->width - tex->tex_x - 1;
}
void calculate_vert_map(t_tex *tex, double wall_height)
{
    tex->step = (double)tex->tex_img->height / wall_height;
    tex->draw_start = (WINDOW_HEIGHT / 2) - (wall_height / 2);
    tex->draw_end = (WINDOW_HEIGHT / 2) + (wall_height / 2);
    if (tex->draw_start < 0)
        tex->draw_start = 0;
    if (tex->draw_end >= WINDOW_HEIGHT)
        tex->draw_end = WINDOW_HEIGHT - 1;
    tex->tex_pos = (tex->draw_start - (WINDOW_HEIGHT / 2) + (wall_height / 2)) * tex->step;
}


// Realistic textures (e.g., brick, wood, stone, concrete)?

// Sci-fi textures (e.g., metal panels, futuristic screens)?

// Fantasy textures (e.g., ancient runes, castle walls)?

// Abstract patterns?