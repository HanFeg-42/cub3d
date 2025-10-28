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
	if (game->player.angle < 0)
		game->player.angle += 360;
	if (game->player.angle > 360)
		game->player.angle -=360;
}

void    update_player(t_game *game)
{
    double x;
    double y;
    int x_step;
    int y_step;

	init_angle(game);
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

void	init_first_horz_intercept(t_game *game, t_ray *ray, double angle)
{
	ray->yintercept = (int)(game->player.y / SCALE) * SCALE;
	if (angle < 180)
		ray->yintercept += SCALE;
	ray->xintercept = game->player.x
		+ (game->player.y - ray->yintercept) / tan(rad(angle));

}

// void	init_horz_step(t_ray *ray, double angle)
// {
// 	ray->y_step = SCALE;
// 	if (sin(rad(angle)) < 0)// hadchi mablanch please normalize the angle
// 		ray->y_step *= -1;
// 	ray->x_step = SCALE / tan(rad(angle));
// 	if ((cos(rad(angle)) < 0 && ray->x_step > 0)
// 		|| (cos(rad(angle)) > 0 && ray->x_step < 0))// cos < 0 == ray facing left
// 		ray->x_step *= -1;
// }

void init_horz_step(t_ray *ray, double angle)
{
    // The angle should be normalized before calling this function
    
    // --- Vertical Step (Y) ---
    // If ray is pointing UP (sin < 0), y_step must be negative (-SCALE)
    ray->y_step = SCALE;
    if (sin(rad(angle)) < 0)
        ray->y_step *= -1;
    
    // --- Horizontal Step (X) ---
    // Calculate the magnitude and correct for a step of SCALE in Y
    ray->x_step = SCALE / tan(rad(angle));
    
    // Check if ray is pointing LEFT (cos < 0) or RIGHT (cos > 0)
    // If ray is facing left, x_step must be negative.
    // If ray is facing right, x_step must be positive.
    if (cos(rad(angle)) < 0 && ray->x_step > 0)
        ray->x_step *= -1;
    if (cos(rad(angle)) > 0 && ray->x_step < 0)
        ray->x_step *= -1;
}

void	line(t_img *img, double x1, double y1, double x2, double y2)
{
	double	dx = x2 - x1;
	double	dy = y2 - y1;
	double	steps = MAX(fabs(dx), fabs(dy));
	double	x_inc = dx / steps;
	double	y_inc = dy / steps;
	int		i = 0;
	while (i < steps)
	{
		my_mlx_pixel_put(img, (int)round(x1), (int)round(y1), 0x212121);
		x1 += x_inc;
		y1 += y_inc;
		i++;
	}
}

double	normalize_angle(double angle)
{
	if (angle < 0)
		return (angle + 360);
	if (angle > 360)
		return (angle - 360);
	return (angle);
}

void	ray_cast(t_game *game)
{
	t_ray ray[320];
	double	angle;
	double	next_horz_x;
	double	next_horz_y;
	int		i;

	ft_bzero(&ray, sizeof(t_ray));
	angle = game->player.angle - FOV / 2;
	i = 0;
	// while (i < NUM_RAYS)
	while (i < 1)
	{
		angle = normalize_angle(angle);
		init_first_horz_intercept(game, &ray[i], angle);
		init_horz_step(&ray[i], angle);
		next_horz_x = ray[i].xintercept;
		next_horz_y = ray[i].yintercept;
		if (sin(rad(angle)) < 0)// ray facing up
			next_horz_y--;
		while (next_horz_x / SCALE  >= 0 && next_horz_x / SCALE < game->width && next_horz_y / SCALE >= 0 && next_horz_y / SCALE  < game->height)
		{
			if (game->map[(int)(next_horz_y / SCALE)][(int)(next_horz_x / SCALE)] == '1')
			{
				ray[i].wall_hit_x = next_horz_x;
				ray[i].wall_hit_y = next_horz_y;
				break;
			}
			else
			{
				next_horz_x += ray[i].x_step;
				next_horz_y += ray[i].y_step;
			}
		}
		if (ray[i].wall_hit_x && ray[i].wall_hit_y)
			line(&game->img, game->player.x, game->player.y, ray[i].wall_hit_x, ray[i].wall_hit_y);
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
