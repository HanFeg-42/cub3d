/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 20:31:50 by hfegrach          #+#    #+#             */
/*   Updated: 2025/11/27 22:15:07 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	count_occ(char *str, char c)
{
	int	count;
	int	i;

	if (!str)
		return (0);
	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

static int	is_numeric(const char *a)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	if (!(a[i] >= '0' && a[i] <= '9'))
		return (false);
	while (a[i] >= '0' && a[i] <= '9')
	{
		res = res * 10 + a[i] - '0';
		if (res > 255)
			return (false);
		i++;
	}
	return ((a[i] == '\0'));
}

static int	parse_rgb(t_game *game, char *nbr)
{
	int	n;

	if (!is_numeric(nbr))
		exit_game(game, ERROR_INVALID_COLOR, EXIT_FAILURE);
	n = ft_atoi(nbr);
	return (n);
}

static int	get_parsed_rgb(t_game *game, char *color, char **rgb_arr)
{
	int		parsed_rgb[3];
	int		rgb;

	if (count_occ(color, ',') != 2)
		exit_game(game, ERROR_MULTI_COMMAS, EXIT_FAILURE);
	if (!rgb_arr || !rgb_arr[0] || !rgb_arr[1] || !rgb_arr[2]
			|| !rgb_arr[3] || rgb_arr[4])
		exit_game(game, ERROR_INVALID_COLOR, EXIT_FAILURE);
	parsed_rgb[0] = parse_rgb(game, rgb_arr[1]);
	parsed_rgb[1] = parse_rgb(game, rgb_arr[2]);
	parsed_rgb[2] = parse_rgb(game, rgb_arr[3]);
	rgb = (parsed_rgb[0] << 16) | (parsed_rgb[1] << 8) | parsed_rgb[2];
	return (rgb);
}

void	parse_color(t_game *game, char *color, char *full_line)
{
	char	**elemt;

	elemt = gc_split_set(full_line, " ,");
	if (!elemt)
		exit_game(game, ERROR_INVALID_COLOR, EXIT_FAILURE);
	if (!ft_strcmp(elemt[0], "F") && game->config.f_rgb == -1)
		game->config.f_rgb = get_parsed_rgb(game, color, elemt);
	else if (!ft_strcmp(elemt[0], "C") && game->config.c_rgb == -1)
		game->config.c_rgb = get_parsed_rgb(game, color, elemt);
	else
		exit_game(game, ERROR_INVALID_COLOR, EXIT_FAILURE);
}