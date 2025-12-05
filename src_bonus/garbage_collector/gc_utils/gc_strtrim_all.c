/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strtrim_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:35:26 by hfegrach          #+#    #+#             */
/*   Updated: 2025/11/12 16:35:42 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

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
