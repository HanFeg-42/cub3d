#include "../../includes/cub3D.h"

void	config_line_loader(char *line, t_game_data *data, int *map_flag)
{
	// TODO : detect each config line, parse it, then load it to the game_data struct
}

void	map_line_loader(char *line, t_game_data *data)
{
	// TODO : load each line to the map array for the moment
	// find a way to handle newlines in between and make sure it is encountered by walls
	// no 0 are facing the outside
}

void	load_line(char *line, t_game_data *data)
{
	static	int	map_start_reached;

	if (map_start_reached == 0)
	{
		config_line_loader(line, data, &map_start_reached);
		return ;
	}
	map_line_loader(line, data);
}
