/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 12:07:24 by hfegrach          #+#    #+#             */
/*   Updated: 2025/12/01 09:49:14 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	check_map_elements(t_game *game, char *map)
{
	int	i;

	i = 0;
	while (map[i] && ft_strchr("01DNSEW \n", map[i]))
		i++;
	if (map[i] != '\0')
		exit_game(game, ERROR_INVALID_ELEMENT, EXIT_FAILURE);
}

static void	check_player(t_game *game, t_parse *parser)
{
	char	*ptr;
	int		x;
	int		y;

	y = 0;
	while (parser->map[y])
	{
		x = 0;
		while (parser->map[y][x])
		{
			ptr = ft_strchr("NWSE", parser->map[y][x]);
			if (ptr && !parser->is_player)
				parser->is_player = 1;
			else if (ptr && parser->is_player == 1)
				exit_game(game, ERROR_MULTIPLE_PLAYERS, EXIT_FAILURE);
			x++;
		}
		y++;
	}
	if (parser->is_player != 1)
		exit_game(game, ERROR_NO_PLAYER, EXIT_FAILURE);
}

static void	check_map_walls(t_game *game, t_parse *parser)
{
	int	x;
	int	y;

	y = 0;
	while (parser->map[y])
	{
		x = 0;
		while (parser->map[y][x])
		{
			if (ft_strchr("NSWE0D", parser->map[y][x])
				&& has_adjacent_space(parser, x, y))
				exit_game(game, ERROR_INVALID_MAP, EXIT_FAILURE);
			if (parser->map[y][x] == 'D')
			{
				if (!is_door_valid(parser, x, y))
					exit_game(game, ERROR_INVALID_DOOR, EXIT_FAILURE);
			}
			x++;
		}
		y++;
	}
}

void	parse_map(t_game *game, t_parse *parser)
{
	char	*map_str;

	map_str = gc_strtrim(parser->join_map, "\n");
	check_map_elements(game, map_str);
	parser->map = gc_split(map_str, '\n');
	check_player(game, parser);
	check_map_walls(game, parser);
	game->map = ft_split(parser->join_map, '\n');
}
