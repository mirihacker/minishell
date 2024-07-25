/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:40:00 by eahn              #+#    #+#             */
/*   Updated: 2024/07/25 22:24:02 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

execute_without_fork(t_node *cmd_node, t_cmd_type cmd_type)
{
	int	stdin_backup;
	int	stdout_backup;

	backup_stdin_stdout(&stdin_backup, &stdout_backup);
	if (redirect_files_no_fork(cmd_node->left) == -1)
	{
		restore_stdin_stdout(stdin_backup, stdout_backup);
		return ;
	}
	// TBD
}

// initialize a new cmd struct
t_cmd	get_new_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	new_cmd->fd_in = -1;
	new_cmd->fd_out = -1;
	return (new_cmd);
}

execute_with_fork(t_node *node, t_cmd *last_cmd)
{
	t_cmd	*current_cmd;

	current_cmd = get_new_cmd();
	ft_lstadd_back(&(mini()->cmd_list), ft_lstnew(current_cmd));
	if (node->right)
		ft_pipe(current_cmd->fd_in, current_cmd->fd_out);
	// TBD
}

t_cmd	get_last_cmd(void)
{
	t_list	*last_list;

	last_list = ft_lstlast(mini()->cmd_list);
	if (last_list)
		return ((t_cmd *)(last_list->content));
	else
		return (NULL);
}

int	is_fork_needed(t_cmd *last_cmd, t_node *tree)
{
	t_cmd_type	cmd_type;

	cmd_type = get_cmd_type(tree->left->value);
	if (!last_cmd && cmd_type != GENERAL && !tree->right)
		return (cmd_type); // fork not needed
	return (true);         // fork needed
}

void	process_ast_node(t_node *tree)
{
	t_cmd	*last_cmd;
	int		result;

	last_cmd = get_last_cmd();
	result = is_fork_needed(last_cmd, tree);
	if (result == true)
		execute_with_fork(tree, last_cmd);
	else
		execute_without_fork(tree->left, (t_cmd_type)result);
}

void	clear_cmd_list(void)
{
	t_list	*current_cmd;

	if (!mini()->cmd_list)
		return ;
	while (mini()->cmd_list)
	{
		current_cmd = mini()->cmd_list;
		mini()->cmd_list = mini()->cmd_list->next;
		free((void **)&(current_cmd->content));
		free((void **)&current_cmd);
	}
}

void	finalize_ast_processing(void)
{
	restore_echoctl();
	signal(SIGINT, ignore_signal);
	wait_for_children();
	free_cmd_list();
}

// this one should be called in parse, if (root)
void	read_tree(t_node *tree)
{
	if (tree)
	{
		process_ast_node(tree);
		read_tree(tree->right);
	}
	else
		finalize_ast_processing();
}
