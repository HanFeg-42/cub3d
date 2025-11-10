/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 12:07:24 by hfegrach          #+#    #+#             */
/*   Updated: 2025/11/10 13:35:39 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void    check_map_elements(t_game *game, char *map)
{
    int i;

    i = 0;
    while(map[i] && ft_strchr("01NSEW \n", map[i]))
        i++;
    if (map[i] != '\0')
        exit_game(game, UNVALID_ELEMENT, EXIT_FAILURE);
}

void    check_map_shape(t_game *game, char *map)
{
    char    *tmp_line;
    char    *nl_pos;
    char    *next_nl_pos;

    tmp_line = map;
    while (tmp_line && *tmp_line)
    {
        nl_pos = ft_strchr(tmp_line, '\n');
        next_nl_pos = ft_strchr(nl_pos + 1, '\n');
        if (nl_pos && next_nl_pos)
        {
            tmp_line = gc_substr(nl_pos, 0, next_nl_pos - nl_pos);
            tmp_line = gc_strtrim(tmp_line, " \n");
            if (tmp_line[0] == '\0')
                exit_game(game, EMPTY_LINE, EXIT_FAILURE);
            tmp_line = next_nl_pos + 1;
        }
        else
            break;
    }
}

void    check_player(t_game *game, t_parse *parser)
{
    char    *ptr;
    int x;
    int y;

    y = 0;
    while (parser->map[y])
    {
        x = 0;
        while (parser->map[y][x])
        {
            ptr = ft_strchr("NWSE", parser->map[y][x]);
            if (ptr && !parser->is_player )
                parser->is_player = EXIST;
            else if (ptr && parser->is_player == EXIST)
                exit_game(game, DOUBLED_PLAYER, EXIT_FAILURE);
            x++;
        }
        y++;
    }
}


void    parse_map(t_game *game, t_parse *parser)
{
    char *map_str;

    map_str = gc_strtrim(parser->join_map, "\n");
    check_map_elements(game, map_str);
    // check_map_shape(game, map_str);
    parser->map = gc_split(map_str, '\n');
    check_player(game, parser);
    
    // check_map_walls(game);
    // also check if there is only one player

    game->map = ft_split(parser->join_map, '\n');
}
