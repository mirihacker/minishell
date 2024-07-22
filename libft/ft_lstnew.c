/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:17:58 by eahn              #+#    #+#             */
/*   Updated: 2024/07/22 16:18:27 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include     "libft.h"

t_list *ft_lstnew (void *content)
{
    t_list *new;

    new = (t_list *)malloc(sizeof(t_list));
    if (!new)
        return (NULL);
    new->content = content;
    new->next = NULL;
    return (new);
}