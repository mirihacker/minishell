/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:27:59 by smiranda          #+#    #+#             */
/*   Updated: 2024/08/07 17:09:43 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int count_arg(char **argv)
{
    int args;

    args = 0;
    while (*argv)
    {
        args++;
        argv++;
    }
    return (args + 1); // +1 for the NULL pointer at the end
}

void get_cmdline(char ***cmdline, t_node *arg)
{
    char	**new_arg;
	int		i;

	if (!arg)
		return ;
	if (arg->type == CMD_SUFFIX) //check if the current node is a suffix type (is an option to the main cmd)
	{
		new_arg = (char **)ft_calloc(count_arg(*cmdline) + 1, sizeof(char *)); // +1 for the following argument
		i = 0;
		while ((*cmdline)[i]) //copy existing arguments
        {
			new_arg[i] = (*cmdline)[i];
            i++;
        }
        new_arg[i] = arg->left->value; //add the new argument
		free_ptr((void **)arg);
		*cmdline = new_arg;
	}
	get_cmdline(cmdline, arg->right); //recursive call for the next subtree in case there is one
}

t_cmd_type	cmd_type_tester(char *cmd_name)
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
		exit_with_err(argv[0], "command not found", 127);
	else
	{
		cmd = find_abs_path(cmd);
		new_envp = make_envp();
		execve(cmd, argv, new_envp);
		if (errno == ENOENT)
			exit_with_err(argv[0], "command not found", 127);
		exit_with_err(argv[0], strerror(errno), EXIT_FAILURE);
	}
}

int	execute_builtin(char **argv, t_cmd_type cmd_type) //TBD
{
	int		exit_code;

	if (cmd_type == CD)
		exit_code = ft_cd(argv);
	else if (cmd_type == ECHO_)
		exit_code = ft_echo(argv);
	else if (cmd_type == ENV)
		exit_code = ft_env(argv);
	else if (cmd_type == EXIT)
		exit_code = ft_exit(argv, NULL);
	else if (cmd_type == EXPORT)
		exit_code = ft_export(argv);
	else if (cmd_type == PWD)
		exit_code = ft_pwd(argv);
	else
		exit_code = ft_unset(argv);
	return (exit_code);
}

char ** init_arguments(t_node *node)
{
	char		**arguments;

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
	if (cmd_type == GENERAL)
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
