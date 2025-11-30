/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 15:25:28 by hfegrach          #+#    #+#             */
/*   Updated: 2025/11/30 20:52:24 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "cub3d.h"

# define TRUE 0
# define FALSE 1

// Error messages for file handling
# define ERROR_INVALID_EXTENSION "Error\nInvalid file extension"
# define ERROR_FILE_OPEN_FAILED  "Error\nFailed to open file"
# define ERROR_EMPTY_FILE        "Error\nFile is empty"

// Error messages for program arguments
# define ERROR_INVALID_ARGS      "Error\nUsage: ./cub3D path_to_map.cub"

// Error messages for configuration
# define ERROR_INVALID_CONFIG    "Error\nInvalid configuration parameter"
# define ERROR_INVALID_COLOR     "Error\nInvalid color format"
# define ERROR_MISSING_TEXTURE   "Error\nMissing texture path"
# define ERROR_MISSING_COLOR     "Error\nMissing color definition"
# define ERROR_MISSING_XPM_EXT   "Error\nTexture must have '.xpm' extension"

// Error messages for map validation
# define ERROR_INVALID_ELEMENT	"Error\nInvalid map element: unknown character"
# define ERROR_EMPTY_LINE		"Error\nMap contains empty line"
# define ERROR_MULTIPLE_PLAYERS	"Error\nMultiple player spawn positions found"
# define ERROR_NO_PLAYER		"Error\nNo player spawn position found"
# define ERROR_INVALID_MAP		"Error\nMap is not properly enclosed by walls"
# define ERROR_INVALID_DOOR		"Error\nInvalid door position"

typedef struct s_parse
{
	int		fd;
	char	*join_config;
	char	*join_map;
	char	**config;
	char	**map;
	int		is_player;
}	t_parse;

void	is_all_config_loaded(t_game *game);
void	parse_color(t_game *game, char *color, char *full_line);
void	parse_texture(t_game *game, char *texture);
void	parse_map(t_game *game, t_parse *parser);
char	*gc_strtrim_all(char const *s1, char const *set);
int		has_adjacent_space(t_parse *parser, int x, int y);
int		is_file_ext_valid(char *filename, char *right_ext);
int		is_door_valid(t_parse *parser, int x, int y);

#endif