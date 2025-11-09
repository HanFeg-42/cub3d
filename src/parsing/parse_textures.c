/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 20:31:50 by hfegrach          #+#    #+#             */
/*   Updated: 2025/11/09 13:27:05 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int is_xpm_valid(char *path)
{
    return (!is_file_ext_valid(path, ".xpm"));
}

void    load_texture(t_game *game,char *t_id, char *texture)
{
    printf("%s\n", texture);
    if (!ft_strcmp(t_id, "NO"))
        game->config.no_path = ft_strdup(texture);
    if (!ft_strcmp(t_id, "SO"))
        game->config.so_path = ft_strdup(texture);
    if (!ft_strcmp(t_id, "EA"))
        game->config.ea_path = ft_strdup(texture);
    if (!ft_strcmp(t_id, "WE"))
        game->config.we_path = ft_strdup(texture);
}

void    parse_texture(t_game *game, char *texture)
{
    char **elemt;

    texture = gc_strtrim(texture, " ");
    elemt = gc_split(texture, ' ');
    if (elemt[1] == NULL || elemt[2] != NULL)
        exit_game(game, UNVALID_CONFIG, EXIT_FAILURE);
    if (is_xpm_valid(elemt[1]))
        load_texture(game, elemt[0], elemt[1]);
        // exit_game(game, XPM_EXT, EXIT_FAILURE);
    return ;
}
