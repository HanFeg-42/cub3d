/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 11:30:28 by hfegrach          #+#    #+#             */
/*   Updated: 2025/11/09 13:03:52 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void    is_all_config_loaded(t_game *game)
{
    if (
        !game->config.ea_path
        || !game->config.no_path
        || !game->config.so_path
        || !game->config.we_path
    )
        exit_game(game, MISSING_TEXTURE, EXIT_FAILURE);
    if (game->config.c_rgb == -1 || game->config.f_rgb == -1)
        exit_game(game, MISSING_COLOR, EXIT_FAILURE);
}

char	*gc_strtrim_all(char const *s1, char const *set)
{
	char	*res;
	int		i;
	int		j;

	if (!s1 || !set)
		return (NULL);
	res = gc_alloc(ft_strlen(s1) + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		if (!ft_strchr(set, s1[i]))
			res[j++] = s1[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}
