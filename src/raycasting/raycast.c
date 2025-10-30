# include "cub3d.h"

void	init_first_horz_intercept(t_game *game, t_ray *ray, double angle)
{
	ray->yintercept = (int)(game->player.y / SCALE) * SCALE;
	if (angle < 180)
		ray->yintercept += SCALE;
	ray->xintercept = game->player.x
		+ (ray->yintercept - game->player.y) / tan(rad(angle));
}

void init_horz_step(t_ray *ray, double angle)
{
    ray->y_step = SCALE;
    if (angle >= 180)
        ray->y_step *= -1;
    ray->x_step = SCALE / tan(rad(angle));
    if (cos(rad(angle)) < 0 && ray->x_step > 0)
        ray->x_step *= -1;
    if (cos(rad(angle)) > 0 && ray->x_step < 0)
        ray->x_step *= -1;
}

t_ray   horz_wall_intersection(t_game *game, double angle)
{
    t_ray   ray;
    double	next_horz_x;
	double	next_horz_y;

    init_ray(&ray, angle);
    init_first_horz_intercept(game, &ray, angle);
    init_horz_step(&ray, angle);
    next_horz_x = ray.xintercept;
    next_horz_y = ray.yintercept;
    if (sin(rad(angle)) < 0)// ray facing up
        next_horz_y--;
    init_wall_hit_intersection(game, &ray, next_horz_x, next_horz_y);
    return (ray);
}

void    init_first_vert_intercept(t_game *game, t_ray *ray, double angle)
{
	ray->xintercept = (int)(game->player.x / SCALE) * SCALE;
	if (cos(rad(angle)) > 0)
		ray->xintercept += SCALE;
	ray->yintercept = game->player.y
		+ (ray->xintercept - game->player.x) * tan(rad(angle));
}

void    init_vert_step(t_ray *ray, double angle)
{
    ray->x_step = SCALE;
    if (cos(rad(angle)) < 0)
        ray->x_step *= -1;
    ray->y_step = SCALE * tan(rad(angle));
    if (sin(rad(angle)) < 0 && ray->y_step > 0)
        ray->y_step *= -1;
    if (sin(rad(angle)) > 0 && ray->y_step < 0)
        ray->y_step *= -1;
}

t_ray   vert_wall_intersection(t_game *game, double angle)
{
    t_ray   ray;
    double	next_vert_x;
	double	next_vert_y;

    init_ray(&ray, angle);
    init_first_vert_intercept(game, &ray, angle);
    init_vert_step(&ray, angle);
    next_vert_x = ray.xintercept;
    next_vert_y = ray.yintercept;
    if (cos(rad(angle)) < 0)// ray facing up
        next_vert_x--;
    init_wall_hit_intersection(game, &ray, next_vert_x, next_vert_y);
    return (ray);
}

void	ray_cast(t_game *game)
{
	t_ray ray[320];
	t_ray horz_ray;
	t_ray vert_ray;
	double	angle;
	int		i;

	// init the t_ray struct
	angle = game->player.angle - FOV / 2;
	i = 0;
	while (i < NUM_RAYS)
	{
		angle = normalize_angle(angle);
        horz_ray = horz_wall_intersection(game, angle);
        vert_ray = vert_wall_intersection(game, angle);
        ray[i] = vert_ray;
        if (horz_ray.distance < vert_ray.distance)
            ray[i] = horz_ray;
        line(&game->img, game->player.x, game->player.y, ray[i].wall_hit_x, ray[i].wall_hit_y);
        angle += (double)FOV / NUM_RAYS;
		i++;
	}
}
