/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:01:27 by kali              #+#    #+#             */
/*   Updated: 2025/08/04 22:19:59 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

t_gc **get_gc(void)
{
    static t_gc *g_gc = NULL;

    return (&g_gc);
}

static void    addnode(void *addr)
{
    t_gc *new_node;
    t_gc *gc;

    new_node = malloc(sizeof(t_gc));
    if (!new_node)
        return ;
    new_node->addr = addr;
    new_node->next = NULL;

    gc = *get_gc();
    if (!gc)
    {
        *get_gc() = new_node;
        return ;
    }
    while (gc->next)
        gc = gc->next;
    gc->next = new_node;
}


void    *malloc(size_t size)
{
    void    *ptr;

    ptr = malloc(size);

    if (!ptr)
        return (NULL);
    addnode(ptr);
    return (ptr);
}

// void   gc_free(void *ptr)
// {
//     t_gc *gc;
//     t_gc *prev;

//     if (!ptr)
//         return ;

//     gc = get_gc();
//     prev = NULL;

//     while (gc)
//     {
//         if (gc->addr == ptr)
//         {
//             if (prev)
//                 prev->next = gc->next;
//             else
//                 get_gc() = gc->next;
//             free(gc);
//             free(ptr);
//             return ;
//         }
//         prev = gc;
//         gc = gc->next;
//     }
// }

void    gc_clear(void)
{
    t_gc *gc;
    t_gc *next;

    gc = *get_gc();
    while (gc)
    {
        next = gc->next;
        if (gc->addr)
            free(gc->addr);
        free(gc);
        gc = next;
    }
    *get_gc() = NULL;
}
