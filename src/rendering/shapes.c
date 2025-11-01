#include "cub3d.h"

void	draw_rays(t_game *game)
{
	double	angle;
	int		i;

	angle = game->player.angle - FOV / 2;
	i = 0;
	while (i < NUM_RAYS)
	{
		draw_line(&game->img, game->player.x, game->player.y, angle, 0xFF0000);
		angle += (double)FOV / NUM_RAYS;
		i++;
	}
}

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

void	draw_line(t_img *img, double x, double y, double deg, int color)
{
	double dx = cos(rad(deg));
	double dy = sin(rad(deg));
	double line_x = x;
	double line_y = y;

	while (sqrt((line_x - x) * (line_x - x) + (line_y - y) * (line_y - y)) <= 50)
	{
		line_x += dx;
		line_y += dy;
		my_mlx_pixel_put(img, line_x, line_y, color);
	}
}

void	draw_disk(t_img *img, double xc, double yc, double r, int color)
{
	for (int y = yc - r; y <= yc + r; y++)
		for (int x = xc - r; x <= xc + r; x++)
			if ((x - xc)*(x - xc) + (y - yc)*(y - yc) <= r*r)
				my_mlx_pixel_put(img, x, y, color);
}
