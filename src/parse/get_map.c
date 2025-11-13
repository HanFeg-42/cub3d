/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:10:20 by hfegrach          #+#    #+#             */
/*   Updated: 2025/10/17 20:10:21 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    get_map(t_game *game, int ac, char **av)
{
    char    *line;
    char    *join;
    int     fd;

    if (ac != 2)
        clean_and_exit(game, "Error\nUsage: ./cub3D path_to_map.cub");
    fd = open(av[1], O_RDONLY);

    line = get_next_line(fd);
    join = NULL;
    while (line)
    {
        join = ft_str_join(join, line);
        free(line);
        line = get_next_line(fd);
    }
    game->map = ft_split(join, '\n');
    free(join);
}
