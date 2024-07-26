/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:40:00 by eahn              #+#    #+#             */
/*   Updated: 2024/07/26 17:30:18 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void execute_without_fork(t_node *cmd_node, t_cmd_type cmd_type)
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

void ft_dup2(int old_fd, int new_fd)
{
	int ret;
	ret = dup2(old_fd, new_fd);
	if (ret < 0)
		exit_with_err("dup2()", strerror(errno), EXIT_FAILURE); // TBD
}

void ft_close(int fd)
{
	int ret;
	ret = close(fd);
	if (ret < 0)
		exit_with_err("close()", strerror(errno), EXIT_FAILURE); // TBD
}

void connect_pipes(t_cmd *last_cmd, t_cmd *current_cmd)
{
	if (last_cmd)
	{
		ft_close(last_cmd->fd_out); //wirte_end close
		ft_dup2(last_cmd->fd_in, STDIN_FILENO); // duplicate read_end to stdin
		ft_close(last_cmd->fd_in); // read_end close
	}
	if (current_cmd->fd_out != -1)
	{
		ft_close(current_cmd->fd_in); // read_end close
		ft_dup2(current_cmd->fd_out, STDOUT_FILENO); // duplicate write_end to stdout
		ft_close(current_cmd->fd_out); // write_end close
	}
}


void	ft_pipe(t_cmd *cmd)
{
	int	pipe_fds[2];
	int	ret;

	ret = pipe(pipe_fds);
	if (ret < 0)
		exit_with_err("pipe()", strerror(errno), EXIT_FAILURE); // TBD
	cmd->fd_in = pipe_fds[0];                                   // read_end
	cmd->fd_out = pipe_fds[1];                                  // write_end
}

void close_pipes(t_cmd *last_cmd)
{
	if (last_cmd)
	{
		ft_close(last_cmd->fd_in);
		ft_close(last_cmd->fd_out);
	}
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

void execute_with_fork(t_node *node, t_cmd *last_cmd)
{
	t_cmd	*current_cmd;

	current_cmd = get_new_cmd();
	ft_lstadd_back(&(mini()->cmd_list), ft_lstnew(current_cmd));
	if (node->right)
		ft_pipe(current_cmd);
	signal(SIGQUIT, ignore_signal); // ignore SIGQUIT
	current_cmd->pid = fork();
	if (current_cmd->pid < 0)
		exit_with_error("fork()", strerror(errno), EXIT_FAILURE); // TBD
	if (current_cmd->pid == 0) // child process
	{
		connect_pipes(last_cmd, current_cmd); // TBD
		handle_redirections(node->left->left); // TBD
		execute_cmd(node->left->right); // TBD
	}
	if (node->right)
		ft_close(current_cmd->fd_out); // close write end
	close_pipes(last_cmd)//TBD

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
	if (result != true)
		execute_without_fork(tree->left, (t_cmd_type)result); // fork not needed
	else
		execute_with_fork(tree, last_cmd); // fork needed
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
void	read_tree(t_node *tree) /
{
	if (tree)
	{
		process_ast_node(tree);
		read_tree(tree->right);
	}
	else
		finalize_ast_processing();
}
