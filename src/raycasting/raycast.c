# include "cub3d.h"

void	init_first_horz_intercept(t_game *game, t_ray *ray, double angle)
{
	ray->yintercept = (int)(game->player.y / SCALE) * SCALE;
	if (angle < 180)
		ray->yintercept += SCALE;
	ray->xintercept = game->player.x
		+ (ray->yintercept - game->player.y) / tan(rad(angle));

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
    if (angle >= 180)
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
	// if (angle < 0)
	// 	return (angle + 360);
	// if (angle > 360)
	// 	return (angle - 360);
	angle = fmod(angle, 360);
    if (angle < 0)
	{
        angle += 360;
	}
	return (angle);
}

// double  get_ray_distance(t_player player, t_ray ray)
// {
//     return (sqrt((ray.wall_hit_x - player.x) * (ray.wall_hit_x - player.x)
//         + (ray.wall_hit_y - player.y) * (ray.wall_hit_y - player.y)));
// }

// t_ray   horz_wall_intersection(t_game *game, double angle)
// {
//     t_ray   ray;
//     double	next_horz_x;
// 	double	next_horz_y;

//     ft_bzero(&ray, sizeof(t_ray));
//     init_first_horz_intercept(game, &ray, angle);
//     init_horz_step(&ray, angle);
//     next_horz_x = ray.xintercept;
//     next_horz_y = ray.yintercept;
//     if (sin(rad(angle)) < 0)// ray facing up
//         next_horz_y--;
//     while (next_horz_x / SCALE  >= 0 && next_horz_x / SCALE < game->width && next_horz_y / SCALE >= 0 && next_horz_y / SCALE  < game->height)
//     {
//         if (game->map[(int)(next_horz_y / SCALE)][(int)(next_horz_x / SCALE)] == '1')
//         {
//             ray.wall_hit_x = next_horz_x;
//             ray.wall_hit_y = next_horz_y;
//             break;
//         }
//         else
//         {
//             next_horz_x += ray.x_step;
//             next_horz_y += ray.y_step;
//         }
//     }
//     if (ray.wall_hit_x && ray.wall_hit_y)
//         line(&game->img, game->player.x, game->player.y, ray.wall_hit_x, ray.wall_hit_y);
//     ray.distance = get_ray_distance(game->player, ray);
//     return (ray);
// }

// void    init_wall_hit_intersection(t_game *game, t_ray *ray, double next_x, double next_y)
// {
//     while (next_x / SCALE  >= 0 && next_x / SCALE < game->width
//         && next_y / SCALE >= 0 && next_y / SCALE  < game->height)
//     {
//         if (game->map[(int)(next_y / SCALE)][(int)(next_x / SCALE)] == '1')
//         {
//             ray->wall_hit_x = next_x;
//             ray->wall_hit_y = next_y;
//             break;
//         }
//         else
//         {
//             next_x += ray->x_step;
//             next_y += ray->y_step;
//         }
//     }
//     if (ray->wall_hit_x && ray->wall_hit_y)
//         line(&game->img, game->player.x, game->player.y, ray->wall_hit_x, ray->wall_hit_y);
//     ray->distance = get_ray_distance(game->player, *ray);
// }

// t_ray   vert_wall_intersection(t_game *game, double angle)
// {
//     t_ray   ray;
//     double	next_vert_x;
// 	double	next_vert_y;

//     ft_bzero(&ray, sizeof(t_ray));
//     init_first_vert_intercept(game, &ray, angle);
//     init_vert_step(&ray, angle);
//     next_vert_x = ray.xintercept;
//     next_vert_y = ray.yintercept;
//     // if (sin(rad(angle)) < 0)// ray facing up
//     //     next_vert_y--;
//     init_wall_hit_intersection(game, &ray, next_vert_x, next_vert_y);
//     return (ray);
// }

void	ray_cast(t_game *game)
{
	t_ray ray[320];
	// t_ray horz_ray;
	// t_ray vert_ray;
	double	angle;
	double	next_horz_x;
	double	next_horz_y;
	int		i;

	// init the t_ray struct
	angle = game->player.angle - FOV / 2;
	i = 0;
	// while (i < 1)
	while (i < NUM_RAYS)
	{
        // horz_ray = horz_wall_intersection(game, angle);
        // vert_ray = vert_wall_intersection(game, angle);
		// angle = normalize_angle(angle);
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
