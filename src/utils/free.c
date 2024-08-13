/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 16:21:10 by eahn              #+#    #+#             */
/*   Updated: 2024/08/13 19:22:58 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_ptr(void **ptr)
{
	if (ptr != NULL && *ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

// void	free_list(t_list **head)
// {
// 	t_list *tmp;
// 	t_list *current;

// 	if (!head || !*head)
// 		return ;
// 	current = *head;
// 	while (current)
// 	{
// 		tmp = current->next;
// 		free(current->content);
// 		free(current);
// 		current = tmp;
// 	}
// 	*head = NULL;
// }