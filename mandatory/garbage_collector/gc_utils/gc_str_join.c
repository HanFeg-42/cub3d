/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_str_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:38:57 by hfegrach          #+#    #+#             */
/*   Updated: 2025/11/08 13:47:54 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libft/libft.h"
#include "gc.h"

char	*gc_str_join(char *s1, char *s2)
{
	char	*res;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	res = gc_alloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	free_one(s1);
	return (res);
}
