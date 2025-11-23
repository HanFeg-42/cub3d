/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:17:01 by hfegrach          #+#    #+#             */
/*   Updated: 2025/11/23 17:44:54 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_img *img, double x, double y, int color)
{
	int	i;
	int	j;

	i = y;
	while (i < y + SCALE * MINIMAP_SCALE_FACTOR)
	{
		j = x;
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

// void	draw_line(t_img *img, double x, double y, t_ray *ray)
// {
// 	double	dx;
// 	double	dy;
// 	double	line_x;
// 	double	line_y;

// 	dx = cos(RAD(ray->angle));
// 	dy = sin(RAD(ray->angle));
// 	line_x = x;
// 	line_y = y;
// 	while (sqrt((line_x - x) * (line_x - x) + (line_y - y) * (line_y - y))
// 		<= ray->distance * MINIMAP_SCALE_FACTOR)
// 	{
// 		line_x += dx;
// 		line_y += dy;
// 		my_mlx_pixel_put(img, (int)round(line_x), (int)round(line_y), RED);
// 	}
// }

void	draw_disk(t_img *img, double xc, double yc, double r)
{
	int	y;
	int	x;

	y = yc - r;
	while (y <= yc + r)
	{
		x = xc - r;
		while (x <= xc + r)
		{
			if ((x - xc) * (x - xc) + (y - yc) * (y - yc) <= r * r)
				my_mlx_pixel_put(img, x, y, GRAY);
			x++;
		}
		y++;
	}
}

void	line(t_img *img, double x1, double y1, double x2, double y2)
{
	double	dx = x2 - x1;
	double	dy = y2 - y1;
	double	steps = max(fabs(dx), fabs(dy));
	double	x_inc = dx / steps;
	double	y_inc = dy / steps;
	int		i = 0;

	while (i < steps)
	{
		my_mlx_pixel_put(img, (int)round(x1), (int)round(y1),GRAY);
		x1 += x_inc;
		y1 += y_inc;
		i++;
	}
}



// https://sketchfab.com/3d-models/fps-pistol-animated-a8cdd6c2e936484aaf67e1786c8320d9




// https://sketchfab.com/3d-models/fps-arms-saiga-animations-remake-74e30b71e4a049b2a82b9d18f58e623c