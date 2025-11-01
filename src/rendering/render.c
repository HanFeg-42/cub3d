#include "cub3d.h"


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

void    render_minimap(t_game *game)
{
	for (int i = 0; game->map[i]; i++)
		for (int j = 0; game->map[i][j]; j++)
		{
			if (game->map[i][j] == '1')
				draw_square(
                    &game->img,
                    j * SCALE * MINIMAP_SCALE_FACTOR,
                    i * SCALE * MINIMAP_SCALE_FACTOR,
                    0x0000FF
                );
			else
				draw_square(
                    &game->img,
                    j * SCALE * MINIMAP_SCALE_FACTOR,
                    i * SCALE * MINIMAP_SCALE_FACTOR,
                    0xFFFFFF
                );
		}
	draw_disk(
        &game->img,
        game->player.x * MINIMAP_SCALE_FACTOR,
        game->player.y * MINIMAP_SCALE_FACTOR,
        3,
        0xFF0000
    );
}

void    render_proj_wall(t_game *game, double wall_height, int i)
{
    double x;
    double y;

    x = i * WALL_STRIP_WIDTH;
    y = (WINDOW_HEIGHT / 2) - (wall_height / 2);
    draw_rect(&game->img, x, y, wall_height);
}

void    proj_walls(t_game *game)
{
    int i;
    double  dist_proj_plane;
    double  wall_strip_height;

    i = 0;
    while (i < NUM_RAYS)
    {
        dist_proj_plane = (WINDOW_WIDTH / 2) / tan(FOV / 2);
        wall_strip_height = (SCALE / game->ray[i].distance) * dist_proj_plane;
        printf("wall height = %f\n", wall_strip_height);
        render_proj_wall(game, fabs(wall_strip_height), i);
        i++;
    }
}

int	render_game(t_game *game)
{
    update_player(game);
	// understand this line down
	ft_memset(game->img.addr, 0, game->img.line_length * (game->height * SCALE));
    render_minimap(game);
	ray_cast(game);
    proj_walls(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}
