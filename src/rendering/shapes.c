/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:17:01 by hfegrach          #+#    #+#             */
/*   Updated: 2025/11/23 20:11:28 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_img *img, double x, double y, int color)
{
	int	i;
	int	j;

	i = y + 2;
	while (i < y + SCALE * MINIMAP_SCALE_FACTOR)
	{
		j = x + 2;
		while (j < x + SCALE * MINIMAP_SCALE_FACTOR)
		{
			my_mlx_pixel_put(img, j, i, color);
			j++;
		}
		i++;
	}
}

int	get_color(t_game *game, double y, double len)
{
	if (y == 0 && len < WINDOW_HEIGHT)
		return (game->config.c_rgb);
	if (y > WINDOW_HEIGHT / 2)
		return (game->config.f_rgb);
	return (GRAY);
}

void	draw_rect(t_game *game, double x, double y, double len)
{
	int	i;
	int	j;
	int	color;

	color = get_color(game, y, len);
	i = y;
	while (i < y + (int)len)
	{
		j = x;
		while (j < x + WALL_STRIP_WIDTH)
		{
			my_mlx_pixel_put(&game->img, j, i, color);
			j++;
		}
		i++;
	}
}

void	draw_disk(t_img *img, t_point c, double r)
{
	int	y;
	int	x;

	y = c.y - r;
	while (y <= c.y + r)
	{
		x = c.x - r;
		while (x <= c.x + r)
		{
			if ((x - c.x) * (x - c.x) + (y - c.y) * (y - c.y) <= r * r)
				my_mlx_pixel_put(img, x, y, PLAYER_COLOR);
			x++;
		}
		y++;
	}
}

void	line(t_img *img, t_point start, t_point end)
{
	t_point	d;
	t_point	inc;
	double	steps;
	int		i;

	d.x = end.x - start.x;
	d.y = end.y - start.y;
	steps = max(fabs(d.x), fabs(d.y));
	inc.x = d.x / steps;
	inc.y = d.y / steps;
	i = 0;
	while (i < steps)
	{
		my_mlx_pixel_put(img, (int)(start.x), (int)(start.y), WHITE);
		start.x += inc.x;
		start.y += inc.y;
		i++;
	}
}



// https://sketchfab.com/3d-models/fps-pistol-animated-a8cdd6c2e936484aaf67e1786c8320d9




// https://sketchfab.com/3d-models/fps-arms-saiga-animations-remake-74e30b71e4a049b2a82b9d18f58e623c