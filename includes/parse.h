#ifndef PARSE_H
# define PARSE_H

# include "cub3d.h"

# define TRUE 0
# define FALSE 1

# define UNVALID_EXTENTION "Error\nunvlalid extention"
# define OPEN_FILE "Error\nfailed to open the file"
# define UNVALID_ARG "Error\nUsage: ./cub3D path_to_map.cub"
# define UNVALID_CONFIG "Error\nunvalid config param"
# define UNVALID_COLOR "Error\nunvalid color!"
# define MISSING_TEXTURE "Error\nmissing texture!"
# define MISSING_COLOR "Error\nmissing color!"
# define XPM_EXT "Error\nmissed '.xpm'  extension"
# define UNVALID_ELEMENT "Error\nunvalid map element unknown char"
# define EMPTY_LINE "Error\nthere is an empty or only spaces in the map"
# define DOUBLED_PLAYER "Error\nmdouble l player"
# define NO_PLAYER "Error\nwa lplayer makaynch"
# define UNVALID_MAP "Error\nlmap mahyach"

typedef struct s_parse
{
	int fd;
	char *join_config;
	char *join_map;
	char **config;
	char **map;
	int		is_player;
}	t_parse;

int is_file_ext_valid(char *filename, char *right_ext);
void    is_all_config_loaded(t_game *game);
void    parse_color(t_game *game, char *color_line);
void    parse_texture(t_game *game, char *texture);
void    parse_map(t_game *game, t_parse *parser);
char	*gc_strtrim_all(char const *s1, char const *set);

#endif