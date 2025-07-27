#include "../../includes/cub3D.h"

int	parse_color(char *nbr)
{
	int n;
	// TODO nbr should be 0 <= nbr <= 255
	// should not contain any other character but its body
	// should be converted to int - use atoi()
	return (n);
}

int	get_rgb_color(char *color)
{
	char	**split_rgb;
	int	parsed_rgb[3];
	int	rgb;

	split_rgb = ft_split(color, ','); // to be freed rg
	if (!(split_rgb[0] && split_rgb[1] && split_rgb[2] && split_rgb[3] == NULL))
		clean_and_exit("mochkiil");
	parsed_rgb[0] = parse_color(split_rgb[0]);
	parsed_rgb[1] = parse_color(split_rgb[1]);
	parsed_rgb[2] = parse_color(split_rgb[2]);
	rgb = (parsed_rgb[0] << 16) | (parsed_rgb[1] << 8) | parsed_rgb[2];
	return (rgb);
}

void	detect_identifier(char *line, t_game_data)
{
	char **info;

	info = ft_split(line, ' '); // TODO free this info array rn
	if (info[2][0] == '\n')
	{
		if (ft_strcmp(info[0], "NO") == 0)
			data->no_path = ft_strdup(info[1]); // TODO should be freed later !!
		else if (ft_strcmp(info[0], "SO") == 0)
			data->so_path = ft_strdup(info[1]); // TODO should be freed later !!
		else if (ft_strcmp(info[0], "WE") == 0)
			data->we_path = ft_strdup(info[1]); // TODO should be freed later !!
		else if (ft_strcmp(info[0], "EA") == 0)
			data->ea_path = ft_strdup(info[1]); // TODO should be freed later !!
		else if (ft_strcmp(info[0], "F") == 0)
			data->f_rgb = get_rgb_color(info[1]); // TODO should be freed later !!
		else if (ft_strcmp(info[0], "C") == 0)
			data->c_rgb = get_rgb_color(info[1]); // TODO should be freed later !!
		else
			clean_and_exit("Unvalid map format!");
	}
	else
		clean_and_exit("Unvalid map format!");
}

void	config_line_loader(char *line, t_game_data *data, int *map_flag)
{
	// TODO : detect each config line, parse it, then load it to the game_data struct
	
	detect_identifier(line, data);
	if (conf_params_loaded(data))
			*map_flag = 1;
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
