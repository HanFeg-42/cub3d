/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:17:01 by hfegrach          #+#    #+#             */
/*   Updated: 2025/11/03 15:56:54 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_img *img, double x, double y, int color)
{
	int i;
	int j;

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

void	draw_rect(t_img *img, double x, double y, double len)
{
	int i;
	int j;

	i = y;
	while (i < y + (int)len)
	{
		j = x;
		while (j < x + WALL_STRIP_WIDTH)
		{
			my_mlx_pixel_put(img, j, i, 0xFFFFFF);
			j++;
		}
		i++;
	}
}

void	draw_line(t_img *img, double x, double y, double deg)
{
	double dx = cos(RAD(deg));
	double dy = sin(RAD(deg));
	double line_x = x;
	double line_y = y;

	while (sqrt((line_x - x) * (line_x - x) + (line_y - y) * (line_y - y)) <= 50)
	{
		line_x += dx;
		line_y += dy;
		my_mlx_pixel_put(img, line_x, line_y, RED);
	}
}

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
				my_mlx_pixel_put(img, x, y, RED);
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
		my_mlx_pixel_put(img, (int)round(x1), (int)round(y1), 0xFF0000);
		x1 += x_inc;
		y1 += y_inc;
		i++;
	}
}
