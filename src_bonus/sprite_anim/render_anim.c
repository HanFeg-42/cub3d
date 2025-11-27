/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_anim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 18:49:02 by gstitou           #+#    #+#             */
/*   Updated: 2025/11/27 15:37:24 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int mouse_click(int button , int x, int y, t_game *game)
{
	(void) x;
	(void) y;
	
	if(button == 1)
	{
		if (game->player.is_shooting == false)
		{
			game->player.is_shooting = true;
			game->gun.current_frame = 0;
		}	
	}
	else if(button == 2)
		check_door_interaction(game);
	return (0);
}

void	update_animation(t_game *game)
{
	if (game->player.is_shooting)
	{
			game->gun.current_frame++;
			if (game->gun.current_frame >= NUM_FRAME_SHOT)
			{
				game->gun.current_frame = 0;
				game->player.is_shooting = false;
			}
		
	}
	else if (game->player.is_moving)
	{
			game->gun.current_frame++;
			if (game->gun.current_frame >= NUM_FRAME_MOVE)
				game->gun.current_frame = 0;
		}
	
	else
		game->gun.current_frame = 0;
}

t_img	*get_right_frame(t_game *game)
{
	if (game->player.is_shooting)
		return (&game->gun.shot[game->gun.current_frame]);
	else if (game->player.is_moving)
		return (&game->gun.move[game->gun.current_frame]);
	else
		return (&game->gun.idle);
}

void	draw_anim_texture(t_game *game, t_img *frame, int drawn_height,
		int drawn_width)
{
	int	x;
	int	y;
	int	screen_x;
	int	screen_y;
	int	color;

	screen_y = WINDOW_HEIGHT - drawn_height;
	screen_x = 0;
	y = 0;
	while (y < drawn_height)
	{
		x = 0;
		while (x < drawn_width)
		{
			color = get_texture_pixel_color(frame, x * GUN_SCALE, y
					* GUN_SCALE);
			if (color != MAGIC_PINK && screen_x + x >= 0
				&& screen_x + x < WINDOW_WIDTH
				&& screen_y + y >= 0 && screen_y + y < WINDOW_HEIGHT)
				my_mlx_pixel_put(&game->img, screen_x + x, screen_y + y, color);
			x++;
		}
		y++;
	}
}

void	render_animation(t_game *game)
{
	t_img	*frame;
	int		drawn_height;
	int		drawn_width;

	frame = get_right_frame(game);
	drawn_width = frame->width / GUN_SCALE;
	drawn_height = frame->height / GUN_SCALE;
	draw_anim_texture(game, frame, drawn_height, drawn_width);
}
