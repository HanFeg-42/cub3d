/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:10:13 by hfegrach          #+#    #+#             */
/*   Updated: 2025/10/17 22:13:50 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	print_map(t_game *game)
{
	int i = 0;
	if (game->map)
	{
		printf("map:\n");
		while (game->map[i])
			printf("  %s\n", game->map[i++]);
	}
}
int	close_window(t_game *game)
{
	mlx_loop_end(game->mlx);
	return (0);
}

// void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
// {
// 	char *dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
// 	*(unsigned int *)dst = color;
// }

// void	draw_disk(t_img *img, int xc, int yc, int r, int color)
// {
// 	for (int y = yc - r; y <= yc + r; y++)
// 		for (int x = xc - r; x <= xc + r; x++)
// 			if ((x - xc)*(x - xc) + (y - yc)*(y - yc) <= r*r)
// 				my_mlx_pixel_put(img, x, y, color);
// }

// double rad(double deg)
// {
// 	return (deg * M_PI / 180);
// }

// void	draw_line(t_img *img, double x, double y, int deg, int color)
// {
// 	double dx = cos(rad(deg));
// 	double dy = sin(rad(deg));
// 	double line_x = x;
// 	double line_y = y;

// 	while (sqrt((line_x - x) * (line_x - x) + (line_y - y) * (line_y - y)) <= 30)
// 	{
// 		line_x += dx;
// 		line_y += dy;
// 		my_mlx_pixel_put(img, line_x, line_y, color);
// 	}
// }

// void	draw_square(t_img *img, int x, int y, int color)
// {
// 	int i;
// 	int j;

// 	i = y + 1;
// 	while (i < y + SCALE)
// 	{
// 		j = x + 1;
// 		while (j < x + SCALE)
// 		{
// 			my_mlx_pixel_put(img, j, i, color);
// 			j++;
// 		}
// 		i++;
// 	}
// }

// int	render_map(t_game *game)
// {
// 	ft_memset(game->img.addr, 0, game->img.line_length * (game->height * SCALE));
// 	for (int i = 0; game->map[i]; i++)
// 		for (int j = 0; game->map[i][j]; j++)
// 		{
// 			if (game->map[i][j] == '1')
// 				draw_square(&game->img, j * SCALE, i * SCALE, 0x0000FF);
// 			else
// 				draw_square(&game->img, j * SCALE, i * SCALE, 0xFFFFFF);
// 		}
// 	draw_disk(&game->img, game->player.x, game->player.y, 5, 0xFF0000);
// 	draw_line(&game->img, game->player.x, game->player.y, game->player.angle, 0xFF0000);
// 	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
// 	return (0);
// }

int main(int ac, char **av)
{
	t_game	*game;

	game = init_game();
	get_map(game, ac, av);
	get_game(game);
	print_map(game);
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_hook(game->win, 2, (1L << 0), key_press, game);
	mlx_hook(game->win, 3, (1L << 1), key_release, game);
	mlx_loop_hook(game->mlx, render_map, game);
	mlx_loop(game->mlx);
	exit_game(game, NULL);
	return (0);
}
