#include "cub3d.h"

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
		my_mlx_pixel_put(img, (int)round(x1), (int)round(y1), 0xFF0000);
		x1 += x_inc;
		y1 += y_inc;
		i++;
	}
}

double	normalize_angle(double angle)
{
	while (angle < 0)
    {
        angle += 360.0;
    }
    while (angle >= 360)
    {
        angle -= 360.0;
    }
	return (angle);
}
double  get_ray_distance(t_player player, t_ray ray)
{
    if (ray.wall_hit_x && ray.wall_hit_y)
        return (sqrt((ray.wall_hit_x - player.x) * (ray.wall_hit_x - player.x)
            + (ray.wall_hit_y - player.y) * (ray.wall_hit_y - player.y)));
    return (10000); // m sorry
}

// int has_wall_at(t_game *game, t_ray *ray, double next_x, double next_y)
// {
//     if ()
// }

void    init_wall_hit_intersection(t_game *game, t_ray *ray, double next_x, double next_y)
{
    while (next_x / SCALE  >= 0 && next_x / SCALE < game->width
        && next_y / SCALE >= 0 && next_y / SCALE  < game->height)
    {
        // if (has_wall_at(game, ray, next_x, next_y))
        if (game->map[(int)(next_y / SCALE)][(int)(next_x / SCALE)] == '1')
        {
            ray->wall_hit_x = next_x;
            ray->wall_hit_y = next_y;
            break;
        }
        else
        {
            next_x += ray->x_step;
            next_y += ray->y_step;
        }
    }
    ray->distance = get_ray_distance(game->player, *ray);
}

void    init_ray(t_ray *ray, double angle)
{
    ft_bzero(ray, sizeof(t_ray));
    ray->angle = angle;
    if (angle > 180)
        ray->is_facing_up = 1;
    if (angle > 90 && angle < 270)
        ray->is_facing_right = 1;
}
