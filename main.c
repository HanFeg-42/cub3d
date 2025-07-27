/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 23:52:48 by kali              #+#    #+#             */
/*   Updated: 2025/07/27 23:59:48 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

void	free_game_data(t_game_data *data)
{
	if (data->no_path)
		free(data->no_path);
	if (data->so_path)
		free(data->so_path);
	if (data->we_path)
		free(data->we_path);
	if (data->ea_path)
		free(data->ea_path);
	if (data->map)
		ft_free_split(data->map);
	if (data->map_path)
		free(data->map_path);
	if (data->join)
		free(data->join);
}

// Function to print t_game_data contents
void	print_game_data(const t_game_data *data)
{
	int	i;

	printf("no_path:    %s\n", data->no_path);
	printf("so_path:    %s\n", data->so_path);
	printf("we_path:    %s\n", data->we_path);
	printf("ea_path:    %s\n", data->ea_path);
	printf("f_rgb:      %d\n", data->f_rgb);
	printf("c_rgb:      %d\n", data->c_rgb);
	if (data->map)
	{
		printf("map:\n");
		i = 0;
		while (data->map[i])
		{
			printf("  %s\n", data->map[i]);
			i++;
		}
	}
	else
		printf("map:        (null)\n");
}

int	main(int ac, char **av)
{
	t_game_data	data;

	if (!parse_args(ac, av, &data))
		return (1);
	print_game_data(&data);
	free_game_data(&data);
	return (0);
}
