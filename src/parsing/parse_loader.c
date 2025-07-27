/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_loader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 23:43:30 by kali              #+#    #+#             */
/*   Updated: 2025/07/27 23:48:19 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	parse_color(char *nbr)
{
	int	n;

	if (!is_numeric(nbr))
		clean_and_exit("unvalid map format");
	n = ft_atoi(nbr);
	return (n);
}

static int	get_rgb_color(char *color)
{
	char	**split_rgb;
	int		parsed_rgb[3];
	int		rgb;

	split_rgb = ft_split(color, ',');
	if (!(split_rgb[0] && split_rgb[1] && split_rgb[2] && split_rgb[3] == NULL))
		clean_and_exit("mochkiil");
	parsed_rgb[0] = parse_color(split_rgb[0]);
	parsed_rgb[1] = parse_color(split_rgb[1]);
	parsed_rgb[2] = parse_color(split_rgb[2]);
	ft_free_split(split_rgb);
	rgb = (parsed_rgb[0] << 16) | (parsed_rgb[1] << 8) | parsed_rgb[2];
	return (rgb);
}

static void	detect_identifier(char *line, t_game_data *data)
{
	char	**info;

	info = ft_split(line, ' ');
	if (info[2][0] == '\n')
	{
		if (ft_strcmp(info[0], "NO") == 0)
			data->no_path = ft_strdup(info[1]);
		else if (ft_strcmp(info[0], "SO") == 0)
			data->so_path = ft_strdup(info[1]);
		else if (ft_strcmp(info[0], "WE") == 0)
			data->we_path = ft_strdup(info[1]);
		else if (ft_strcmp(info[0], "EA") == 0)
			data->ea_path = ft_strdup(info[1]);
		else if (ft_strcmp(info[0], "F") == 0)
			data->f_rgb = get_rgb_color(info[1]);
		else if (ft_strcmp(info[0], "C") == 0)
			data->c_rgb = get_rgb_color(info[1]);
		else
			clean_and_exit("Unvalid map format!");
	}
	else
		clean_and_exit("Unvalid map format!");
	ft_free_split(info);
}

static void	config_line_loader(char *line, t_game_data *data, int *map_flag)
{
	detect_identifier(line, data);
	if (conf_params_loaded(data))
		*map_flag = 1;
}

void	load_line(char *line, t_game_data *data)
{
	static int	map_start_reached;

	if (map_start_reached == 0)
	{
		config_line_loader(line, data, &map_start_reached);
		return ;
	}
	map_line_loader(line, data);
}
