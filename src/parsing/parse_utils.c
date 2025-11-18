/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 11:30:28 by hfegrach          #+#    #+#             */
/*   Updated: 2025/11/18 15:07:55 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	is_file_ext_valid(char *filename, char *right_ext)
{
	char	*ext;

	ext = ft_strrstr(filename, right_ext);
	return (!ext || ft_strlen(ext) != 4);
}

void	is_all_config_loaded(t_game *game)
{
	if (
		!game->config.ea
		|| !game->config.no
		|| !game->config.so
		|| !game->config.we
	)
		exit_game(game, ERROR_MISSING_TEXTURE, EXIT_FAILURE);
	if (game->config.c_rgb == -1 || game->config.f_rgb == -1)
		exit_game(game, ERROR_MISSING_COLOR, EXIT_FAILURE);
}

int	has_adjacent_space(t_parse *parser, int x, int y)
{
	if (!parser->map[y - 1][x] || !parser->map[y + 1][x]
			|| !parser->map[y][x + 1] || !parser->map[y][x - 1])
		return (1);
	if (parser->map[y - 1][x] == ' '
			|| parser->map[y + 1][x] == ' '
			|| parser->map[y][x - 1] == ' '
			|| parser->map[y][x + 1] == ' ')
		return (1);
	return (0);
}
