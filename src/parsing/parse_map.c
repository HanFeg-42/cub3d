/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 23:45:59 by kali              #+#    #+#             */
/*   Updated: 2025/07/27 23:50:42 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

// TODO : load each line to the map array for the moment
// find a way to handle newlines in between
// and make sure it is encountered by walls
// no 0 are facing the outside
void	map_line_loader(char *line, t_game_data *data)
{
	data->join = ft_str_join(data->join, line);
}

void	init_map_matrix(t_game_data *data)
{
	data->map = ft_split(data->join, '\n');
}
