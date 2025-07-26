#include "../../includes/cub3D.h"

// TODO: chech .cub extention
// TODO: open the file 
// TODO: use get_next_line to read it

void	init_game_data(t_game_data *data)
{
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->map_path = NULL;
	data->map = NULL;
	data->fd = 0;
}

void	check_file_extention(char *filename)
{
	char	*ext;

	ext = ft_strrstr(filename, ".cub");
	if (!ext || ft_strlen(ext) != 4)
		clean_and_exit("Usage: ./cub3D path_to_map.cub\n");
}

void	open_file(char *filename, t_game_data *data)
{
	check_file_extention(filename);
	data->fd = open(filename, O_RDONLY);
	if (data->fd == -1)
		clean_and_exit("Failed to open the file");
}

void	read_file(t_game_data *data)
{
	char	*line;

	line = get_next_line(data->fd);
	while (line)
	{
		load_line(line, data);
		free(line);
		line = get_next_line(data->fd);
	}
}

/**
 * @brief Parses command line arguments and initializes game data.
 * @param ac Argument count.
 * @param av Argument vector.
 * @param data Pointer to the game data structure to be initialized.
 * @return true if parsing and initialization are successful, false otherwise.
 * @details
 * This function checks if the correct number of arguments is provided,
 * initializes the MinilibX library, creates a new window, and sets the map path.
 * It also initializes the map to NULL, which will be set when loading the map.
 * If any step fails, it prints an error message and returns false.
 * If successful, it returns true.
 */
bool	parse_args(int ac, char **av, t_game_data *data)
{
	t_parse_data	parse_data;

	init_game_data(data);
	if (ac != 2)
	{
		printf("Error\nUsage: ./cub3D path_to_map.cub\n");
		return (1);
	}
	open_file(av[1], data);
	read_file(data);	
	return true;
}
