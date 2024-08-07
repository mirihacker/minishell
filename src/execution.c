/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:27:59 by smiranda          #+#    #+#             */
/*   Updated: 2024/08/07 12:24:13 by smiranda         ###   ########.fr       */
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
    return (args + 1);
}

void get_cmdline(char ***cmdline, t_node *arg)
{
    char	**new_arg;
	int		i;

	if (!arg)
		return ;
	if (arg->type == CMD_SUFFIX)
	{
		new_arg = (char **)ft_calloc(count_arg(*cmdline) + 1, sizeof(char *));
		i = 0;
		while ((*cmdline)[i])
        {
			new_arg[i] = (*cmdline)[i];
            i++;
        }
        new_arg[i] = arg->left->value;
		free_ptr((void **)arg);
		*cmdline = new_arg;
	}
	get_cmdline(cmdline, arg->right);
}

void	execution(t_node *node)
{
	char		**arguments;
	t_cmd_type	cmd_type;
	int			exit_code;

    // init execution //
	arguments = (char **)ft_calloc(2, sizeof(char *));
	arguments[0] = node->left->value;
	get_cmdline(&arguments, node->right);
    // check command type //
	cmd_type = which_cmd_type(arguments[0]);
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
