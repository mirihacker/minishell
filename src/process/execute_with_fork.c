/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_with_fork.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:34:17 by eahn              #+#    #+#             */
/*   Updated: 2024/08/12 19:52:24 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

/**
 * - If last_cmd exists, this cmd is part of a pipeline.
 * - rd_end of last_cmd is duplicated to stdin, fd closed to prevent leaks.
 * - If current_cmd has a wr_end, it will output to next cmd in pipeline.
 * - The wr_end is duplicated to stdout, fd closed to prevent leaks.
 */
static void	setup_pipes(t_cmd *last_cmd, t_cmd *current_cmd)
{
	if (last_cmd)
	{
		ft_close(last_cmd->fd_out);
		// wirte_end close (cause i've never written)
		ft_dup2(last_cmd->fd_in, STDIN_FILENO);
		// duplicate read_end to stdin
		ft_close(last_cmd->fd_in); // read_end close
	}
	if (current_cmd->fd_out != -1)
	{
		ft_close(current_cmd->fd_in); // read_end close
		ft_dup2(current_cmd->fd_out, STDOUT_FILENO);
		// duplicate write_end to stdout
		ft_close(current_cmd->fd_out); // write_end close
	}
}

/**
 * @brief Closes pipes associated with the previous command.
 */
static void	close_pipes(t_cmd *last_cmd)
{
	if (last_cmd)
	{
		ft_close(last_cmd->fd_in);
		ft_close(last_cmd->fd_out);
	}
}

/**
 * @brief Executes command by forking new process and setting up pipes
 * - If command is part of pipeline, a pipe is created.
 * - In the child process:
 *  - Pipes are set up to redirect input/output.
 *  - Command is executed with appropriate redirection.
 * - In the parent process:
 * 	- wr_end of current pipe is closed.
 *  - Pipes associated with last command are closed.
 */
void	execute_with_fork(t_node *node, t_cmd *last_cmd)
{
	t_cmd	*current_cmd;
	t_mini	*mini;

	mini = get_mini();
	current_cmd = get_new_cmd();
	ft_lstadd_back(&(mini->cmd_list), ft_lstnew(current_cmd));
	if (node->right) // create pipe
		ft_pipe(current_cmd);
	signal(SIGQUIT, &handle_ignored_signal);
	current_cmd->pid = fork();
	if (current_cmd->pid < 0)
		exit_error("fork()", strerror(errno), EXIT_FAILURE);
	if (current_cmd->pid == 0)
	// child process
	{
		setup_pipes(last_cmd, current_cmd);
		redirect_with_fork(node->left->left);
		execution(node->left->right);
	}
	if (node->right)
		ft_close(current_cmd->fd_out); // close write end
	close_pipes(last_cmd);
}
