/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:40:00 by eahn              #+#    #+#             */
/*   Updated: 2024/08/16 17:21:57 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

/**
 * - Fork not needed: built-in command with no prev, following cmd
 *   e.g. echo, pwd, cd, export, unset, env, exit
 * - Fork needed: external commands (ls, grep) or pipes
 *   e.g. ls | grep, echo hello | wc -c
 */
static int	is_fork_needed(t_cmd *last_cmd, t_node *tree)
{
	t_cmd_type	cmd_type;

	cmd_type = cmd_type_tester(tree->left->value);
	if (!last_cmd && cmd_type != EXTERNAL && !tree->right)
		return (cmd_type);
	return (-1);
}

/**
 * @brief Finalizes AST processing
 * clean up and restore terminal settings
 */
static void	finalize_ast_processing(void)
{
	enable_ctrl_echo();
	signal(SIGINT, handle_ignored_signal);
	wait_for_children();
	reset_cmd_list();
}

/**
 * @brief Traverses the AST and processes each node
 */
void	traverse_ast(t_node *tree)
{
	t_cmd	*last_cmd;
	int		result;

	if (tree)
	{
		last_cmd = get_last_cmd();
		result = is_fork_needed(last_cmd, tree);
		if (result != -1)
		{
			execute_without_fork(tree->left, (t_cmd_type)result);
			return ;
		}
		execute_with_fork(tree, last_cmd);
		traverse_ast(tree->right);
	}
	else
	{
		finalize_ast_processing();
		return ;
	}
}
