#include "includes/cub3D.h"

void	free_game_data(t_game_data *data)
{
	if (data->no_path) free(data->no_path);
	if (data->so_path) free(data->so_path);
	if (data->we_path) free(data->we_path);
	if (data->ea_path) free(data->ea_path);
	if (data->map) ft_free_split(data->map);
	if (data->map_path) free(data->map_path);
	if (data->join) free(data->join);
}

void	print_game_data(const t_game_data *data)
{
	int	i = 0;

	printf("no_path:    %s\n", data->no_path);
	printf("so_path:    %s\n", data->so_path);
	printf("we_path:    %s\n", data->we_path);
	printf("ea_path:    %s\n", data->ea_path);
	printf("f_rgb:      %d\n", data->f_rgb);
	printf("c_rgb:      %d\n", data->c_rgb);
	if (data->map)
	{
		printf("map:\n");
		while (data->map[i])
			printf("  %s\n", data->map[i++]);
	}
	else
		printf("map:        (null)\n");
}

/* ✅ FIXED: added safety checks for bounds */
void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return;
	char *dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_square(t_img *img, int x, int y, int color)
{
	// for (int i = x; i <= x + SCALE; i++)
	// 	my_mlx_pixel_put(img, i, y, color);
	for (int j = y + 1; j < y + SCALE; j++)
	{
		// my_mlx_pixel_put(img, x, j, color);
		for (int i = x + 1; i < x + SCALE; i++)
			my_mlx_pixel_put(img, i, j, color);
		// my_mlx_pixel_put(img, x + SCALE, j, color);
	}
	// for (int i = x; i <= x + SCALE; i++)
	// 	my_mlx_pixel_put(img, i, y + SCALE, color);
}

void	eight_circle_points(t_img *img, int cx, int cy, int x, int y, int c)
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

void	draw_disk(t_img *img, int xc, int yc, int r, int color)
{
	for (int y = yc - r; y <= yc + r; y++)
		for (int x = xc - r; x <= xc + r; x++)
			if ((x - xc)*(x - xc) + (y - yc)*(y - yc) <= r*r)
				my_mlx_pixel_put(img, x, y, color);
}

void	draw_circle(t_img *img, int xc, int yc, int r, int color)
{
	int x = 0, y = r, p = 1 - r;

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

/* ✅ Uses the fixed safe pixel_put */
void	draw_line(t_img *img, int c, int px, int py)
{
	int dx = 0, dy = 0;

	if (c == 'N'){dx = NX; dy = NY;}
	if (c == 'S'){dx = SX; dy = SY;}
	if (c == 'E'){dx = EX; dy = EY;}
	if (c == 'W'){dx = WX; dy = WY;}

	for (int i = 0; i <= 25; i++)
		my_mlx_pixel_put(img, px + dx * i, py + dy * i, 0xFF0000);
}

void	clear_image(t_game_data *data)
{
	for (int y = 0; y < data->height; y++)
		for (int x = 0; x < data->width; x++)
			my_mlx_pixel_put(&data->img, x, y, 0x000000);
}

double rad(double deg)
{
	return (deg * M_PI / 180);
}
void draw_ray(t_game_data *data)
{
	double dx = cos(rad(data->player.angle));
	double dy = sin(rad(data->player.angle));
	double ray_x = (double)data->player.x;
	double ray_y = (double)data->player.y;

	while (data->map[(int)(ray_y / SCALE)][(int)(ray_x / SCALE)] != '1')
	{
		ray_x += dx * SPEED - 3;
		ray_y += dy * SPEED - 3;
	}
	draw_disk(&data->img, ray_x, ray_y, 5, 0x000000);
}

int	draw_map(t_game_data *data)
{
	if (!data->map) return (0);
	ft_memset(data->img.addr, 0, data->img.line_length * (data->height * SCALE));
	for (int i = 0; data->map[i]; i++)
		for (int j = 0; data->map[i][j]; j++)
		{
			if (data->map[i][j] == '1')
				draw_square(&data->img, j * SCALE, i * SCALE, 0x0000FF);
			else
				draw_square(&data->img, j * SCALE, i * SCALE, 0xFFFFFF);
		}
	draw_disk(&data->img, data->player.x, data->player.y, 10, 0x00FF00);
	draw_ray(data);
	// draw_line(&data->img,
	// 	data->map[(data->player.y - SCALE / 2) / SCALE][(data->player.x - SCALE / 2) / SCALE],
	// 	data->player.x, data->player.y);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}

static int player_angle(int c)
{
	if (c == 'N') return (270);
	else if (c == 'S') return (90);
	else if (c == 'E') return (0);
	else return (180);
}

static void	player_pos(t_game_data *data)
{
	for (int y = 0; data->map[y]; y++)
		for (int x = 0; data->map[y][x]; x++)
			if (ft_strchr("NWSE", data->map[y][x]))
			{
				data->player.x = x * SCALE + SCALE / 2;
				data->player.y = y * SCALE + SCALE / 2;
				data->player.angle = player_angle(data->map[y][x]);
				printf("hello player pos, ANGLE: %d\n", data->player.angle);
			}
}

/* ✅ FIXED: correctly computes width/height */
static void	init_img(t_game_data *data)
{
	data->width = 0;
	data->height = 0;

	for (int y = 0; data->map[y]; y++)
	{
		int row_len = 0;
		while (data->map[y][row_len])
			row_len++;
		if (row_len > data->width)
			data->width = row_len;
		data->height++;
	}
}

void	move_player(char m, t_game_data *data)
{
	if (m == 'U')
		data->player.y -= SPEED;
	if (m == 'D')
		data->player.y += SPEED;
	if (m == 'L')
		data->player.x -= SPEED;
	if (m == 'R')
		data->player.x += SPEED;
}

void	rotate_player(char r, t_game_data *data)
{
	if (r == 'L')
		data->player.angle -= SPEED;
	if (r == 'R')
		data->player.angle += SPEED;
}


int	key_press(int key, t_game_data *data)
{
	if (key == XK_w)
		move_player('U', data);
	else if (key == XK_s)
		move_player('D', data);
	else if (key == XK_d)
		move_player('R', data);
	else if (key == XK_a)
		move_player('L', data);
	else if (key == XK_Left)
		rotate_player('L', data);
	else if (key == XK_Right)
		rotate_player('R', data);
	return (0);
}

int	main(int ac, char **av)
{
	t_game_data	data;

	parse_args(ac, av, &data);
	init_img(&data);
	player_pos(&data);

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.width * SCALE, data.height * SCALE, "kiwi");

	data.img.img = mlx_new_image(data.mlx, data.width * SCALE, data.height * SCALE);
	data.img.addr = mlx_get_img_addr(data.img.img,
		&data.img.bits_per_pixel, &data.img.line_length, &data.img.endian);
	
	data.img.width = data.width * SCALE;
	data.img.height = data.height * SCALE;

	draw_map(&data);
	print_game_data(&data);

	mlx_hook(data.win, 2, (1L << 0), key_press, &data);
	mlx_loop_hook(data.mlx, draw_map, &data);
	mlx_loop(data.mlx);
	return (0);
}
