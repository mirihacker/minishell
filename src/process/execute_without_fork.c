/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_execute_without.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:41:50 by eahn              #+#    #+#             */
/*   Updated: 2024/08/09 16:10:30 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

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
			exit_error("dup()", strerror(errno), EXIT_FAILURE); // TBD
	}
}

char	**prepare_cmd_args(t_node *cmd_node)
{
	char	**argv;

	argv = (char **)ft_calloc(2, sizeof(char *));
	argv[0] = cmd_node->right->left->value;
	get_cmdline(&argv, cmd_node->right->right);
	return (argv);
}

void	execute_if_exit(char **argv, t_cmd_type cmd_type, t_node *cmd_node)
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

void	execute_without_fork(t_node *cmd_node, t_cmd_type cmd_type)
{
	t_mini	*mini;
	int		stdin_backup;
	int		stdout_backup;
	char	**argv;

	mini = get_mini();
	backup_restore_stdio(&stdin_backup, &stdout_backup, false); // backup
	if (redirect_without_fork(cmd_node->left) == -1)
	{
		backup_restore_stdio(stdin_backup, stdout_backup, true); // restore
		return ;
	}
	if (cmd_type == NONE) // when there's no CMD
	{
		mini->exit_code = EXIT_SUCCESS;
		backup_restore_stdio(stdin_backup, stdout_backup, true); // restore
		return ;
	}
	argv = prepare_cmd_args(cmd_node);
	execute_if_exit(argv, cmd_type, cmd_node);
	free_ptr((void **)&argv);
	backup_restore_stdio(stdin_backup, stdout_backup, true); // restore
}
