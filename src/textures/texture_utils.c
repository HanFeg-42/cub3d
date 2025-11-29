/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:08:44 by gstitou           #+#    #+#             */
/*   Updated: 2025/11/29 16:01:58 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_texture_pixel_color(t_img *tex_img, int tex_x, int tex_y)
{
	char	*pixel_address;

	pixel_address = tex_img->addr + (int)((tex_y * tex_img->line_length)
			+ tex_x * (tex_img->bits_per_pixel / 8));
	return (*(int *)pixel_address);
}

t_img	*get_correct_texture(t_game *game, t_ray ray)
{
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
