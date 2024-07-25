/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:40:00 by eahn              #+#    #+#             */
/*   Updated: 2024/07/25 13:51:26 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>
#include <unistd.h>

t_cmd	get_last_cmd(void)
{
	t_list	*last_list;

	last_list = ft_lstlast(mini()->cmd_list);
	if (last_list)
		return (t_cmd *)(last_list->content);
	else
		return (NULL);
}

bool	is_fork_needed(t_cmd *last_cmd, t_node *tree)
{
	t_cmd_type	cmd_type;

	cmd_type = get_cmd_type(tree->left->value);
	if (!last_cmd && cmd_type != GENERAL && !tree->right)
		return (cmd_type);
	return (false);
}

void	execute_cmd(t_node *tree)
{
	t_cmd	*last_cmd;
	int		ret;

	if (tree)
	{
		last_cmd = get_last_cmd();
		ret = if_fork_needed(last_cmd, tree);
		if (!ret)
		{
			execute_without_fork(tree->left, (t_cmd_type)ret);
			return ;
		}
		execute_with_fork(tree, last_cmd);
	}
}
