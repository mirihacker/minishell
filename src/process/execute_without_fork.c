/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_without_fork.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:41:50 by eahn              #+#    #+#             */
/*   Updated: 2024/08/16 11:06:55 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

/**
 * @brief backup standard input/output fds.
 */

static void	backup_stdio(int *stdin_fd, int *stdout_fd)
{
	*stdin_fd = dup(STDIN_FILENO);
	*stdout_fd = dup(STDOUT_FILENO);
	if (*stdin_fd < 0 || *stdout_fd < 0)
		exit_error("dup()", strerror(errno), EXIT_FAILURE);
}

/**
 * @brief restore standard input/output fds.
 */
static void	restore_stdio(int stdin_fd, int stdout_fd)
{
	ft_dup2(stdin_fd, STDIN_FILENO);
	ft_close(stdin_fd);
	ft_dup2(stdout_fd, STDOUT_FILENO);
	ft_close(stdout_fd);
}

/**
 * @brief Prepares command argument from AST node.
 * - Allocates memory for argument array and populates it based on command node.
 * - First argument is command itself,
	additional arguments are parsed from cmdline.
 */
static char	**prepare_cmd_args(t_node *cmd_node)
{
	char	**argv;

	argv = (char **)ft_calloc(2, sizeof(char *));
	if (!argv)
		exit_error("malloc()", strerror(errno), EXIT_FAILURE);
	argv[0] = cmd_node->right->left->value;
	get_cmdline(&argv, cmd_node->right->right);
	return (argv);
}

/**
 * @brief Executes command if it is an exit or builtin command.
 * - If command is exit, handles exit process and shell.
 * - For other builtin, delegates execution to builtin handler.
 */
static void	execute_if_exit(char **argv, t_cmd_type cmd_type, t_node *cmd_node)
{
	int		shoud_exit;
	t_mini	*mini;

	mini = get_mini();
	if (cmd_type == EXIT)
	{
		shoud_exit = 1;
		ft_putendl_fd("exit", STDOUT_FILENO);
		mini->exit_code = builtin_exit(argv, &shoud_exit);
		if (shoud_exit)
		{
			delete_tmpfile(cmd_node);
			exit(mini->exit_code);
		}
	}
	else
		mini->exit_code = execute_builtin(argv, cmd_type);
}

/**
 * @brief Executes command without forking a new process (builtin)
 * - Handles std input/output redirection and then executes command.
 * - After execution, restores std input/output.
 */
void	execute_without_fork(t_node *cmd_node, t_cmd_type cmd_type)
{
	t_mini	*mini;
	int		stdin_backup;
	int		stdout_backup;
	char	**argv;

	mini = get_mini();
	backup_stdio(&stdin_backup, &stdout_backup);
	if (handle_redirection(cmd_node->left) == -1)
	{
		restore_stdio(stdin_backup, stdout_backup);
		return ;
	}
	if (cmd_type == NONE)
	{
		mini->exit_code = EXIT_SUCCESS;
		restore_stdio(stdin_backup, stdout_backup);
		return ;
	}
	argv = prepare_cmd_args(cmd_node);
	execute_if_exit(argv, cmd_type, cmd_node);
	free_ptr((void **)&argv);
	restore_stdio(stdin_backup, stdout_backup);
}
