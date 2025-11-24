/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 12:07:24 by hfegrach          #+#    #+#             */
/*   Updated: 2025/11/24 20:56:39 by gstitou          ###   ########.fr       */
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

static void	check_map_shape(t_game *game, char *map)
{
	char	*tmp_line;
	char	*nl_pos;
	char	*next_nl_pos;

	tmp_line = map;
	while (tmp_line && *tmp_line)
	{
		nl_pos = ft_strchr(tmp_line, '\n');
		if (!nl_pos)
			break ;
		next_nl_pos = ft_strchr(nl_pos + 1, '\n');
		if (!next_nl_pos)
			break ;
		tmp_line = gc_substr(nl_pos, 0, next_nl_pos - nl_pos);
		tmp_line = gc_strtrim(tmp_line, " \n");
		if (tmp_line[0] == '\0')
			exit_game(game, ERROR_EMPTY_LINE, EXIT_FAILURE);
		tmp_line = next_nl_pos + 1;
	}
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
				parser->is_player = EXIST;
			else if (ptr && parser->is_player == EXIST)
				exit_game(game, ERROR_MULTIPLE_PLAYERS, EXIT_FAILURE);
			x++;
		}
		y++;
	}
	if (parser->is_player != EXIST)
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
			if (ft_strchr("NSWED0", parser->map[y][x])
					&& has_adjacent_space(parser, x, y))
				exit_game(game, ERROR_INVALID_MAP, EXIT_FAILURE);
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
	check_map_shape(game, map_str);
	parser->map = gc_split(map_str, '\n');
	check_player(game, parser);
	check_map_walls(game, parser);
	game->map = ft_split(parser->join_map, '\n');
}
