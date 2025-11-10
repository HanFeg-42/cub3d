/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 20:31:50 by hfegrach          #+#    #+#             */
/*   Updated: 2025/11/10 16:59:16 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

//TODO : IDA DOUBLT TEXTURES KAYN MOCHKIL +  ee

void    load_texture(t_game *game,char *t_id, char *texture)
{
    printf("%s\n", texture);
    if (!ft_strcmp(t_id, "NO") && !game->config.no)
        game->config.no = ft_strdup(texture);
    else if (!ft_strcmp(t_id, "SO") && !game->config.so)
        game->config.so = ft_strdup(texture);
    else if (!ft_strcmp(t_id, "EA") && !game->config.ea)
        game->config.ea = ft_strdup(texture);
    else if (!ft_strcmp(t_id, "WE") && !game->config.we)
        game->config.we = ft_strdup(texture);
    else
        exit_game(game, UNVALID_CONFIG, EXIT_FAILURE);
    // what if NN??
}

void    parse_texture(t_game *game, char *texture)
{
    char **elemt;

    texture = gc_strtrim(texture, " ");
    elemt = gc_split(texture, ' ');
    if (elemt[1] == NULL || elemt[2] != NULL)
        exit_game(game, UNVALID_CONFIG, EXIT_FAILURE);
    load_texture(game, elemt[0], elemt[1]);
    return ;
}
