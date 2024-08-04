/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:40:00 by eahn              #+#    #+#             */
/*   Updated: 2024/08/05 01:38:24 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// redirect_files.c or redirect_with_fork from execute_with_fork.c
int	ft_open(char *filename, int open_flag, int mode)
{
	int	fd;

	fd = open(filename, open_flag, mode);
	if (fd < 0)
		exit_with_err(filename, strerror(errno), EXIT_FAILURE);
	return (fd);
}

void	forked_set_redirect(const char *filename, int open_flag, int target_fd)
{
	int	file_fd;

	file_fd = ft_open(filename, open_flag, 0644);
	ft_dup2(file_fd, target_fd);
	ft_close(file_fd);
}

void	forked_redirect_input(const char *filename);
{
	forked_set_redirect(filename, O_RDONLY, STDIN_FILENO);
}

void	forked_redirect_output(t_token_type rdr_type, const char *filename)
{
	int	open_flag;

	if (rdr_type == RDR_O)
		open_flag = O_WRONLY | O_CREAT | O_TRUNC;
	else
		open_flag = O_WRONLY | O_CREAT | O_APPEND;
	forked_set_redirect(filename, open_flag, STDOUT_FILENO);
}

void	forked_redirect_node(t_node *rdr_node)
{
	t_token_type	rdr_type;
	char			*filename;

	rdr_type = rdr_node->left->type;
	filename = rdr_node->right->value;
	if (rdr_type == RDR_O || rdr_type == RDR_DO) // if it's > or >>
		forked_redirect_output(rdr_type, filename);
	else // if it's <
		forked_redirect_input(filename);
}

void	redirect_with_fork(t_node *rdr_node)
{
	if (!rdr_node)
		return ;
	if (rdr_node->type == RDR) // To check with Siria,
	{
		forked_redirect_node(rdr_node);
	}
	if (rdr_node->left)
		redirect_with_fork(rdr_node->left);
	if (rdr_node->right)
		redirect_with_fork(rdr_node->right);
}
// redirect_files_no_fork.c
int	verify_system_call(int res, char *str)
{
	if (res < 0)
	{
		print_err(str, NULL, strerror(errno));
		mini()->exit_code = EXIT_FAILURE;
		return (-1);
	}
	return (0);
}
// 6: owner read & write (4 + 2)
// 4: group, others read-only
int	set_redirect(const char *filename, int open_flag, int target_fd)
{
	int	file_fd;
	int	res;

	file_fd = open(filename, open_flag, 0644); // 0644: rw-r--r--
	if (verify_system_call(file_fd, filename) == -1)
		return (-1);
	res = dup2(file_fd, target_fd);
	if (verify_system_call(res, "dup2()") == -1)
		return (-1);
	res = close(file_fd);
	if (verify_system_call(res, "close()") == -1)
		return (-1);
	return (0);
}

int	redirect_input(char *filename) // <
{
	return (open_redirect(filename, O_RDONLY, STDIN_FILENO));
}

int	redirect_output(t_token_type rdr_type, char *filename)
{
	int	open_flag;

	if (rdr_type == RDR_O) // if it's >, overwrite with TRUNC
		open_flag = O_WRONLY | O_CREAT | O_TRUNC;
	else // if it's >>, append
		open_flag = O_WRONLY | O_CREAT | O_APPEND;
	return (open_redirect(filename, open_flag, STDOUT_FILENO));
}

int	redirect_node(t_node *rdr_node)
{
	t_token_type	rdr_type;
	char			*filename;

	rdr_type = rdr_node->left->type;
	filename = rdr_node->right->value;
	if (rdr_type == RDR_O || rdr_type == RDR_DO) // > or >>
		return (redirect_output(rdr_type, filename));
	return (redirect_input(filename)); // <
										// herdoc will be treated seperately
}

int	redirect_without_fork(t_node *rdr_node)
{
	int	res;

	if (!rdr_node) // if there's no redirection
		return (0);
	if (rdr_node->type == RDR) // To check with Siria,
								// if we make IO_RDR or IO_HERE
	{
		if (redirect_node(rdr_node) == -1)
			return (-1);
	}
	if (rdr_node->left && redirect_without_fork(rdr_node->left) == -1)
		return (-1);
	if (rdr_node->right && redirect_without_fork(rdr_node->right) == -1)
		return (-1);
	return (0);
}

void	backup_restore_stdio(int *stdin_fd, int *stdout_fd, bool restore)
{
	if (restore)
	{
		ft_dup2(stdin_fd, STDIN_FILENO);   // duplicate stdin
		ft_close(stdin_fd);                // close duplicated stdin
		ft_dup2(stdout_fd, STDOUT_FILENO); // duplicate stdout
		ft_close(stdout_fd);               // close duplicated stdout
	}
	else // backup
	{
		*stdin_fd = dup(STDIN_FILENO);   // duplicate stdin
		*stdout_fd = dup(STDOUT_FILENO); // duplicate stdout
		if (*stdin_fd < 0 || *stdout_fd < 0)
			exit_with_err("dup()", strerror(errno), EXIT_FAILURE); // TBD
	}
}

void	execute_without_fork(t_node *cmd_node, t_cmd_type cmd_type)
{
	int		stdin_backup;
	int		stdout_backup;
	char	**argv;

	backup_restore_stdio(&stdin_backup, &stdout_backup, false); // backup
	if (redirect_without_fork(cmd_node->left) == -1)
	{
		backup_restore_stdio(stdin_backup, stdout_backup, true); // restore
		return ;
	}
	if (cmd_type == NONE) // when there's no CMD
	{
		mini()->exit_code = EXIT_SUCCESS;                        // TBD
		backup_restore_stdio(stdin_backup, stdout_backup, true); // restore
		return ;
	}
	argv = prepare_cmd_args(cmd_node);                // TBD
	execute_cmd_or_builtin(argv, cmd_type, cmd_node); // TBD
	free_ptr((void **)&argv);
	backup_restore_stdio(stdin_backup, stdout_backup, true); // restore
}

void	ft_dup2(int old_fd, int new_fd)
{
	int	ret;

	ret = dup2(old_fd, new_fd);
	if (ret < 0)
		exit_with_err("dup2()", strerror(errno), EXIT_FAILURE); // TBD
}

void	ft_close(int fd)
{
	int	ret;

	ret = close(fd);
	if (ret < 0)
		exit_with_err("close()", strerror(errno), EXIT_FAILURE); // TBD
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
		exit_with_err("pipe()", strerror(errno), EXIT_FAILURE); // TBD
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

// initialize a new cmd struct
t_cmd	get_new_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	new_cmd->fd_in = -1;
	new_cmd->fd_out = -1;
	return (new_cmd);
}

void	execute_with_fork(t_node *node, t_cmd *last_cmd)
{
	t_cmd	*current_cmd;

	current_cmd = get_new_cmd();
	ft_lstadd_back(&(mini()->cmd_list), ft_lstnew(current_cmd));
	if (node->right) // create pipe
		ft_pipe(current_cmd);
	signal(SIGQUIT, ignore_signal); // TBD ignore SIGQUIT
	current_cmd->pid = fork();
	if (current_cmd->pid < 0)
		exit_with_error("fork()", strerror(errno), EXIT_FAILURE); // TBD
	if (current_cmd->pid == 0)
	// child process
	{
		setup_pipes(last_cmd, current_cmd);
		redirect_with_fork(node->left->left); // TBD
		execute_cmd(node->left->right);       // TBD
	}
	if (node->right)
		ft_close(current_cmd->fd_out); // close write end
	close_pipes(last_cmd)
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
		execute_without_fork(tree->left, (t_cmd_type)result);
	// fork not needed
	else
		execute_with_fork(tree, last_cmd); // fork needed
}

void	free_cmd_list(void)
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
	restore_echoctl(); // TBD
	signal(SIGINT, ignore_signal);
	wait_for_children(); // TBD
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
