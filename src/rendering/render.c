#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_disk(t_img *img, double xc, double yc, double r, int color)
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

void	draw_square(t_img *img, double x, double y, int color)
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

void	init_angle(t_game *game)
{
    game->player.angle += game->player.turn_dir * ROTATION_SPEED;
	while (game->player.angle < 0)
		game->player.angle += 360;
	while (game->player.angle >= 360)
		game->player.angle -=360;
}

void check_move_valid(t_game *game, double new_x, double new_y)
{
    int map_x = (int)(new_x / SCALE);
    int map_y = (int)(new_y / SCALE);
    if (game->map[map_y][map_x] != '1')
    {
        game->player.x = new_x;
        game->player.y = new_y;
    }
}

void    update_player(t_game *game)
{
    double new_x;
    double new_y;
    double y_step;

    init_angle(game);
    y_step = game->player.y_dir * MOVE_SPEED;

    if (game->player.y_dir !=  0)
    {
        new_x = game->player.x + y_step * cos(rad(game->player.angle));
        new_y = game->player.y + y_step * sin(rad(game->player.angle));
    }
    else if (game->player.x_dir != 0)
    {
        new_x = game->player.x + cos(rad(game->player.angle +
            game->player.x_dir * 90)) * MOVE_SPEED;
        new_y = game->player.y + sin(rad(game->player.angle +
            game->player.x_dir * 90)) * MOVE_SPEED;
    }
    else
        return;
    check_move_valid(game, new_x, new_y);
}
// {
//     double x;
//     double y;
//     int x_step;
//     int y_step;

// 	init_angle(game);
//     x_step = game->player.x_dir * MOVE_SPEED;
//     y_step = game->player.y_dir * MOVE_SPEED;
//     x = game->player.x + cos(rad(game->player.angle)) * y_step + x_step;// next player position
//     y = game->player.y + sin(rad(game->player.angle)) * y_step;//
//     if (game->map[(int)y / SCALE][(int)x / SCALE] != '1')
//     {
//         game->player.x = x;
//         game->player.y = y;
//     }
// }

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


int	render_map(t_game *game)
{
    update_player(game);
	// understand this line down
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
	// draw_rays(game);
	ray_cast(game);
	draw_line(&game->img, game->player.x, game->player.y, game->player.angle, 0xFFFF00);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}
