/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 23:39:58 by kali              #+#    #+#             */
/*   Updated: 2025/07/27 23:39:59 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrstr(char *str, char *to_find)
{
	int		len;
	char	*ret;
	char	*tmp;

	ret = NULL;
	tmp = str;
	len = ft_strlen(to_find);
	while (tmp)
	{
		tmp = ft_strnstr(tmp, to_find, ft_strlen(tmp));
		if (tmp)
		{
			ret = tmp;
			tmp = tmp + len;
		}
	}
	return (ret);
}
