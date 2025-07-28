/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 23:46:19 by kali              #+#    #+#             */
/*   Updated: 2025/07/27 23:51:52 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	clean_and_exit(char *message)
{
	ft_putstr_fd(message, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

int	is_numeric(const char *a)
{
	int		i;
	int		sign;
	long	res;

	i = 0;
	sign = 1;
	res = 0;
	if (a[i] == '-' || a[i] == '+')
	{
		if (a[i] == '-')
			sign *= -1;
		i++;
	}
	if (!(a[i] >= '0' && a[i] <= '9'))
		return (false);
	while (a[i] >= '0' && a[i] <= '9')
	{
		res = res * 10 + a[i] - '0';
		if (res > 255 || res * sign < 0)
			return (false);
		i++;
	}
	return ((a[i] == '\0'));
}

bool	conf_params_loaded(t_game_data *data)
{
	if (data->no_path && data->so_path && data->we_path && data->ea_path
		&& data->f_rgb >= 0 && data->c_rgb >= 0)
		return (true);
	return (false);
}

void	ft_free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	free(arr);
}
