/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 23:52:48 by kali              #+#    #+#             */
/*   Updated: 2025/10/06 20:46:49 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	free_game_data(t_game_data *data)
{
	if (data->no_path)
		free(data->no_path);
	if (data->so_path)
		free(data->so_path);
	if (data->we_path)
		free(data->we_path);
	if (data->ea_path)
		free(data->ea_path);
	if (data->map)
		ft_free_split(data->map);
	if (data->map_path)
		free(data->map_path);
	if (data->join)
		free(data->join);
}

// Function to print t_game_data contents
void	print_game_data(const t_game_data *data)
{
	int	i;

	printf("no_path:    %s\n", data->no_path);
	printf("so_path:    %s\n", data->so_path);
	printf("we_path:    %s\n", data->we_path);
	printf("ea_path:    %s\n", data->ea_path);
	printf("f_rgb:      %d\n", data->f_rgb);
	printf("c_rgb:      %d\n", data->c_rgb);
	if (data->map)
	{
		printf("map:\n");
		i = 0;
		while (data->map[i])
		{
			printf("  %s\n", data->map[i]);
			i++;
		}
	}
	else
		printf("map:        (null)\n");
}

void	my_mlx_pixel_put(t_data *img,int x, int y, int color)
{
	char *dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_square(t_data *img, int x, int y,int color)
{
	for (int i = x; i <=x + SCALE; i++)
		my_mlx_pixel_put(img, i,y,color);
	for (int j = y + 1; j <y + SCALE; j++)
	{
		my_mlx_pixel_put(img, x, j, color);
		for (int i = x + 1; i < x + SCALE; i++)
			my_mlx_pixel_put(img, i, j, 0x808080);
		my_mlx_pixel_put(img, x + SCALE, j, color);
	}
	for (int i = x; i <=x + SCALE; i++)
		my_mlx_pixel_put(img, i,y + SCALE,color);
}

void	eight_circle_points(t_data *img, int cx, int cy, int x, int y, int c)
{
	my_mlx_pixel_put(img, cx + x, cy + y, c);
	my_mlx_pixel_put(img, cx - x, cy + y, c);
	my_mlx_pixel_put(img, cx + x, cy - y, c);
	my_mlx_pixel_put(img, cx - x, cy - y, c);
	my_mlx_pixel_put(img, cx + y, cy + x, c);
	my_mlx_pixel_put(img, cx - y, cy + x, c);
	my_mlx_pixel_put(img, cx + y, cy - x, c);
	my_mlx_pixel_put(img, cx - y, cy - x, c);
}

void	draw_circle(t_data *img, int xc, int yc, int r, int color)
{
	int x = 0;
	int y = r;
	int p = 1 - r;

	eight_circle_points(img, xc, yc, x, y, color);
	while (x <= y)
	{
		x++;
		if (p < 0)
			p += 2 * x + 1;
		else
		{
			y--;
			p += 2 * (x - y) + 1;
		}
		eight_circle_points(img, xc, yc, x, y, color);
	}
}

void	draw_line(t_data *img, int c, int px, int py)
{
	int dx, dy;
	int x, y;

	if (c == 'N'){dx = NX; dy = NY;}
	if (c == 'S'){dx = SX; dy = SY;}
	if (c == 'E'){dx = EX; dy = EY;}
	if (c == 'W'){dx = WX; dy = WY;}

	for (int i = 0; i <= 25; i++)
	{
		x = px + dx * i;
		y = py + dy * i;
		my_mlx_pixel_put(img, x, y, 0xFFFF00);
	}
}

void	draw_map(t_game_data *data, t_data *img)
{
	int	i = 0;
	int j;

	if (data->map)
	{
		i = 0;
		while (data->map[i])
		{
			j = 0;
			while (data->map[i][j])
			{
				if (data->map[i][j] == '1')
					draw_square(img, j * SCALE, i * SCALE, 0x00FF0000);
				if (data->map[i][j] != '1' && data->map[i][j] != '0')
				{
					draw_circle(img, j * SCALE + SCALE/2, i * SCALE + SCALE/2, 5, 0x000000FF);
					draw_line(img, data->map[i][j], j * SCALE + SCALE/2, i * SCALE + SCALE/2);
				}
				j++;
			}
			i++;
		}
	}
}

int	main(int ac, char **av)
{
	t_game_data	data;
	void *mlx;
	void *win;
	t_data img;

	if (!parse_args(ac, av, &data))
		return (1);
	mlx = mlx_init();
	win = mlx_new_window(mlx, 800,600, "kiwi");
	img.img = mlx_new_image(mlx, 800, 600);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	//my_mlx_pixel_put(&img, 5,5,0x00FF0000);
	// draw_square(&img, 200, 100, 0x00FF0000);
	// draw_circle(&img, 500, 450, 25, 0x00FF00FF);
	//draw_triangle();
	draw_map(&data, &img);
	mlx_put_image_to_window(mlx, win, img.img, 0,0);
	print_game_data(&data);
	free_game_data(&data);
	mlx_loop(mlx);
	return (0);
}
