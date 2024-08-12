/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:27:46 by eahn              #+#    #+#             */
/*   Updated: 2024/08/12 17:26:50 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (i > 0);
}

// if code negative, make it positive
// if code > 255, make it modulo 256
static int	get_exit_code(char *str)
{
	int	status;

	status = ft_atoi(str);
	if (status < 0)
		status = 256 - (-status % 256);
	else
		status %= 256;
	return (status);
}

// only called form execute_if_exit
// it can be removed from execute_builtin
// then make print_error function only for builtin_exit
int	builtin_exit(char **av, int *exit_requested)
{
	int		exit_code;
	t_mini	*mini;

	mini = get_mini();
	if (!av[1])
		return (mini->exit_code);
	if (!is_number(av[1]))
	{
		print_error("exit", av[1], "numeric argument required");
		return (255);
	}
	exit_code = get_exit_code(av[1]);
	if (av[2])
	{
		print_error("exit", NULL, "too many arguments");
		if (exit_requested)
			*exit_requested = 0;
		return (EXIT_FAILURE);
	}
	return (exit_code);
}
