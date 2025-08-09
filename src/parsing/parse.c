/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 23:48:32 by kali              #+#    #+#             */
/*   Updated: 2025/08/09 19:19:10 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

// TODO: chech .cub extention
// TODO: open the file 
// TODO: use get_next_line to read it

static void	init_game_data(t_game_data *data)
{
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->map_path = NULL;
	data->join = NULL;
	data->map = NULL;
	data->fd = 0;
	data->no_path = NULL;
	data->so_path = NULL;
	data->we_path = NULL;
	data->ea_path = NULL;
	data->f_rgb = -1;
	data->c_rgb = -1;
}

static void	check_file_extention(char *filename)
{
	char	*ext;

	ext = ft_strrstr(filename, ".cub");
	if (!ext || ft_strlen(ext) != 4)
		clean_and_exit("Usage: ./cub3D path_to_map.cub\n");
}

static void	open_file(char *filename, t_game_data *data)
{
	check_file_extention(filename);
	data->fd = open(filename, O_RDONLY);
	if (data->fd == -1)
		clean_and_exit("Failed to open the file");
}

static void	read_file(t_game_data *data)
{
	char	*line;

	line = get_next_line(data->fd, 0);
	while (line)
	{
		load_line(line, data);
		free(line);
		line = get_next_line(data->fd, 0);
	}
	init_map_matrix(data);
}

/**
 * @brief Parses command line arguments and initializes game data.
 * @param ac Argument count.
 * @param av Argument vector.
 * @param data Pointer to the game data structure to be initialized.
 * @return true if parsing and initialization are successful, false otherwise.
 */
bool	parse_args(int ac, char **av, t_game_data *data)
{
	init_game_data(data);
	if (ac != 2)
	{
		printf("Error\nUsage: ./cub3D path_to_map.cub\n");
		clean_and_exit("Invalid number of arguments");
	}
	open_file(av[1], data);
	read_file(data);
	return (true);
}
