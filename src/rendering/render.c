#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_disk(t_img *img, int xc, int yc, int r, int color)
{
	for (int y = yc - r; y <= yc + r; y++)
		for (int x = xc - r; x <= xc + r; x++)
			if ((x - xc)*(x - xc) + (y - yc)*(y - yc) <= r*r)
				my_mlx_pixel_put(img, x, y, color);
}

double rad(double deg)
{
	return (deg * M_PI / 180);
}

void	draw_line(t_img *img, double x, double y, int deg, int color)
{
	double dx = cos(rad(deg));
	double dy = sin(rad(deg));
	double line_x = x;
	double line_y = y;

	while (sqrt((line_x - x) * (line_x - x) + (line_y - y) * (line_y - y)) <= 30)
	{
		line_x += dx;
		line_y += dy;
		my_mlx_pixel_put(img, line_x, line_y, color);
	}
}

void	draw_square(t_img *img, int x, int y, int color)
{
	int i;
	int j;

	i = y + 1;
	while (i < y + SCALE)
	{
		j = x + 1;
		while (j < x + SCALE)
		{
			my_mlx_pixel_put(img, j, i, color);
			j++;
		}
		i++;
	}
}

void    update_player(t_game *game)
{
    double x;
    double y;
    int x_step;
    int y_step;

    game->player.angle += game->player.turn_dir * ROTATION_SPEED;
    x_step = game->player.x_dir * MOVE_SPEED;
    y_step = game->player.y_dir * MOVE_SPEED;
    x = game->player.x + cos(rad(game->player.angle)) * y_step + x_step;// next player position
    y = game->player.y + sin(rad(game->player.angle)) * y_step;//
    if (game->map[(int)y / SCALE][(int)x / SCALE] != '1')
    {
        game->player.x = x;
        game->player.y = y;
    }
}

int	render_map(t_game *game)
{
    update_player(game);
	ft_memset(game->img.addr, 0, game->img.line_length * (game->height * SCALE));
	for (int i = 0; game->map[i]; i++)
		for (int j = 0; game->map[i][j]; j++)
		{
			if (game->map[i][j] == '1')
				draw_square(&game->img, j * SCALE, i * SCALE, 0x0000FF);
			else
				draw_square(&game->img, j * SCALE, i * SCALE, 0xFFFFFF);
		}
	draw_disk(&game->img, game->player.x, game->player.y, 5, 0xFF0000);
	draw_line(&game->img, game->player.x, game->player.y, game->player.angle, 0xFF0000);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}
