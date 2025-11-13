/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 15:39:40 by gstitou           #+#    #+#             */
/*   Updated: 2025/11/12 15:22:59 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_textured_column(t_game *game, t_tex *tex, int i)
{
	int y;
	int x;
	int tex_y;
	int color;

	y = tex->draw_start;

	while (y < tex->draw_end)
	{
		tex_y = (int)tex->tex_pos;
		if(tex_y < 0)
			tex_y = 0;
		color = get_texture_pixel_color(tex->tex_img, tex->tex_x, tex_y);
		x = i;
		while (x < i + WALL_STRIP_WIDTH)
		{
			my_mlx_pixel_put(&game->img, x, y, color);

			x++;
		}
		tex->tex_pos += tex->step;
		y++;
	}
}

void draw_floor(t_game *game,t_tex tex, int x)
{
	int y;
	y = tex.draw_end;

	while ( y < WINDOW_HEIGHT)
	{
		my_mlx_pixel_put(&game->img,x,y,0x46413C);
		y++;
	}	
}
void draw_ceiling(t_game *game ,t_tex tex, int x)
{
	int y;
	y = 0;

	while ( y < tex.draw_start)
	{
		my_mlx_pixel_put(&game->img,x,y,0x23232D);
		y++;
	}	
}
void texture_mapping_and_draw(t_game *game, t_ray ray, int i, double wall_h)
{
	t_tex tex;

	ft_bzero(&tex, sizeof(t_tex));

	tex.tex_img = get_correct_texture(game, ray);
	calculate_horz_map(game, ray, &tex);
	calculate_vert_map(&tex, wall_h);
	draw_ceiling(game,tex,i);
	draw_floor(game,tex,i);
	draw_textured_column(game, &tex, i);
}