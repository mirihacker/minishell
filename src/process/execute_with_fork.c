/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_with_fork.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:34:17 by eahn              #+#    #+#             */
/*   Updated: 2024/08/09 18:02:29 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

void	ft_dup2(int old_fd, int new_fd)
{
	int	ret;

	ret = dup2(old_fd, new_fd);
	if (ret < 0)
		exit_error("dup2()", strerror(errno), EXIT_FAILURE); // TBD
}

void	ft_close(int fd)
{
	int	ret;

	ret = close(fd);
	if (ret < 0)
		exit_error("close()", strerror(errno), EXIT_FAILURE); // TBD
}

void	setup_pipes(t_cmd *last_cmd, t_cmd *current_cmd)
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

void	ft_pipe(t_cmd *cmd)
{
	int	ret;

	int pipe_fds[2]; // 0: read, 1: write
	ret = pipe(pipe_fds);
	if (ret < 0)
		exit_error("pipe()", strerror(errno), EXIT_FAILURE); 
	cmd->fd_in = pipe_fds[0];                                   // read_end
	cmd->fd_out = pipe_fds[1];                                  // write_end
}

void	close_pipes(t_cmd *last_cmd)
{
	if (last_cmd)
	{
		ft_close(last_cmd->fd_in);
		ft_close(last_cmd->fd_out);
	}
}

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

