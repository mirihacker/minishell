/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:27:59 by smiranda          #+#    #+#             */
/*   Updated: 2024/08/12 19:54:49 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	execute_builtin(char **argv, t_cmd_type cmd_type) // TBD
{
	int exit_code;

	if (cmd_type == CD)
		exit_code = builtin_cd(argv);
	else if (cmd_type == ECHO_)
		exit_code = builtin_echo(argv);
	else if (cmd_type == ENV)
		exit_code = builtin_env(argv);
	else if (cmd_type == EXIT)
		exit_code = builtin_exit(argv, 0);
	else if (cmd_type == EXPORT)
		exit_code = builtin_export(argv);
	else if (cmd_type == PWD)
		exit_code = builtin_pwd(argv);
	else
		exit_code = builtin_unset(argv);
	return (exit_code);
}

static t_cmd_type	cmd_type_tester(char *cmd_name)
{
	t_cmd_type	type;

	if (!cmd_name)
		type = NONE;
	else if (!ft_strcmp(cmd_name, "cd"))
		type = CD;
	else if (!ft_strcmp(cmd_name, "echo"))
		type = ECHO_;
	else if (!ft_strcmp(cmd_name, "env"))
		type = ENV;
	else if (!ft_strcmp(cmd_name, "exit"))
		type = EXIT;
	else if (!ft_strcmp(cmd_name, "export"))
		type = EXPORT;
	else if (!ft_strcmp(cmd_name, "pwd"))
		type = PWD;
	else if (!ft_strcmp(cmd_name, "unset"))
		type = UNSET;
	else
		type = GENERAL;
	return (type);
}

static void	execute_general(char *cmd, char **argv)
{
	char	**new_envp;

	if (!ft_strncmp(".", cmd, 2) || !ft_strncmp("..", cmd, 3))
		exit_error(argv[0], "command not found", 127);
	else
	{
		cmd = find_abs_path(cmd);
		new_envp = get_var_val_list();
		execve(cmd, argv, new_envp);
		if (errno == ENOENT) //shell command not found
			exit_error(argv[0], "command not found", 127);
		exit_error(argv[0], strerror(errno), EXIT_FAILURE);
	}
}

static char	**init_arguments(t_node *node)
{
	char	**arguments;

	arguments = (char **)ft_calloc(2, sizeof(char *));
	arguments[0] = node->left->value;
	get_cmdline(&arguments, node->right);
	return (arguments);
}

void	execution(t_node *node)
{
	char		**arguments;
	t_cmd_type	cmd_type;
	int			exit_code;

	// init execution //
	arguments = init_arguments(node);
	// check command type //
	cmd_type = cmd_type_tester(arguments[0]);
	if (cmd_type == GENERAL) // tbd name
		execute_general(node->left->value, arguments);
	else if (cmd_type == NONE)
		exit(EXIT_SUCCESS);
	else
	{
		exit_code = execute_builtin(arguments, cmd_type);
		exit(exit_code);
	}
}

// void	execution(t_node *node)
// {
// 	char		**arguments;
// 	t_cmd_type	cmd_type;
// 	int			exit_code;

//     // init execution //
// 	// Gather all arguments to form the comand line //
// 	arguments = (char **)ft_calloc(2, sizeof(char *));
// 	arguments[0] = node->left->value;
// 	get_cmdline(&arguments, node->right);
//     // check command type //
// 	cmd_type = cmd_type_tester(arguments[0]);
// 	if (cmd_type == GENERAL)
// 		execute_general(node->left->value, arguments);
// 	else if (cmd_type == NONE)
// 		exit(EXIT_SUCCESS);
// 	else
// 	{
// 		exit_code = execute_builtin(arguments, cmd_type);
// 		exit(exit_code);
// 	}
// }
