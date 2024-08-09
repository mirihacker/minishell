/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:52:31 by eahn              #+#    #+#             */
/*   Updated: 2024/08/09 16:12:35 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

// redirect_files_no_fork.c
int	verify_system_call(int res, char *str)
{
	t_mini	*mini;

	mini = get_mini();
	if (res < 0)
	{
		print_err(str, NULL, strerror(errno));
		mini->exit_code = EXIT_FAILURE;
		return (-1);
	}
	return (0);
}

// redirect_files.c or redirect_with_fork from execute_with_fork.c
int	ft_open(char *filename, int open_flag, int mode)
{
	int	fd;

	fd = open(filename, open_flag, mode);
	if (fd < 0)
		exit_error(filename, strerror(errno), EXIT_FAILURE);
	return (fd);
}