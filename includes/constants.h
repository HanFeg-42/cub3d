/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 15:27:39 by hfegrach          #+#    #+#             */
/*   Updated: 2025/11/29 15:49:46 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

/* Window & Display Settings */
# define WINDOW_WIDTH       1500
# define WINDOW_HEIGHT      1000
# define SCALE              32
# define FOV                60
# define NUM_RAYS           WINDOW_WIDTH
# define WALL_STRIP_WIDTH   1

/* Minimap Settings */
# define MM_FACTOR                  0.2
# define WALLSTRIP_SCALE_FACTOR     0.5
# define MARGIN                     5

/* Player Movement */
# define MOVE_SPEED         2
# define ROTATION_SPEED     1
# define SENSITIVITY        0.008
# define DOOR_DIST          1.3

/* Color Definitions */
# define RED            0xFF0000
# define GREEN          0x00FF00
# define BLUE           0x0000FF
# define WHITE          0xFFFFFF
# define BLACK          0x000000
# define GRAY           0x505050
# define MAGIC_PINK     0xFF00FF
# define MINIMAP_COLOR  0xC8C8C8
# define PLAYER_COLOR   0x64FF64
# define DOOR_COLOR     BLUE
# define OPEN_DOOR_COLOR 0xC0E8FF

/* Texture & Animation */
# define NUM_TEXTURES       4
# define NUM_FRAME_SHOT     10
# define NUM_FRAME_MOVE     22
# define NUM_DOOR_FRAME     15
# define ANIM_SPEED         2
# define GUN_SCALE          1

/* Direction Constants */
# define NORTH  0
# define EAST   1
# define SOUTH  2
# define WEST   3

/* Collision Detection */
# define HORZ   1
# define VERT   0

/* Utility Macros */
# define BUFFER_SIZE        32
# define _USE_MATH_DEFINES

#endif