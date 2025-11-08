#ifndef PARSE_H
# define PARSE_H

# include "cub3d.h"

# define TRUE 0
# define FALSE 1

# define UNVALID_EXTENTION "unvlalid extention"
# define OPEN_FILE "failed to open the file"
# define UNVALID_ARG "Error\nUsage: ./cub3D path_to_map.cub"
# define UNVALID_CONFIG "unvalid config param"


typedef struct s_parse
{
	int fd;
	char *join_config;
	char *join_map;
	char **config;
	char **map;
}	t_parse;



#endif