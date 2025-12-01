/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 11:30:28 by hfegrach          #+#    #+#             */
/*   Updated: 2025/12/01 10:22:02 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	open_file(t_game *game, t_parse *parser, char *filename)
{
	if (is_file_ext_valid(filename, ".cub") == FALSE)
		exit_game(game, ERROR_INVALID_EXTENSION, EXIT_FAILURE);
	parser->fd = open(filename, O_RDONLY);
	if (parser->fd == -1)
		exit_game(game, ERROR_FILE_OPEN_FAILED, EXIT_FAILURE);
}

static void	read_file(t_game *game, t_parse *parser)
{
	char	*line;

	line = get_next_line(parser->fd);
	if (!line)
		exit_game(game, ERROR_EMPTY_FILE, EXIT_FAILURE);
	while (line && !ft_strchr("1", gc_strtrim(line, " ")[0]))
	{
		parser->join_config = gc_strjoin(parser->join_config, line);
		free_one(line);
		line = get_next_line(parser->fd);
	}
	while (line)
	{
		if (line[0] == '\n' || gc_strtrim(line, " ")[0] == '\n')
			exit_game(game, ERROR_EMPTY_LINE, EXIT_FAILURE);
		parser->join_map = gc_strjoin(parser->join_map, line);
		free_one(line);
		line = get_next_line(parser->fd);
	}
	return ;
}

static void	parse_config(t_game *game, t_parse *parser)
{
	int		i;
	char	*trim;

	parser->config = gc_split(parser->join_config, '\n');
	if (!parser->config)
		exit_game(game, ERROR_INVALID_CONFIG, EXIT_FAILURE);
	i = 0;
	while (parser->config[i])
	{
		trim = gc_strtrim_all(parser->config[i], " ");
		if (trim[0] == '\0')
		{
			i++;
			continue ;
		}
		if (ft_strchr("NSWE", trim[0]))
			parse_texture(game, parser->config[i]);
		else if (ft_strchr("FC", trim[0]))
			parse_color(game, trim, parser->config[i]);
		else
			exit_game(game, ERROR_INVALID_CONFIG, EXIT_FAILURE);
		i++;
	}
	is_all_config_loaded(game);
}

void	parse_input(t_game *game, int ac, char **av)
{
	t_parse	parser;

	if (ac != 2)
		exit_game(game, ERROR_INVALID_ARGS, EXIT_FAILURE);
	ft_bzero(&parser, sizeof(t_parse));
	open_file(game, &parser, av[1]);
	read_file(game, &parser);
	parse_config(game, &parser);
	parse_map(game, &parser);
	free_all();
}
