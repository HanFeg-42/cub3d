/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 11:30:28 by hfegrach          #+#    #+#             */
/*   Updated: 2025/11/08 20:31:30 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	init_parser(t_parse *parser)
{
	ft_bzero(parser, sizeof(t_parse));
}

static int is_file_ext_valid(char *filename)
{
	char	*ext;

	ext = ft_strrstr(filename, ".cub");
	return (!ext || ft_strlen(ext) != 4);
}

static void	open_file(t_game *game, t_parse *parser, char *filename)
{
	if (is_file_ext_valid(filename) == FALSE)
		exit_game(game, UNVALID_EXTENTION, EXIT_FAILURE);
	parser->fd = open(filename, O_RDONLY);
	if (parser->fd == -1)
		exit_game(game, OPEN_FILE, EXIT_FAILURE);
}

// void	load_config_line(t_parse *parser, char *line)
// {
	
// }

// void	load_map_line(t_parse *parser, char *line)
// {}

static void	read_file(t_parse *parser)
{
	char	*line;

	line = get_next_line(parser->fd);
	while (line && !ft_strchr(" 1", line[0]))
	{
		// load_config_line(parser, line);
		parser->join_config = gc_strjoin(parser->join_config, line);
		free_one(line);
		line = get_next_line(parser->fd);
	}
	while (line)
	{
		// load_map_line(parser, line);
		parser->join_map = gc_strjoin(parser->join_map, line);
		free_one(line);
		line = get_next_line(parser->fd);
	}
	return ;
}

void	parse_config(t_game *game, t_parse *parser)
{
	int i;

	parser->config = gc_split(parser->join_config, '\n');
	i = 0;
	while (parser->config[i])
	{
		if (strchr("NSWE", parser->config[i][0]))
			parse_texture(game, parser);
		else if (strchr("FC", parser->config[i][0]))
			parse_color(game, parser);
		else
			exit_game(game, UNVALID_CONFIG, EXIT_FAILURE);
		i++;
	}
}

void    parse_input(t_game *game, int ac, char **av)
{
	t_parse parser;

	if (ac != 2)
		exit_game(game, UNVALID_ARG, EXIT_FAILURE);
	init_parser(&parser);
	open_file(game, &parser, av[1]);
	read_file(&parser);
	parse_config(game, &parser);
	// parse_map(game, &parser);
}
