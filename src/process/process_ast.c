/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:40:00 by eahn              #+#    #+#             */
/*   Updated: 2024/08/13 19:36:42 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

/**
 * - Fork not needed: built-in command with no prev, following cmd
 * - Fork needed: general commands (ls, grep) or pipes
 */
static bool	is_fork_needed(t_cmd *last_cmd, t_node *tree)
{
	t_cmd_type	cmd_type;

	cmd_type = cmd_type_tester(tree->left->value);
	if (!last_cmd && cmd_type != GENERAL && !tree->right)
		return (false);
	return (true);
}

/**
 * @brief Determines if a fork is needed to execute the command
 */
static void	process_ast_node(t_node *tree)
{
	t_cmd	*last_cmd;
	bool	fork_needed;

	last_cmd = get_last_cmd();
	fork_needed = is_fork_needed(last_cmd, tree);
	if (fork_needed)
		execute_with_fork(tree, last_cmd);
	else
		execute_without_fork(tree->left, cmd_type_tester(tree->left->value));
}

/**
 * @brief Finalizes AST processing, clean up and restore terminal settings
 */
static void	finalize_ast_processing(void)
{
	enable_ctrl_echo();
	signal(SIGINT, &handle_ignored_signal);
	wait_for_children();
	// free_cmd_list();
}

/**
 * @brief Traverses the AST and processes each node
 */
void	traverse_ast(t_node *tree)
{
	if (tree)
	{
		process_ast_node(tree);
		traverse_ast(tree->right);

	}
	else
	{
		finalize_ast_processing();
		return ;
	}
}
