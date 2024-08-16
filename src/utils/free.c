/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 16:21:10 by eahn              #+#    #+#             */
/*   Updated: 2024/08/16 16:22:00 by eahn             ###   ########.fr       */
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

/**
 * @brief Frees the entire environment list.
 * @param env_list The pointer to the first node of the environment list.
 */

void	free_env_list(t_list *env_list)
{
	t_list	*temp;

	while (env_list)
	{
		temp = env_list->next;
		free(env_list->content);
		free(env_list);
		env_list = temp;
	}
}
