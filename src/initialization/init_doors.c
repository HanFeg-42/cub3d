/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_doors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:57:34 by gstitou           #+#    #+#             */
/*   Updated: 2025/11/26 23:40:34 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void init_doors(t_game *game)
// {
//     int i;
//     int j;
//     int k;

//     game->doors = gc_alloc(sizeof(t_door) * game->door_conter);
//     i = 0;
//     k = 0;
//     while (game->map[i])
//     {
//         j = 0;
//         while (game->map[i][j])
//         {
//             if (game->map[i][j] == 'D')
//             {
//                 game->doors[k].x = j;
//                 game->doors[k].y = i;
//                 game->doors[k].is_open = false;
//                 k++;
//             }
//             j++;
//         }
//         i++;
//     }
// }
