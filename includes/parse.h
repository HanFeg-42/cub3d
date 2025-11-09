#ifndef PARSE_H
# define PARSE_H

# include "cub3d.h"

# define TRUE 0
# define FALSE 1

# define UNVALID_EXTENTION "unvlalid extention"
# define OPEN_FILE "failed to open the file"
# define UNVALID_ARG "Error\nUsage: ./cub3D path_to_map.cub"
# define UNVALID_CONFIG "unvalid config param"
# define UNVALID_COLOR "unvalid color!"
# define MISSING_TEXTURE "missing texture!"
# define MISSING_COLOR "missing color!"
# define XPM_EXT "missed '.xpm'  extension"

typedef struct s_parse
{
	int fd;
	char *join_config;
	char *join_map;
	char **config;
	char **map;
}	t_parse;

int is_file_ext_valid(char *filename, char *right_ext);
void    is_all_config_loaded(t_game *game);
void    parse_color(t_game *game, char *color_line);
void    parse_texture(t_game *game, char *texture);
void    parse_map(t_game *game, t_parse *parser);
char	*gc_strtrim_all(char const *s1, char const *set);

#endif