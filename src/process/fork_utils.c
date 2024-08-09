/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:33:03 by eahn              #+#    #+#             */
/*   Updated: 2024/08/09 17:47:11 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

void	free_cmd_list(void)
{
	t_list	*current_cmd;
	t_mini	*mini;

	mini = get_mini();
	if (!mini->cmd_list)
		return ;
	while (mini->cmd_list)
	{
		current_cmd = mini->cmd_list;
		mini->cmd_list = mini->cmd_list->next;
		free((void **)&(current_cmd->content));
		free((void **)&current_cmd);
	}
}

t_cmd	*get_last_cmd(void)
{
	t_list	*last_list;
	t_mini	*mini;

	mini = get_mini();
	last_list = ft_lstlast(mini->cmd_list);
	if (last_list)
		return ((t_cmd *)(last_list->content));
	else
		return (NULL);
}

// initialize a new cmd struct
t_cmd	*get_new_cmd(void)
{
	t_cmd *new_cmd;

	new_cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	new_cmd->fd_in = -1;
	new_cmd->fd_out = -1;
	return (new_cmd);
}

void free_ast (t_node *node)
{
	if (!node)
		return ;
	if (node->type == RDR_DI)
		unlink(node->right->value);
	free_ast(node->left);
	free_ast(node->right);
	if (node->value && node->type != CMD)
	{
		free(node->value);
		node->value = NULL;
	}
	free(node);
	node = NULL;
}

