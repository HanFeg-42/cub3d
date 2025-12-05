/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:18:59 by hfegrach          #+#    #+#             */
/*   Updated: 2025/11/29 15:24:34 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "cub3d.h"

typedef struct s_gc
{
	void		*addr;
	struct s_gc	*next;
	struct s_gc	*prev;
}	t_gc;

t_gc	**get_gc_head(void);
void	*gc_alloc(size_t size);
void	free_one(void *addr);
void	free_all(void);
char	*gc_strjoin(char const *s1, char const *s2);
char	*gc_str_join(char *s1, char *s2);
char	*gc_strdup(const char *str);
char	**gc_split(char const *s, char c);
char	*gc_strtrim(char const *s1, char const *set);
char	*gc_substr(char const *s, unsigned int start, size_t len);
char	*gc_itoa(int nbr);
char	**gc_split_set(char const *s, char const *set);

#endif