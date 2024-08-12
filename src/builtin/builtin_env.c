/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:10:33 by smiranda          #+#    #+#             */
/*   Updated: 2024/08/12 17:40:29 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int is_option_echo(char *str)
{
    if (str[0] == '-')
    {
        if (str[1] != 'n')
        {
            ft_putstr_fd("limonshello: echo: ", STDERR_FILENO);
            write(STDERR_FILENO, str, 2);
            ft_putstr_fd(": invalid option\n", STDERR_FILENO);
            ft_putstr_fd("echo: usage: echo [-n] [string ...]\n", STDERR_FILENO);
            return (1);
        }
    }
    return (0);
}

static	void	print_usage(char *cmd)
{
	if (!ft_strcmp(cmd, "cd"))
		ft_putendl_fd("cd [directory]", STDERR_FILENO);
	else if (!ft_strcmp(cmd, "pwd"))
		ft_putendl_fd("pwd [argument]", STDERR_FILENO);
	else if (!ft_strcmp(cmd, "env"))
		ft_putendl_fd("env", STDERR_FILENO);
	else if (!ft_strcmp(cmd, "export"))
		ft_putendl_fd("export [NAME[=value] ...]", STDERR_FILENO);
	else if (!ft_strcmp(cmd, "unset"))
		ft_putendl_fd("unset [name ...]", STDERR_FILENO);
}

int is_option(char *str, char *cmd)
{
    int ret;

    ret = 0;
    if (!ft_strcmp(cmd, "echo"))
        ret = is_option_echo(str);
    else
    {
        if (str[0] == '-')
        {
            if (str[1])
            {
                ft_putstr_fd("limonshello: ", STDERR_FILENO);
                ft_putstr_fd(cmd, STDERR_FILENO);
                ft_putstr_fd(": ", STDERR_FILENO);
                write(STDERR_FILENO, str, 2);
                ft_putstr_fd(": option not allowed\n", STDERR_FILENO);
                ft_putstr_fd(cmd, STDERR_FILENO);
                ft_putstr_fd(": usage: ", STDERR_FILENO);
                print_usage(cmd);
                ret = 1;
            }
        }
    }
    return (ret);
}

int	builtin_env(char **argv)
{
	t_list	*ptr;
    t_mini	*mini;

    mini = get_mini();
	ptr = mini->env_list;
	if (argv[1])
	{
		if (is_option(argv[1], "env"))
			return (EXIT_FAILURE);
		print_err("env", argv[1], strerror(EINVAL));
		ft_putendl_fd("env: usage: env", STDERR_FILENO);
		return (127);
	}
	while (ptr)
	{
		if (ft_strchr(ptr->content, '='))
			ft_putendl_fd((char *)ptr->content, STDOUT_FILENO);
		ptr = ptr->next;
	}
	return (EXIT_SUCCESS);
}
