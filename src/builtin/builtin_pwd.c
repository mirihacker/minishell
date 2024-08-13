/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:20:16 by eahn              #+#    #+#             */
/*   Updated: 2024/08/13 12:25:43 by smiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	builtin_pwd(char **av)
{
	char	*cwd;

	if (av[1] && av[1][0] != '\0')
	{
		ft_putstr_fd("pwd: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		print_error("pwd", NULL, strerror(errno));
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	return (EXIT_SUCCESS);
}
