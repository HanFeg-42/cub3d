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
