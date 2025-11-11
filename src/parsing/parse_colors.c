/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 20:31:50 by hfegrach          #+#    #+#             */
/*   Updated: 2025/11/10 22:16:49 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int count_occ(char *str, char c)
{
	int count;
	int i;

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

int	is_numeric(const char *a)
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
    {
        printf("%s\n", nbr);
        exit_game(game, "1", EXIT_FAILURE);
    }
	n = ft_atoi(nbr);
	return (n);
}

int get_parsed_rgb(t_game *game, char *color)
{
    char    **rgb_arr;
    int     parsed_rgb[3];
    int     rgb;

    if (count_occ(color, ',') != 2)
        exit_game(game, "2", EXIT_FAILURE);
    rgb_arr = gc_split(color, ',');
    if (!rgb_arr || !rgb_arr[0] || !rgb_arr[1] || !rgb_arr[2] || rgb_arr[3])
        exit_game(game, "3", EXIT_FAILURE);
    parsed_rgb[0] = parse_rgb(game, rgb_arr[0]);
	parsed_rgb[1] = parse_rgb(game, rgb_arr[1]);
	parsed_rgb[2] = parse_rgb(game, rgb_arr[2]);
	rgb = (parsed_rgb[0] << 16) | (parsed_rgb[1] << 8) | parsed_rgb[2];
	return (rgb);
}

void    parse_color(t_game *game, char *color)
{
    if (color[0] == 'C' && game->config.c_rgb == -1)
        game->config.c_rgb = get_parsed_rgb(game, color + 1);
    else if (color[0] == 'F' && game->config.f_rgb == -1)
        game->config.f_rgb = get_parsed_rgb(game, color + 1);
	else
		exit_game(game, UNVALID_COLOR, EXIT_FAILURE);
}
