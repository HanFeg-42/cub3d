/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:18:52 by hfegrach          #+#    #+#             */
/*   Updated: 2025/11/07 13:53:03 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

void	free_all(void)
{
	t_gc	**head;
	t_gc	*curr;
	t_gc	*next;

	head = get_gc_head();
	if (!head || !(*head))
		return ;
	curr = *head;
	while (curr)
	{
		next = curr->next;
		if (curr->addr)
			free(curr->addr);
		free(curr);
		curr = next;
	}
	*head = NULL;
}

void	clean_and_exit(int status)
{
	free_all();
	exit(status);
}
