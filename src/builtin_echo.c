/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:59:14 by eahn              #+#    #+#             */
/*   Updated: 2024/08/07 16:27:44 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_n_option(const char *str)
{
	if (*str == '-')
	{
		str++;
		while (*str == 'n')
			str++;
		if (*str == '\0')
			return (1);
	}
	return (0);
}

int	builtin_echo(char **av)
{
	int	has_n_option;

	has_n_option = 0;
	av++;
	while (*av && is_n_option(*av))
	{
		has_n_option = 1;
		av++;
	}
	while (*av)
	{
		ft_putstr_fd(*av, STDOUT_FILENO);
		if (*(av + 1))
			ft_putstr_fd(" ", STDOUT_FILENO);
		av++;
	}
	if (!has_n_option)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
